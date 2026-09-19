"""单文件钢琴程序：音色合成 + 乐谱编曲 + 渲染播放 / 导出。

原本拆成 synth.py / score.py / play.py 三个文件，现在合成一个 music.py，
不再需要 `import synth`、`import score`，直接用本文件里的名字即可。

依赖：numpy（必需）；sounddevice（播放用，可选）
    python -m pip install numpy sounddevice

运行：
    python music.py                 # 直接播放
    python music.py --score         # 只在终端打印和声进行与钢琴卷帘
    python music.py --wav out.wav   # 顺便存一份 WAV
    python music.py --midi out.mid  # 导出 MIDI
    python music.py --no-play       # 只渲染不播放
    python music.py --fast          # 粗渲染（少分音、短余韵），几秒就能出声
    python music.py --list-devices  # 列出音频输出设备，再用 --device N 指定

文件分三段（§1 → §2 → §3）：

  §1 音色合成   render_note / write_wav / widen / soft_clip
      音色做法：
        * 加法合成 —— 每个音叠加衰减的正弦"分音"，分音频率带轻微非谐性（钢琴弦的刚性）
        * 每个音用两根略微失谐的"弦"模拟同音弦群的自然拍频（chorus）
        * 幅度包络 = 极快起音 + 双指数衰减（琴弦 + 音板），余韵长度自动算到听不见为止
        * 高音区混入一点 FM（钟琴感），低音区加重低次分音
      混响不在这里，在 §3 的 _reverb_fast()（FFT 卷积一段噪声脉冲响应）。

  §2 乐谱与编曲  CHORDS / THEME_A,B / CODA / ARP_PATTERNS / build_piece()
      这里存的是"乐谱数据"：
        * CHORDS        8 小节循环的和声进行
        * THEME_A/B     主部与中段旋律（以 4/4 拍的"拍"为单位）
        * ARP_PATTERNS  左手八分音符分解和弦音型
        * build_piece() 把乐谱展开成一份带时间的演奏事件表

      事件表是纯数据（音高 / 起始秒 / 时长 / 力度 / 声像 / 声部），
      所以同一份事件表可以拿去合成音频、导出 MIDI，或画成钢琴卷帘。

      音乐特征（这首曲子的辨识点，编排时都尽量保留）：
        1. 同一个音的重复动机 —— 开头的音型是"同一音 + 落回"的反复，
           不是一句到处游走的旋律；乐句内部也大量使用重复音。
        2. 左手持续不断的分解和弦（八分音符为主），像钟声一样不停走动。
        3. 8 小节一句，句子结构对称：前半上行、后半落回主音。
        4. 主部 → 中段（转到下属方向）→ 主部再现 → 尾声，力度层层推进。

      全曲结构（4/4，♩=66）：
        前奏 4 → A 8 → A' 8 → B 8 → A'' 8 → 尾声 9 = 45 小节

  §3 渲染与播放  render_piece / _reverb_fast / play / export_midi / show_score / main
"""

from __future__ import annotations

import argparse
import time
import wave
from pathlib import Path

import numpy as np


PROJECT_DIR = Path(__file__).resolve().parent


SAMPLE_RATE = 44_100


_PITCH_CLASS = {"C": 0, "D": 2, "E": 4, "F": 5, "G": 7, "A": 9, "B": 11}
_ACCIDENTAL = {"#": 1, "b": -1, "♯": 1, "♭": -1}


def note_to_midi(name: str) -> int:
    """'F#4' / 'Bb3' / 'C5' -> MIDI 音高编号（中央 C = C4 = 60）。"""
    name = name.strip()
    if not name:
        raise ValueError("空音名")
    letter = name[0].upper()
    if letter not in _PITCH_CLASS:
        raise ValueError(f"无法识别的音名: {name!r}")
    i, accidental = 1, 0
    while i < len(name) and name[i] in _ACCIDENTAL:
        accidental += _ACCIDENTAL[name[i]]
        i += 1
    octave = int(name[i:])
    return 12 * (octave + 1) + _PITCH_CLASS[letter] + accidental


def midi_to_freq(midi: float) -> float:
    """MIDI 编号 -> 频率(Hz)，A4 = 440Hz。"""
    return 440.0 * 2.0 ** ((midi - 69) / 12.0)


_N_PARTIALS = 8
_TAIL_CAP = 3.0
_NYQUIST = SAMPLE_RATE * 0.47
_AUDIBLE = 1.0e-4


