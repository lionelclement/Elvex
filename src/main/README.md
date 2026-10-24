# ELVEX implementation

This directory contains the C++11 implementation of the ELVEX natural-language generation engine.

Key source areas include `generator.*` for the generation process, `rule.*` and `rules.*` for grammar rules, `feature.*` and `features.*` for feature structures, `forest.*` and `node.*` for shared derivation forests, and the `compacted-lexicon-*` files for lexical storage and lookup. `ruleslex.l` and `rulesyacc.y` are the Flex and Bison parser inputs; the `postedition_*.l` files define the language-specific post-editors.

Do not edit generated lexer/parser C++ files. Use the top-level [CMake build](../../CMakeLists.txt), then run the [regression tests](../test/README.md). See [INSTALL.md](../../INSTALL.md) for the required tools.
