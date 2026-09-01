from pathlib import Path
import re, sys

root = Path(__file__).resolve().parent
required = [
    'en.rules','en-sentence.rules','en-normalize.rules','en-noun.rules','en-verb.rules','en-copula.rules',
    'en-tense.rules','en-modal.rules','en.pattern','en.morpho','en.lexicon','en.macros','en.stdin'
]
errors=[]
for f in required:
    if not (root/f).exists(): errors.append(f'missing {f}')

master=(root/'en.rules').read_text(encoding='utf-8')
includes=re.findall(r'^#include\s+(\S+)', master, re.M)
for f in includes:
    if not (root/f).exists(): errors.append(f'include target missing: {f}')

# Crude delimiter checks, good enough to catch generator/edit accidents.
for f in [p for p in root.glob('*.rules')]+[root/'en.lexicon',root/'en.macros']:
    s=f.read_text(encoding='utf-8')
    if s.count('{') != s.count('}'): errors.append(f'{f.name}: unbalanced braces')
    if s.count('[') != s.count(']'): errors.append(f'{f.name}: unbalanced brackets')

tr=(root/'en-tense.rules').read_text(encoding='utf-8')
mr=(root/'en-modal.rules').read_text(encoding='utf-8')
if tr.count('TenseClause →') != 48:
    errors.append(f'en-tense.rules: expected 48 TenseClause productions, got {tr.count("TenseClause →")}')
if mr.count('ModalClause →') != 16:
    errors.append(f'en-modal.rules: expected 16 ModalClause productions, got {mr.count("ModalClause →")}')
cr=(root/'en-copula.rules').read_text(encoding='utf-8')
if cr.count('TenseClause →') != 8:
    errors.append(f'en-copula.rules: expected 8 simple-copula TenseClause productions, got {cr.count("TenseClause →")}')

lex=(root/'en.lexicon').read_text(encoding='utf-8')
for modal in 'can could may might must shall should will would'.split():
    if not re.search(rf'^{modal}\s+aux_modal\b', lex, re.M): errors.append(f'modal missing: {modal}')

inp=(root/'en.stdin').read_text(encoding='utf-8')
if len(re.findall(r'^Axiom\s+\[', inp, re.M)) < 90:
    errors.append('en.stdin: unexpectedly small regression corpus')

if errors:
    print('STATIC VALIDATION FAILED')
    for e in errors: print('-',e)
    sys.exit(1)
print('STATIC VALIDATION OK')
print('includes:', ', '.join(includes))
print('tense rules:', tr.count('TenseClause →'))
print('simple copula rules:', cr.count('TenseClause →'))
print('modal rules:', mr.count('ModalClause →'))
print('input cases:', len(re.findall(r'^Axiom\s+\[', inp, re.M)))