def _partial_weights(midi: float) -> np.ndarray:
    """返回 8 个分音的相对强度。"""
    brightness = float(np.clip((midi - 36) / 48.0, 0.0, 1.0))
    base = np.array([1.00, 0.50, 0.30, 0.18, 0.11, 0.070, 0.045, 0.030])
    tilt = np.array([1.25, 1.10, 1.00, 0.92, 0.85, 0.78, 0.72, 0.66])
    return base * (tilt ** brightness) * (brightness ** (0.35 * np.arange(_N_PARTIALS)))


def _string_decay(midi: float) -> float:
    """琴弦衰减时间常数（秒）：低音长、高音短。"""
    return 1.3 + 15.0 * np.exp(-(midi - 21) / 26.0)


def render_note(midi: float, velocity: float, duration: float,
                n_partials: int = _N_PARTIALS, tail_cap: float = _TAIL_CAP) -> np.ndarray:
    """合成一个钢琴音，返回单声道 float32 波形。

    duration 是"手指按住"的时长，之后还会附加一段自由衰减的余韵
    （自动算到听不见为止：低音尾巴长、高音尾巴短）。
    """
    freq = midi_to_freq(midi)
    string_tau = _string_decay(midi)
    tau_fast = 0.25 + 2.4 * string_tau
    tau_slow = 18.0 * string_tau


    a, b = 1.0 / tau_fast, 1.0 / tau_slow
    disc = (5.0 * (a + b)) ** 2 - 20.0 * b * np.log(_AUDIBLE)
    ring = float(np.clip((5.0 * (a + b) + np.sqrt(max(disc, 0.0))) / 10.0, 0.15, tail_cap))
    n = int((duration + ring) * SAMPLE_RATE) + 1
    t = (np.arange(n, dtype=np.float32) / np.float32(SAMPLE_RATE))

    weights = _partial_weights(midi)[:n_partials]

    env = -np.exp(-t / np.float32(0.0016))
    env += 1.0
    env *= np.exp(-t / np.float32(tau_fast))
    env *= np.exp(-t / np.float32(tau_slow))

    wave = np.zeros(n, dtype=np.float32)

    for detune, gain in ((0.9993, 1.0), (1.0009, 0.55)):
        for k, weight in enumerate(weights):
            partial = k + 1
            f = freq * partial * detune * (1.0 + 0.00018 * partial * partial)
            if f > _NYQUIST:
                break
            tau = string_tau / (1.0 + 0.55 * k)
            phase = t * np.float32(f)
            if k:
                phase += np.float32(0.25 * k / (2.0 * np.pi))
            wave += (weight * gain * np.exp(-t / np.float32(tau))) * np.sin(
                phase * np.float32(2.0 * np.pi))


    if midi >= 72:
        index = (1.1 * np.exp(-t / np.float32(0.16))).astype(np.float32)
        wave += 0.05 * np.exp(-t / np.float32(0.35 * string_tau)) * np.sin(
            t * np.float32(freq * 3.7 * 2.0 * np.pi) + index)

    wave *= env * np.float32(velocity ** 1.45 * 0.16)
    return wave


def widen(sig: np.ndarray, ms: float = 11.0) -> np.ndarray:
    """Haas 效应：右声道延迟若干毫秒，制造宽度。"""
    d = int(ms * SAMPLE_RATE / 1000.0)
    out = sig.copy()
    out[d:, 1] = sig[:-d, 1]
    return out


def soft_clip(sig: np.ndarray, drive: float = 1.15) -> np.ndarray:
    """温和的软限幅，防止叠加处爆音。"""
    return np.tanh(sig * drive) / np.tanh(drive)


def write_wav(path, stereo: np.ndarray, sample_rate: int = SAMPLE_RATE) -> None:
    """把 float 立体声写成立体声 16bit WAV。"""
    peak = float(np.max(np.abs(stereo))) or 1.0
    ints = np.clip(stereo / peak * 0.92 * 32767.0, -32768, 32767).astype("<i2")
    with wave.open(str(path), "wb") as f:
        f.setnchannels(2 if stereo.ndim == 2 else 1)
        f.setsampwidth(2)
        f.setframerate(sample_rate)
        f.writeframes(ints.tobytes())


