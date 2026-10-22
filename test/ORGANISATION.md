# Organisation des tests Elvex

Les exemples historiques auparavant placés directement dans `test/` sont désormais regroupés par famille :

- `test/Adj/`, `test/Base/`, `test/BigLexicon/`, `test/Comb1/`, `test/Comb2/`,
  `test/Disjunction1/`, `test/Disjunction2/`, `test/Embeded/`, `test/Environment/`,
  `test/FreeLinkedVariables/`, `test/IfPos/`, `test/InheritedSynthesized/`,
  `test/Lightness/`, `test/NP/`, `test/order-partial/`, `test/syntax-2/` ;
- `test/Adj/variants/` contient les variantes de règles d'ordre, **sans modifier** `Adj.rules` ;
- `test/music/exemples-historiques/music.txt` conserve l'ancien exemple musical ;
- `test/music/variantes-historiques/formal_long_forms.rules` et
  `test/music_pop_didactic/variantes-historiques/pop_didactic.rules` conservent les variantes distinctes des règles déjà présentes (sans écrasement) ;
- les copies **strictement identiques** de `common.lexicon`, `music.rules` et `music.lexicon` situées à l'ancienne racine ont été supprimées. Les exemplaires utilisés sous `music/` ou `music_pop_didactic/` restent présents.

Les extensions originales `.input`, `.stdin`, `.test` et `.output` sont conservées.

## Lancer un exemple

Depuis `test/`, le Makefile accepte les entrées `.input` **ou** `.stdin` :

```sh
cd test
make DATA=Base run
make DATA=syntax-2 run
make DATA=En-1.0 run
```

Il faut disposer des exécutables `elvex` et éventuellement `elvexlexicon` sur le `PATH`.

## Tests d'intégration

Depuis la racine du dépôt :

```sh
make -f Makefile.test test
bash test/run-regression.sh ./bin/elvex ./bin/elvexlexicon
```

`Makefile.test` parcourt maintenant les fichiers `test/<suite>/*.test`, sans essayer d'exécuter les nombreux exemples musicaux indépendants. La suite `test/regression/` reste pilotée par `test/run-regression.sh` et CTest ; elle n'a pas été déplacée.

Remarque : les fichiers `.output` déjà fournis servent de résultats d'exemple ; si une exécution doit forcer leur reconstruction, supprimer le `.output` ciblé ou utiliser `make -B -f Makefile.test test`.
