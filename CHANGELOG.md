# Historique des versions

## 2.28.0 — 23 octobre 2026

Évolution fonctionnelle et consolidation de la distribution source, sans changement du format des règles annoncé.

- **Performances** : réduction des reprises inutiles de `SHIFT` et cache des recherches lexicales compactées, activé par défaut et désactivable via `ELVEX_LEXICON_CACHE=0`. Préservation des sorties vérifiée sur les jeux de régression.
- **Génération** : option `--forest-only` pour construire la forêt partagée sans énumérer les phrases ; suivi de progression facultatif avec `--progress` sur `stderr` ; export XML disponible selon la configuration de compilation.
- **Fiabilité** : correction de la fusion entre lexique classique et lexique compacté, évitant la modification des listes partagées du parseur.
- **Organisation** : `src/main/` pour le moteur, `src/test/` pour les tests, `data/regression/` et `data/examples/` pour les ressources ; `CMakeLists.txt` reste à la racine ; génération Flex/Bison et objets dans `build/`.
- **Non-régression** : 42 scénarios comparés aux sorties attendues avec cache activé et désactivé, plus un test de la forêt et de la progression (**85 tests CTest**).
- **Distribution** : documentation d'installation, archive source épurée et manifeste de vérification SHA-256.

**Validation** : 85/85 tests réussis sur macOS (AppleClang 15, Flex 2.6.4, Bison 2.3) après migration et nettoyage ; voir `SOURCE-DISTRIBUTION.md` pour le périmètre du contrôle Linux.

## 2.27.0 — version antérieure

Version de référence avant la réorganisation du dépôt et les optimisations de génération décrites ci-dessus.