CHORDS: dict[str, list[str]] = {
    "Bm":  ["B2", "F#3", "B3", "D4", "F#4", "B4", "D5", "F#5"],
    "G":   ["G2", "D3", "G3", "B3", "D4", "G4", "B4", "D5"],
    "D":   ["D3", "A3", "D4", "F#4", "A4", "D5", "F#5", "A5"],
    "A":   ["A2", "E3", "A3", "C#4", "E4", "A4", "C#5", "E5"],
    "F#m": ["F#2", "C#3", "F#3", "A3", "C#4", "F#4", "A4", "C#5"],
    "F#":  ["F#2", "C#3", "F#3", "A#3", "C#4", "F#4", "A#4", "C#5"],
    "Em":  ["E3", "B3", "E4", "G4", "B4", "E5", "G5", "B5"],
}


PROGRESSION: list[str] = ["F#m", "Bm", "G", "F#",
                          "Bm", "G", "D", "A"]


PROGRESSION_B: list[str] = ["G", "D", "Em", "A",
                            "F#m", "Bm", "G", "F#"]


ARP_PATTERNS: list[list[int]] = [
    [0, 2, 1, 2, 0, 2, 1, 2, 0, 2, 1, 2, 0, 2, 1, 2],
    [0, 2, 1, 3, 1, 2, 0, 2, 1, 3, 2, 1, 0, 2, 1, 2],
    [0, 2, 1, 2, 3, 2, 1, 2, 0, 2, 1, 2, 3, 2, 1, 2],
]


def chord_for_bar(bar: int) -> str:
    """第 bar 小节（从 0 开始）的和弦名。"""
    return PROGRESSION[bar % len(PROGRESSION)]


THEME_A: list[tuple[float, str, float]] = [

    (0.0, "F#4", 1.5),
    (1.5, "F#4", 0.5),
    (2.0, "F#4", 1.0),
    (3.0, "E4", 1.0),

    (4.0, "D4", 1.5),
    (5.5, "D4", 0.5),
    (6.0, "D4", 1.0),
    (7.0, "B3", 1.0),

    (8.0, "F#4", 2.0),
    (10.0, "A4", 1.0),
    (11.0, "F#4", 2.0),

    (13.0, "E4", 1.0),
    (14.0, "D4", 2.0),

    (16.0, "F#4", 1.5),
    (17.5, "F#4", 0.5),
    (18.0, "F#4", 1.0),
    (19.0, "A4", 1.0),

    (20.0, "B4", 2.0),
    (22.0, "A4", 1.0),
    (23.0, "F#4", 1.0),

    (24.0, "G4", 2.0),
    (26.0, "F#4", 1.0),
    (27.0, "E4", 1.0),

    (28.0, "F#4", 2.0),
    (30.0, "B3", 2.0),
]


THEME_B: list[tuple[float, str, float]] = [

    (0.0, "D5", 1.5),
    (1.5, "B4", 0.5),
    (2.0, "G4", 2.0),

    (4.0, "F#4", 1.5),
    (5.5, "A4", 0.5),
    (6.0, "D5", 2.0),

    (8.0, "E5", 1.5),
    (9.5, "D5", 0.5),
    (10.0, "B4", 2.0),

    (12.0, "C#5", 1.5),
    (13.5, "B4", 0.5),
    (14.0, "A4", 2.0),

    (16.0, "F#4", 1.5),
    (17.5, "A4", 0.5),
    (18.0, "C#5", 2.0),

    (20.0, "B4", 1.5),
    (21.5, "F#4", 0.5),
    (22.0, "D4", 2.0),

    (24.0, "G4", 1.5),
    (25.5, "A4", 0.5),
    (26.0, "B4", 2.0),

    (28.0, "A#4", 1.5),
    (29.5, "C#5", 0.5),
    (30.0, "F#4", 2.0),
]


THEME_CODA: list[tuple[float, str, float]] = [
    (0.0, "F#4", 1.5),
    (1.5, "F#4", 0.5),
    (2.0, "F#4", 1.0),
    (3.0, "E4", 1.0),
    (4.0, "D4", 1.5),
    (5.5, "D4", 0.5),
    (6.0, "B3", 2.0),
    (8.0, "F#4", 2.0),
    (10.0, "A4", 1.0),
    (11.0, "F#4", 1.0),
    (12.0, "E4", 2.0),
    (14.0, "D4", 2.0),
    (16.0, "B3", 2.0),
    (18.0, "D4", 2.0),
    (20.0, "F#4", 2.0),
    (22.0, "E4", 2.0),
    (24.0, "D4", 2.0),
    (26.0, "C#4", 2.0),
    (28.0, "D4", 2.0),
    (30.0, "F#4", 2.0),
    (32.0, "B3", 4.0),
]


