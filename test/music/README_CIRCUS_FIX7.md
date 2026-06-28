# Circus fix7

Cette version remplace la tentative `fix6` par une variante plus prudente.

## Principes

- pas de règles `direct` ni de blocs LilyPond complets par instrument ;
- fonctions musicales génériques : `lead`, `countermelody`, `harmonic_support`, `accent`, `bass`, `rhythmic_pedal` ;
- forme commune de 8 mesures : A, A', B, cadence ;
- cellules motiviques explicites : appel, réponse, contraste, cadence, basse oom-pah, percussion de marche ;
- variation par règles alternatives avec `attest rand() % 100`, toujours suivies d'une règle de repli non aléatoire.

## Pourquoi corriger fix6 ?

`fix6` mettait de gros blocs `if / else if / else` à l'intérieur des cellules. Même si la syntaxe peut être acceptée, cela rend la dérivation fragile. Ici, chaque variante est une règle autonome : si le guard aléatoire échoue, Elvex peut passer à la règle suivante.

## Test

```bash
rm -f 900_circus_sax_clarinet_brass_perc.ly log.txt
make 900_circus_sax_clarinet_brass_perc.ly
```

Debug reproductible :

```bash
elvex \
  --seed 17 \
  --rules-file music.rules \
  --lexicon-file music.lexicon \
  --input-file 900_circus_sax_clarinet_brass_perc.input \
  -f > 900_circus_sax_clarinet_brass_perc.ly \
  2> elvex_circus.err
```

Trace HTML :

```bash
elvex \
  --seed 17 \
  --trace-all \
  --rules-file music.rules \
  --lexicon-file music.lexicon \
  --input-file 900_circus_sax_clarinet_brass_perc.input \
  -f > log.html
```
