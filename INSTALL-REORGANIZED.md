# Installation et tests (arborescence réorganisée)

La configuration **CMake reste à la racine** du projet. La compilation se fait hors des sources.

Prérequis : CMake, compilateur C++11, Flex, Bison, libxml2 ; Bash et Perl pour les tests.

```sh
cmake -S . -B build
cmake --build build --parallel 8
ctest --test-dir build --output-on-failure
```

Les exécutables sont dans `build/bin/`.

Tests individuels :

```sh
ctest --test-dir build -N
ctest --test-dir build -R '^regression.31_animal_compacted_lexicon.' --output-on-failure
ctest --test-dir build -R 'regression.forest.progress' --output-on-failure
```

Lancer directement les **42 cas historiques** dans les deux modes de cache :

```sh
ELVEX_LEXICON_CACHE=0 bash src/test/run-regression.sh ./build/bin/elvex ./build/bin/elvexlexicon
ELVEX_LEXICON_CACHE=1 bash src/test/run-regression.sh ./build/bin/elvex ./build/bin/elvexlexicon
```

Pour les exemples :

```sh
make -C data/examples DATA=Animal run
make -C data/examples DATA=En-1.0 run
```

Les fichiers de référence des régressions (`.expected`) restent **versionnés** ; les fichiers
compilés (`.fsa`, `.tbl`), sorties et journaux restent non versionnés.

**Note de compatibilité :** l’ancien `Makefile.test` et ses exemples historiques
ont été placés séparément de CTest. Les scripts référencés par les anciens chemins
`test/...` doivent être adaptés ; voir `MIGRATION.md`.
