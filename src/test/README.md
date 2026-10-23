# Suite de non-régression ELVEX

- `CMakeLists.txt` : enregistre **85 contrôles** sous CTest.
- `run-regression.sh` : compare chaque sortie générée aux `.expected` de `data/regression`,
  en conservant les doublons et en ignorant seulement l'ordre des lignes.
- `check-forest.sh` : vérifie que `--forest-only` construit un XML non vide,
  ne produit pas de phrases et signale la fin via `--progress` sur `stderr`.

42 corpus sont testés **avec** et **sans** cache lexical (84 contrôles),
plus un test de la forêt partagée.

Le nouveau cas `42_mixed_compacted_lexicon` vérifie la coexistence du lexique
classique et du lexique compacté pour une même clé `(POS, HEAD)`.

Les temps de calcul ne constituent pas des critères de réussite de cette suite :
les performances peuvent être suivies dans des benchmarks séparés.

Ajouter un cas : créer dans `data/regression/` un même préfixe de fichier avec
`.rules`, `.lexicon`, `.input` (ou `.stdin`) et `.expected`. Les fichiers `.macros`,
`.morpho` et `.pattern` sont facultatifs, mais `.morpho` et `.pattern` vont par paire.
Relancer `cmake -S . -B build` (ou reconfigurer automatiquement CMake récent).
