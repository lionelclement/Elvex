# music_pop_didactic — version simple et bornée

Cette archive corrige l'erreur :

```text
*** fatal error: too much items build : 12001 (12000 Max)
```

La cause était que la première archive réutilisait plusieurs gros modules historiques
(`role_ensemble.rules`, `staves.rules`, `bars.rules`) contenant de nombreuses formes
anciennes. Même avec un exemple pop simple, Elvex devait ouvrir trop d'items.

Cette version garde seulement :

- `music.rules`
- `pop_didactic.rules`
- `music.lexicon`
- `common.lexicon`
- `chords.lexicon`
- `Makefile`
- 4 fichiers `.input`

Le fichier principal est `pop_didactic.rules`. Il contient :

1. la construction LilyPond minimale ;
2. les portées pour des ensembles de 4, 6, 7 ou 9 instruments ;
3. le routage par rôle musical ;
4. une forme pop de 16 mesures ;
5. des cellules tonales simples ;
6. les règles de conversion degré relatif -> note absolue.

La grammaire reste volontairement didactique : elle décrit des rôles musicaux
(`lead`, `guitar`, `bass`, `drums`, `brass_punch`, etc.), pas des morceaux ad hoc.

## Compiler

```bash
make list
make ly
make pdf
```

Pour un seul exemple :

```bash
make 001_chanson_francaise_voix_guitare_djembe.ly
make 001_chanson_francaise_voix_guitare_djembe.pdf
```

## Tracer

```bash
make trace-001
open log.html
```

ou :

```bash
elvex --trace-all \
  --rules-file music.rules \
  --lexicon-file music.lexicon \
  --input-file 001_chanson_francaise_voix_guitare_djembe.input \
  -f > log.html
```


## fix2

Cette version ajoute explicitement un attribut synthétisé `⇑=[];` à chaque règle qui ne renvoie pas déjà de structure. C’est volontairement verbeux mais plus sûr pour Elvex : chaque réduction peut se fermer proprement même si le parent n’utilise pas de traits synthétisés.

## fix3 — piano_lh / keyboard_lh à l'octave 2

Cette archive corrige aussi le cas où les exemples `002_english_pop_piano_band.input`
et `004_refrain_pop_avec_cuivres.input` ne produisaient aucun `.ly`.

Cause : les rôles `piano_lh` et `keyboard_lh` utilisent des basses à l'octave 2,
mais certaines mesures de main gauche sont des accords plaqués. Le lexique
`chords.lexicon` commence ses accords à l'octave 3. Les anciennes règles
`LH_I_CHORDS`, `LH_V_CHORDS` et `LH_IV_CHORDS` appelaient `CHORD4`, qui
cherchait des accords à l'octave 2 et échouait silencieusement.

Correction : ajout de `LH_CHORD4`, qui conserve les basses à l'octave donnée
mais place les accords de main gauche à `$oct+1`.

