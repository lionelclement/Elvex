# Circus tonal fix9

Cette version remplace la fanfare trop dense par une phrase tonale de 8 mesures.

## Principe musical

Forme : période de 8 mesures en 2/4.

- Mesures 1-4 : antécédent, I - V - I - V, demi-cadence.
- Mesures 5-8 : conséquent, IV - ii/V - V - I, cadence parfaite.

Les règles imposent :

- notes d'accord sur les temps forts ;
- passages conjoints seulement dans la mélodie ;
- basse fonctionnelle par fondamentales ;
- contre-mélodie espacée ;
- cuivres en ponctuation, non en doublure permanente ;
- percussion moins dense.

Le fichier `900_circus_sax_clarinet_brass_perc.input` est en si bémol majeur,
`bpm:96`, avec `form:circus_tonal_period_8`.

## Compilation

```bash
make 900_circus_sax_clarinet_brass_perc.ly
make 900_circus_sax_clarinet_brass_perc.pdf
```

Pour une version reproductible :

```bash
elvex --seed 17 --rules-file music.rules --lexicon-file music.lexicon \
  --input-file 900_circus_sax_clarinet_brass_perc.input -f \
  > 900_circus_sax_clarinet_brass_perc.ly
```
