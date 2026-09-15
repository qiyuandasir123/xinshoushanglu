import glob, json, re, os

folder = r'c:\Users\jianan\AppData\Roaming\Code\User\workspaceStorage\00d710014f0ead9c6c57d81c5a0fc8af\GitHub.copilot-chat\chat-session-resources\fea7f933-017d-45a7-b993-66bc8cf050d3'
seen = set()
results = []
for f in glob.glob(os.path.join(folder, '*')):
    try:
        with open(f, encoding='utf-8') as fh:
            content = fh.read()
        m = re.search(r'\[.*\]', content, re.S)
        if m:
            arr = json.loads(m.group())
            for e in arr:
                if e['id'] not in seen:
                    seen.add(e['id'])
                    results.append((e['id'], e['name'][:70], e.get('installCount',''), e.get('rating','')))
    except Exception as ex:
        results.append(('ERROR', str(ex), '', ''))

for r in results:
    print(' | '.join([str(x) for x in r]))
