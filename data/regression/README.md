# Données de tests de non-régression

Chaque test est identifié par un préfixe `NN_nom` :

- `.rules` : grammaire
- `.lexicon` : lexique classique
- `.input` ou `.stdin` : entrée du générateur
- `.expected` : sortie attendue **versionnée**
- `.stderr` : éventuellement, messages attendus sur stderr
- `.macros`, `.morpho`, `.pattern` : éventuellement, lexique compacté

Ne pas régénérer automatiquement les `.expected` lors de l'exécution des tests.
Le cas `42_mixed_compacted_lexicon` vérifie la fusion des lexiques.