def transpose(note: str, semitones: int) -> str:
    """把音名整体移动若干半音（用于八度加倍）。"""
    midi = note_to_midi(note) + semitones
    names = ["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"]
    return f"{names[midi % 12]}{midi // 12 - 1}"


TOTAL_BARS = 45
_CODA_START = 36
_SLOWDOWN_FROM = 36


def _intensity(bar: int) -> float:
    """每小节的力度（0~1）：让全曲有一次完整的起伏。"""
    if bar < 4:
        return 0.30 + 0.08 * bar
    if bar < 12:
        return 0.66
    if bar < 20:
        return 0.80
    if bar < 28:
        return 0.92
    if bar < 36:
        return 0.78
    return max(0.24, 0.52 - 0.035 * (bar - _CODA_START))


def _bpm_scale(bar: int) -> float:
    """尾声逐小节渐慢：返回该小节相对时长的放大系数。"""
    if bar < _SLOWDOWN_FROM:
        return 1.0
    return 1.0 + 0.014 * (bar - _SLOWDOWN_FROM)


def _time_map(bpm: float) -> tuple[list[float], list[float]]:
    """预计算每小节的 (等间距拍位, 含渐慢的绝对秒数)。"""
    beat = 60.0 / bpm
    times, beats = [0.0], [0.0]
    for bar in range(TOTAL_BARS + 1):
        times.append(times[-1] + 4.0 * beat * _bpm_scale(bar))
        beats.append(beats[-1] + 4.0)
    return beats, times


def _section_chord(bar: int) -> str:
    """按段落取和弦：中段用 PROGRESSION_B。"""
    if 20 <= bar < 28:
        return PROGRESSION_B[(bar - 20) % len(PROGRESSION_B)]
    return PROGRESSION[bar % len(PROGRESSION)]


