# Finalisation de la normalisation PASS / UNFOLD

## Correctif conserve

Les items qui portent un terme optionnel (`PASS`) ou une alternative (`UNFOLD`) restent
presents comme temoins de normalisation. Une branche n'est recreee que si les donnees
pertinentes ont change depuis leur derniere propagation :

- references entrantes ;
- contraintes d'ordre ;
- contenu des quatre structures de traits (↑, ↓, ⇑, ⇓).

Les structures de traits sont comparees au moyen d'une signature reconstruite sur
une copie profonde, afin de detecter egalement les mutations internes apres
mise en cache d'une serialisation.

Les traces ponctuelles `ELVEX_PASS_DIAGNOSTICS`, `ELVEX_CYCLE_DIAGNOSTICS`,
`[PASS-DETAIL]`, `[CYCLE]` et les impressions inconditionnelles de fichier/ligne
ont ete retirees. Les diagnostics de redondance et metriques experimentales
preexistants ont ete preserves.

## Tests

Depuis la racine du projet :

```sh
sh tests/run_optional_late_features.sh
```

Apres une construction CMake avec CTest :

```sh
ctest --test-dir build --output-on-failure
```

Pour la generation avec la grammaire anglaise (depuis `test/`, si
`En-1.0` est installee, et avec `elvex` et `elvexlexicon` dans le PATH) :

```sh
make DATA=En-1.0
```

Les anciens repertoires de reproduction exploratoire ont ete retires de
`test/`. Les tests permanents sont `test/run-regression.sh` et
`tests/run_optional_late_features.sh`, egalement enregistres dans CTest.

ATTENTION : `MAX_TIME` est une option interne au generateur, non un delai
systeme. Utiliser `gtimeout` sur macOS pour imposer un delai externe, si besoin.

## Validation effectuee sur la version nettoyee

- Compilation complete de `elvex` et de `elvexlexicon` : OK (GCC 14, C++17, Linux).
- Verification syntaxique C++11 de `generator.cc` et `item.cc` : OK.
- Tests de propagation tardive : 17 controles passes.
- Suite `test/run-regression.sh` : 41 cas passes, y compris le lexique compacte.
- Cas minimaux exploratoires avec constituants optionnels : termines avec code 0 avant retrait de ces dossiers temporaires.
- Test `En-1.0` : termine avec code 0 ; produit notamment
  `present:  John uses Elvex.` et `present:  John uses the elvex.`

Ce correctif est valide sur ces essais, sans garantie d'absence de regressions
sur toutes les grammaires possibles. Le projet reste en version 2.27.0 ;
aucune nouvelle version officielle n'est annoncee dans cet ensemble.

## Notes de distribution

Cette archive source n'inclut pas l'historique `.git`, les dossiers de build,
les binaires, les journaux volumineux, les caches et les projets locaux ignores
par `.gitignore` (notamment `motiflow-poc/`). La configuration PHP locale
`elvex-www/config/config.php` n'est pas incluse ; son exemple `.ini` est conserve.
Le patch associe permet aussi de modifier le projet d'origine sans supprimer
ses autres fichiers.
