# Organisation des sources et des non-régressions

```text
Elvex/
├── CMakeLists.txt              # configuration de compilation À LA RACINE
├── src/
│   ├── main/                   # moteur ELVEX (C++, Flex/Bison)
│   └── test/                   # scripts et déclaration CTest
├── data/
│   ├── regression/             # entrées + sorties de référence (42 cas)
│   └── examples/               # grammaires et corpus historiques
├── doc/                        # documentation existante
└── build/                      # généré par CMake, non versionné
    ├── bin/
    └── generated/
```

`src/main` : uniquement du code. `src/test` : logique des tests. `data` :
seulement des ressources d'entrée et des résultats attendus.

La suite CTest enregistre **chaque cas** deux fois : cache lexical désactivé
(`ELVEX_LEXICON_CACHE=0`) et activé (`=1`). Les résultats sont comparés au
fichier `.expected`, avec tri des lignes complètes et conservation des doublons.

La comparaison ne repose **pas sur les temps d'exécution**, qui dépendent de
la machine. Un test dédié contrôle `--forest-only`, l'export XML et la
progression sur `stderr`.

## Utilisation

```bash
cmake -S . -B build
cmake --build build -j 8
ctest --test-dir build --output-on-failure
ctest --test-dir build -R '^regression.31_' --output-on-failure
make -C data/examples DATA=Animal run
```

## Points de migration

- Le `Makefile` généré par une ancienne compilation **dans la racine** n'est
  pas un fichier source. Ne pas le réutiliser après déplacement des sources.
- Après réorganisation, régénérer CMake avec `cmake -S . -B build`.
- `test/run-regression.sh` → `src/test/run-regression.sh` ;
  `test/regression/` → `data/regression/` ;
  `test/<exemple>/` → `data/examples/<exemple>/`.
- Les sources générées par Flex/Bison et `config.hpp` vont dans
  `build/generated/`, pas dans `src/main`.
- Ne pas déplacer les fichiers `.elvex-build`, `.fsa`, `.tbl`, `.o`, les
  journaux ou les exécutables vers les données versionnées.

La migration est fournie comme **arborescence propre**, afin d'éviter les
modifications destructrices dans un dépôt existant. Avant de remplacer le
projet, comparer les fichiers C++ avec la branche de travail locale.

## Anciennes commandes conservées

```sh
make -f Makefile.test test
```

Les anciens tests individuels `.test` restent archivés dans `data/examples/` ;
la suite CTest fait foi pour la non-régression.

## Migrer sans remplacer les sources actuelles

Depuis un dépôt **historique** (après avoir commité les modifications courantes) :

```sh
python3 /chemin/du/kit/migrate-layout.py .          # aperçu, sans écriture
python3 /chemin/du/kit/migrate-layout.py --apply .  # migration
cmake -S . -B build
cmake --build build -j 8
ctest --test-dir build --output-on-failure
```

Le script **déplace les sources C++ existantes**, il ne les remplace pas par
celles de l'archive ; il refuse de remplacer un `CMakeLists.txt` différent de
celui reçu dans `Elvex(5).zip`. Il crée une sauvegarde des Makefiles originaux
dans `.elvex-layout-backup/` et laisse les anciens fichiers générés sur place.