def build_piece(bpm: float = 66.0, tail_seconds: float = 6.0):
    """展开成演奏事件表。

    返回 (events, duration)：
      events   = [{"midi","start","duration","velocity","pan","voice"}, ...]
      duration = 全曲秒数（含混响尾巴）
    """
    beat = 60.0 / bpm
    bar_beats, _bar_time = _time_map(bpm)
    events: list[dict] = []

    def add(note: str, abs_beat: float, dur_beats: float, velocity: float,
            pan: float = 0.0, voice: str = "arp", bar: int | None = None) -> None:
        if bar is None:
            bar = min(TOTAL_BARS - 1, int(abs_beat // 4.0))
        scale = _bpm_scale(bar)
        events.append({
            "midi": note_to_midi(note),
            "start": abs_beat * beat,
            "duration": max(0.06, dur_beats * beat * scale),
            "velocity": float(min(1.0, max(0.05, velocity))),
            "pan": pan,
            "voice": voice,
        })

    for bar in range(TOTAL_BARS):
        chord = _section_chord(bar)
        voicing = CHORDS[chord]
        intensity = _intensity(bar)
        pattern = ARP_PATTERNS[(bar // 4) % len(ARP_PATTERNS)]
        bar_start = bar_beats[bar]


        for step, idx in enumerate(pattern):
            note = voicing[idx]

            accent = 1.0 if step % 4 == 0 else (0.80 if step % 2 == 0 else 0.66)
            add(note, bar_start + step * 0.25, 2.0,
                intensity * accent * 0.46, pan=-0.32, voice="arp", bar=bar)


        add(voicing[0], bar_start, 3.4, intensity * 0.52, pan=-0.04, voice="bass", bar=bar)
        add(voicing[0], bar_start + 2.0, 1.8, intensity * 0.34, pan=-0.04, voice="bass", bar=bar)


        if bar < 4:
            add("F#5", bar_start, 3.5, 0.26, pan=0.28, voice="shimmer", bar=bar)


        melody: list[tuple[float, str, float]] | None = None
        phrase_bar, octave, vel = 0, 0, 0.80
        if 4 <= bar < 20:
            melody, phrase_bar = THEME_A, 4
            octave, vel = (0, 0.76) if bar < 12 else (0, 0.86)
        elif 20 <= bar < 28:
            melody, phrase_bar, octave, vel = THEME_B, 20, 0, 0.90
        elif 28 <= bar < 36:
            melody, phrase_bar, octave, vel = THEME_A, 28, 12, 0.86
        elif bar >= _CODA_START:
            melody, phrase_bar, octave, vel = THEME_CODA, _CODA_START, 0, 0.60

        if melody is None:
            continue

        rel = (bar - phrase_bar) * 4.0
        for start, note, dur in melody:
            local = start - rel
            if not (-dur <= local < 4.0):
                continue
            offset = max(0.0, local)
            length = min(dur + local, 4.0 - offset)
            if length <= 0.05:
                continue
            add(transpose(note, octave), bar_start + offset, length,
                vel * intensity / 0.78, pan=0.26, voice="melody", bar=bar)
            if octave == 12:
                add(transpose(note, 0), bar_start + offset, length,
                    vel * 0.40 * intensity / 0.78, pan=0.10, voice="melody-double", bar=bar)

    events.sort(key=lambda e: e["start"])
    last = max(e["start"] + e["duration"] for e in events)
    return events, last + tail_seconds


MELODY_VOICES = ("melody", "melody-double", "shimmer")


def melody_only(events: list[dict]) -> list[dict]:
    """筛出右手部分（供参考/可视化）。"""
    return [e for e in events if e.get("voice") in MELODY_VOICES]


def render_piece(events: list[dict], duration: float, *, fast: bool = False,
                 reverb: bool = True, verbose: bool = True) -> np.ndarray:
    """把演奏事件表渲染成立体声波形。"""
    sr = SAMPLE_RATE
    total = int(duration * sr) + sr // 4
    left = np.zeros(total, dtype=np.float32)
    right = np.zeros(total, dtype=np.float32)


    n_partials = 4 if fast else _N_PARTIALS
    tail_cap = 1.1 if fast else _TAIL_CAP

    t0 = time.time()
    n_notes = len(events)
    for i, ev in enumerate(events, 1):
        wave = render_note(ev["midi"], ev["velocity"], ev["duration"],
                           n_partials=n_partials, tail_cap=tail_cap)
        start = int(ev["start"] * sr)
        end = min(total, start + len(wave))
        if end <= start:
            continue
        chunk = wave[: end - start]
        pan = float(np.clip(ev["pan"], -1.0, 1.0))

        gl = np.sqrt((1.0 - pan) * 0.5)
        gr = np.sqrt((1.0 + pan) * 0.5)
        left[start:end] += chunk * gl
        right[start:end] += chunk * gr
        if verbose and (i % 200 == 0 or i == n_notes):
            print(f"\r  合成音符 {i}/{n_notes} …", end="", flush=True)
    if verbose:
        print(f"\r  合成 {n_notes} 个音符，用时 {time.time() - t0:.1f}s")

    dry = np.stack([left, right], axis=1)
    if reverb:
        t0 = time.time()
        mono = (left + right) * 0.5
        left_wet = _reverb_fast(mono, sr, seed=20230401, spread=0.0)
        right_wet = _reverb_fast(mono, sr, seed=19700101, spread=1.7)
        rms_dry = float(np.sqrt(np.mean(mono ** 2))) or 1.0
        rms_wet = float(np.sqrt(np.mean(left_wet ** 2 + right_wet ** 2) * 0.5)) or 1.0
        gain = min(3.0, rms_dry / rms_wet)
        out = dry * 0.78 + np.stack([left_wet, right_wet], axis=1) * (0.40 * gain)
        if verbose:
            print(f"  混响用时 {time.time() - t0:.1f}s")
    else:
        out = dry

    peak = float(np.max(np.abs(out))) or 1.0
    out = out / peak * 0.86
    return out.astype(np.float32)


def _reverb_fast(mono: np.ndarray, sr: int, rt60: float = 3.6,
                 seed: int = 20230401, spread: float = 0.0) -> np.ndarray:
    """用 FFT 卷积做混响：噪声脉冲响应（指数衰减 + 早期反射 + 高频滚降）。

    比逐样本的 Schroeder 网络快得多，而且尾巴更自然。
    两只耳朵用两份不同的噪声（spread 略有偏移），混响因此自带立体声宽度。
    """
    n = len(mono)
    ir_len = int(rt60 * sr)
    rng = np.random.default_rng(seed)

    t = np.arange(ir_len) / sr
    decay = np.exp(-6.907755 * t / rt60)
    ir = rng.standard_normal(ir_len) * decay
    for delay_ms, gain in ((11.0, 0.62), (19.0, 0.48), (27.0, 0.40), (43.0, 0.32)):
        idx = int((delay_ms + spread) * sr / 1000.0)
        if idx < ir_len:
            ir[idx] += gain

    win = np.hanning(257)
    win /= win.sum()
    ir = np.convolve(ir, win, mode="same")
    ir[: int(0.006 * sr)] = 0.0
    ir /= np.max(np.abs(ir)) or 1.0

    nfft = 1 << max(1, (n + ir_len - 1).bit_length())
    wet = np.fft.irfft(np.fft.rfft(mono, nfft) * np.fft.rfft(ir, nfft), nfft)[:n]
    return np.nan_to_num(wet).astype(np.float32)


def list_devices() -> None:
    try:
        import sounddevice as sd
    except Exception:
        print("没装 sounddevice，无法列出设备（仍可用 --wav 导出后自己播放）")
        return
    default_out = sd.default.device[1]
    print("可用的输出设备：")
    for i, d in enumerate(sd.query_devices()):
        if d["max_output_channels"] > 0:
            mark = " <- 当前默认" if i == default_out else ""
            print(f"  [{i:>2}] {d['name']}  ({d['max_output_channels']}ch, "
                  f"{int(d['default_samplerate'])}Hz){mark}")


def play(audio: np.ndarray, sr: int, device: int | None = None,
         blocking: bool = True) -> None:
    try:
        import sounddevice as sd
    except Exception as exc:
        print(f"播放需要 sounddevice（{exc}）。可以改用 --wav 导出再自己播。")
        return
    sd.play(audio, sr, device=device, blocking=blocking)
    if blocking:
        sd.stop()


def export_midi(events: list[dict], path: Path, bpm: float = 78.0) -> None:
    """手写一个 SMF type-1 文件（不需要 mido）：右手/左手分成两个轨道。"""
    import struct

    TPQ = 480
    sec_per_tick = 60.0 / (bpm * TPQ)
    melody: list[tuple[int, int, int, int]] = []
    accomp: list[tuple[int, int, int, int]] = []
    for ev in events:
        tick = int(round(ev["start"] / sec_per_tick))
        dur = max(1, int(round(ev["duration"] / sec_per_tick)))
        vel = int(np.clip(ev["velocity"] * 127, 1, 127))
        row = (tick, ev["midi"], vel, dur)
        right_hand = ev.get("voice") in ("melody", "melody-double", "shimmer")
        (melody if right_hand else accomp).append(row)
    melody.sort()
    accomp.sort()

    def track_bytes(rows: list[tuple[int, int, int, int]]) -> bytes:
        msgs: list[tuple[int, int, bytes]] = []
        for tick, pitch, vel, dur in rows:
            msgs.append((tick, 1, bytes([0x90, pitch, vel])))
            msgs.append((tick + dur, 0, bytes([0x80, pitch, 0])))
        msgs.sort(key=lambda m: (m[0], m[1]))
        out = bytearray()
        prev = 0
        for tick, _, data in msgs:
            delta = tick - prev
            prev = tick
            out += _vlq(delta) + data
        out += _vlq(0) + b"\xff\x2f\x00"
        return bytes(out)

    header = b"MThd" + struct.pack(">IHHH", 6, 1, 2, TPQ)
    tempos = b"\x00\xff\x51\x03" + struct.pack(">I", int(60_000_000 / bpm))[:3]
    name = "Merry Christmas Mr. Lawrence"
    meta = b"\x00\xff\x03" + bytes([len(name)]) + name.encode()
    body = (
        b"MTrk" + struct.pack(">I", len(tempos + meta + track_bytes(accomp))) + tempos + meta + track_bytes(accomp)
        + b"MTrk" + struct.pack(">I", len(track_bytes(melody))) + track_bytes(melody)
    )
    path.write_bytes(header + body)
    print(f"已导出 MIDI：{path}（{len(events)} 个音符，2 个轨道）")


def _vlq(value: int) -> bytes:
    """MIDI 的可变长度量。"""
    if value < 0:
        value = 0
    buf = [value & 0x7F]
    value >>= 7
    while value:
        buf.append((value & 0x7F) | 0x80)
        value >>= 7
    return bytes(reversed(buf))


def show_score(events: list[dict], bpm: float, bars: int = 16) -> None:
    """在终端画一段钢琴卷帘，顺便当自检。"""
    print(f"\n和声进行（每小节一个和弦，4/4，♩={bpm:g}）：")
    for row_start in range(0, bars, 8):
        names = [f"{b:>3}" for b in range(row_start, min(bars, row_start + 8))]
        chords = [f"{chord_for_bar(b):>3}" for b in range(row_start, min(bars, row_start + 8))]
        print("  小节 " + " ".join(names))
        print("  和弦 " + " ".join(chords))

    beat = 60.0 / bpm
    print(f"\n钢琴卷帘（▉=右手 ◇=左手，每格 = 一个十六分音符，共 {bars} 小节）：")
    lo, hi = 45, 84
    for b in range(bars):
        grid = [[] for _ in range(hi, lo - 1, -1)]
        t0, t1 = b * 4 * beat, (b + 1) * 4 * beat
        for ev in events:
            s, e = ev["start"], ev["start"] + ev["duration"]
            if s >= t1 or (e <= t0 and s < t0 - 1e-9):
                continue
            if s < t0 - 1e-9:
                continue
            step = min(15, max(0, int((s - t0) / (t1 - t0) * 16)))
            idx = hi - ev["midi"]
            if 0 <= idx < len(grid):
                grid[idx].append((step, "▉" if ev.get("voice", "").startswith("melody") else "◇"))
        print(f"  ── 第 {b + 1} 小节 [{chord_for_bar(b)}] " + "─" * 10)
        for i, cells in enumerate(grid):
            if not cells:
                continue
            line = ["·"] * 16
            for step, ch in cells:
                if line[step] == "·" or ch == "▉":
                    line[step] = ch
            print(f"   {hi - i:>3} |{''.join(line)}|")


def main(argv: list[str] | None = None) -> int:
    p = argparse.ArgumentParser(
        description="用 Python 演奏坂本龙一《Merry Christmas Mr. Lawrence》",
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    p.add_argument("--bpm", type=float, default=66.0, help="速度，默认 66")
    p.add_argument("--wav", type=Path, nargs="?", const=PROJECT_DIR / "merry_christmas.wav",
                   help="把渲染结果存成 WAV（不给路径就用默认文件名）")
    p.add_argument("--midi", type=Path, help="导出 MIDI 文件")
    p.add_argument("--no-play", action="store_true", help="只渲染，不播放")
    p.add_argument("--open", action="store_true",
                   help="渲染后交给系统默认播放器打开（配合 --no-play 用）")
    p.add_argument("--device", type=int, help="输出设备编号（见 --list-devices）")
    p.add_argument("--list-devices", action="store_true", help="列出音频输出设备后退出")
    p.add_argument("--no-reverb", action="store_true", help="关掉混响")
    p.add_argument("--fast", action="store_true", help="粗渲染，速度快很多")
    p.add_argument("--score", action="store_true", help="在终端打印和声与钢琴卷帘")
    args = p.parse_args(argv)

    if args.list_devices:
        list_devices()
        return 0

    events, duration = build_piece(bpm=args.bpm)
    print(f"《Merry Christmas Mr. Lawrence》  ♩={args.bpm:g}  "
          f"{TOTAL_BARS} 小节（B 小调），{len(events)} 个音符，"
          f"约 {duration / 60:.1f} 分钟")

    if args.score:
        show_score(events, args.bpm)

    if args.midi:
        export_midi(events, args.midi, bpm=args.bpm)

    if args.no_play and not args.wav:
        return 0

    audio = render_piece(events, duration, fast=args.fast, reverb=not args.no_reverb)

    if args.wav:
        write_wav(args.wav, audio)
        size_mb = args.wav.stat().st_size / 1e6
        print(f"已写入 {args.wav}（{size_mb:.1f} MB，立体声 44.1kHz/16bit）")

    if args.open:
        target = args.wav or (PROJECT_DIR / "merry_christmas.wav")
        if not target.exists():
            write_wav(target, audio)
        import subprocess
        subprocess.Popen(["powershell", "-NoProfile", "-Command", f"Invoke-Item -LiteralPath '{target}'"])
        print(f"已交给系统默认播放器：{target}")

    if not args.no_play:
        print("♪ 开始播放…（Ctrl+C 停止）")
        try:
            play(audio, SAMPLE_RATE, device=args.device)
        except KeyboardInterrupt:
            try:
                import sounddevice as sd
                sd.stop()
            except Exception:
                pass
            print("\n已停止。")
            return 130
        print("♪ 演奏结束。")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())