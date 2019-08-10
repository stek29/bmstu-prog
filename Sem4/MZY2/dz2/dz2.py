import sys
import re
import json


class Arr:
    signed = None
    volatility = None
    typ = None
    name = None
    dimensions = None
    values = None

    def __repr__(self):
        return '\n'.join((
            f'Sig: {self.signed}',
            f'Vol: {self.volatility}',
            f'Typ: {self.typ}',
            f'Nam: {self.name}',
            f'Dim: {self.dimensions}',
            f'Val: {self.values}',
        ))


EXPR_REGEX = re.compile(r"""
^\s*
(?:(?P<volatility>const|volatile)\s+)?
(?:(?P<sign>signed|unsigned)\s+)?
(?P<type>int)\s+
(?P<name>[a-zA-Z]\w*)
(?P<dimensions>(?:\s*\[\d*\])+)
(?:
\s*=\s*
(?P<value>[{},\d+\s-]*)
)?
\s*;\s*$
""", flags=re.I | re.X)


def parse_dimensions(d):
    m = re.findall(r'\[(\d*)\]', d)
    if not m:
        raise Exception('Failed to parse dimensions')
    return [int(v) if v else '*' for v in m]


def parse(text, start=0):
    res = []
    i = start
    while i < len(text):
        c = text[i]
        i += 1

        if c == '{':
            v, i = parse(text, i)
            res.append(v)
        elif c == ',':
            pass
        elif c == '}':
            break
        else:
            l = re.search(r'[^\d+-]', text[i:]).start()
            res.append(int(text[i-1:i+l]))
            i = i+l

    return res, i


def parse_values(v):
    if not v:
        return None
    v = re.sub(r'[^{},\d+-]', '', v)
    print(v)
    return parse(v)[0][0]


def process(line):
    m = EXPR_REGEX.match(line)
    if m is None:
        raise Exception('Invalid expression')

    d = m.groupdict()
    arr = Arr()
    arr.volatility = d['volatility']
    arr.signed = d['sign'] != 'unsigned'
    arr.typ = d['type']
    arr.name = d['name']
    arr.dimensions = parse_dimensions(d['dimensions'])
    arr.values = parse_values(d['value'])

    return arr


if __name__ == '__main__':
    for line in sys.stdin:
        line = line.strip()
        print(line)

        try:
            arr = process(line)
            print(arr)
        except Exception as e:
            print('Invalid expression:', str(e))
