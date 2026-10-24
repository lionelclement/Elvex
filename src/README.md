# ELVEX source code

The `src/` directory contains the C++ engine and the test harness.

- [Main engine](main/README.md) — generators, feature structures, lexicon compilation, parser definitions, and post-editors.
- [Tests](test/README.md) — CTest registration, regression scripts, and expected-output conventions.

The supported build entry point is the top-level [CMakeLists.txt](../CMakeLists.txt), not an in-source build. See [INSTALL.md](../INSTALL.md) for the build requirements and commands.
