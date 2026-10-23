# Publication d'une version ELVEX

## Vérifications avant publication

Depuis une copie propre des sources :

```sh
cmake -S . -B build
cmake --build build --parallel 8
ctest --test-dir build --output-on-failure
./build/bin/elvex --version
./build/bin/elvexlexicon --version
```

Les deux commandes `--version` doivent afficher `2.28.0` et CTest doit afficher **85/85 tests réussis**.

## Vérifier l'archive

Depuis la racine décompressée : `shasum -a 256 -c SHA256SUMS` sur macOS ; sous Linux : `sha256sum -c SHA256SUMS`.

## Git (sur le dépôt original, après intégration du patch)

```sh
git status --short
git add CMakeLists.txt README.md INSTALL.md SOURCE-DISTRIBUTION.md FINALISATION_NORMALISATION.md doc/doc-en.tex CHANGELOG.md RELEASING.md
git commit -m 'Release ELVEX 2.28.0'
git tag -a v2.28.0 -m 'ELVEX 2.28.0'
# Après vérification du dépôt distant et avec votre accord :
# git push origin <branche>
# git push origin v2.28.0
```

Un tag Git **n'est pas créé automatiquement** par l'archive. La publication distante doit être réalisée séparément par le mainteneur.
