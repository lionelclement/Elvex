# Circus fix8

Cette version vise à rendre `900_circus_sax_clarinet_brass_perc.input` moins répétitif et moins attaché à do majeur.

## Changements

- tonalité de l'exemple : `f major` au lieu de `c major` ;
- `notation:[accidental_policy:flat]`, plus naturel pour fa majeur et l'écriture de fanfare ;
- tempo proposé : `bpm:108`, plus vivant que 96 mais beaucoup moins rapide que 168 ;
- `circus.rules` réécrit avec une trajectoire harmonique lisible :
  - A : I / question ;
  - A' : V / réponse ;
  - B : IV + couleur bVII ;
  - cadence : V-I ;
- les rôles restent génériques : `lead`, `countermelody`, `harmonic_support`, `accent`, `bass`, `rhythmic_pedal` ;
- les motifs sont relatifs à `tonic_pc`, donc pas ad hoc à do majeur ;
- les variantes aléatoires utilisent des règles alternatives avec `attest rand()%100 ...`, toujours suivies d'un fallback.

## Test

```bash
rm -f 900_circus_sax_clarinet_brass_perc.ly
make 900_circus_sax_clarinet_brass_perc.ly
make 900_circus_sax_clarinet_brass_perc.pdf
```

Pour un résultat reproductible :

```bash
elvex --seed 17 --rules-file music.rules --lexicon-file music.lexicon --input-file 900_circus_sax_clarinet_brass_perc.input -f > 900_circus_sax_clarinet_brass_perc.ly
```
