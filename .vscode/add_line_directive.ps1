#requires -version 5
<#
    fix-line: add a "#line" directive on line 1 of a C source file so that
    breakpoints work even if the file name contains non-ASCII characters.

    WHY THIS IS NEEDED
      gcc receives the source file name from the Windows command line as
      ANSI(CP936) bytes and writes those raw bytes into the debug info (GBK).
      VS Code / cpptools sends the file name to gdb or lldb as UTF-8, and the
      debugger compares the two byte-by-byte -> mismatch -> the breakpoint
      silently fails (grey hollow circle, program runs to the end).

      The file name inside a "#line" directive is just a string: gcc never
      opens it. It is copied into the debug info exactly as it appears in the
      (UTF-8) source file, which matches what VS Code sends.
      "#line 2" is used so that physical line numbers stay equal to reported
      line numbers, i.e. breakpoint positions in VS Code do not shift.

    USAGE
      powershell -NoProfile -ExecutionPolicy Bypass -File add_line_directive.ps1 <file.c>

    IMPORTANT: KEEP THIS FILE PURE ASCII - see the note at the end of the file.
#>
param(
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$Path
)

$ErrorActionPreference = 'Stop'

if (-not (Test-Path -LiteralPath $Path -PathType Leaf)) {
    Write-Host "[fix-line] not found: $Path" -ForegroundColor Red
    exit 1
}

$full = (Resolve-Path -LiteralPath $Path).Path
$name = Split-Path $full -Leaf

# Pure-ASCII path: the debugger already matches, nothing to do.
if ($full -match '^[\x20-\x7E]+$') {
    Write-Host "[fix-line] skip (ASCII path): $name"
    exit 0
}

# The file must decode as UTF-8, otherwise the directive is not written as UTF-8.
$bytes = [IO.File]::ReadAllBytes($full)
$hasBom = ($bytes.Length -ge 3 -and $bytes[0] -eq 0xEF -and $bytes[1] -eq 0xBB -and $bytes[2] -eq 0xBF)
try {
    $text = (New-Object Text.UTF8Encoding($false, $true)).GetString($bytes)
    $enc = New-Object Text.UTF8Encoding($hasBom)
}
catch {
    Write-Host "[fix-line] skip (not valid UTF-8): $name" -ForegroundColor Yellow
    Write-Host "           In VS Code use the status bar encoding picker -> Save with encoding -> UTF-8." -ForegroundColor Yellow
    exit 1
}

# Keep the original line ending style.
$nl = if ($text.Contains("`r`n")) { "`r`n" } else { "`n" }
$lines = [System.Collections.Generic.List[string]]($text -split "`r?`n")

# Use the FULL path, with backslashes escaped for the C string.
#   * the debug info then holds the same UTF-8 bytes VS Code sends -> exact match
#   * compiler diagnostics keep the full path, so the VS Code Problems panel
#     can still jump to the file (a bare file name would resolve against the
#     workspace root and point at nothing)
$want = '#line 2 "' + $full.Replace('\', '\\') + '"'

if ($lines[0].Trim() -eq $want) {
    Write-Host "[fix-line] already OK: $name"
    exit 0
}
elseif ($lines[0].Trim() -match '^#line\s+\d+\s+"') {
    $lines[0] = $want
    $action = 'updated'
}
else {
    $lines.Insert(0, $want)
    $action = 'inserted'
}

[IO.File]::WriteAllText($full, ($lines -join $nl), $enc)
Write-Host "[fix-line] $action line 1 -> $want" -ForegroundColor Green

# ---------------------------------------------------------------------------
# KEEP THIS FILE PURE ASCII. DO NOT ADD CHINESE TEXT TO IT.
#   Windows PowerShell 5.1 reads a script that has no UTF-8 BOM using the ANSI
#   code page (936 on this machine). Any non-ASCII literal in the file then
#   becomes garbage and the script fails with
#       "The string is missing the terminator: '"
#   Keeping the file pure ASCII makes it work no matter which encoding is
#   assumed, so it can never break again after an edit or a re-save.
# ---------------------------------------------------------------------------
