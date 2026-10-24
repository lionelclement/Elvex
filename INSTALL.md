# Install ELVEX from source

These instructions apply to the current repository layout (ELVEX **2.28.0**), including GitHub's **Code → Download ZIP** archive. Builds take place in a separate `build/` directory.

## Prerequisites

- **CMake 3.12 or newer**
- A **C++11** compiler (for example, AppleClang, Clang, or GCC)
- **Flex** and **Bison**, used to generate scanners and parsers
- **libxml2** headers and library, required by the CMake configuration
- **Bash** and **Perl** for the regression tests; standard Unix utilities including `sort` and `diff`
- **Make** for the optional example Makefiles; GNU Make 4.3 or newer is recommended for the shared example Makefile

On Debian/Ubuntu-like systems, typical development packages include `build-essential`, `cmake`, `flex`, `bison`, `libxml2-dev`, and `perl`. On macOS, the build requires command-line developer tools plus CMake, Flex, Bison, and libxml2; ensure CMake can discover the installed versions.

LilyPond is optional and only used by the music-generation examples. The browser-based web interface has its own deployment requirements.

## Obtain the source

```sh
git clone https://github.com/lionelclement/Elvex.git
cd Elvex
```

Alternatively, download the GitHub ZIP archive and open a terminal in the extracted directory (the directory containing `CMakeLists.txt`).

## Configure and compile

```sh
cmake -S . -B build
cmake --build build --parallel 8
```

Executables are placed in `build/bin/`:

```sh
./build/bin/elvex --version
./build/bin/elvexlexicon --version
```

Both should report `2.28.0` for this source version. The two post-editing tools are also built in `build/bin/`.

The build does **not** require `sudo` or a system-wide installation. If you explicitly want to install binaries to a system prefix, first configure CMake with an appropriate `-DCMAKE_INSTALL_PREFIX=...`, then run `cmake --install build`.

## Run the tests

```sh
ctest --test-dir build --output-on-failure
```

For this version, the expected suite contains **85 CTest tests**: 42 regression cases checked with and without the lexicon cache, plus one forest/progress test.

```sh
ctest --test-dir build -N
ctest --test-dir build -R 'regression.31_animal_compacted_lexicon' --output-on-failure
```

The test fixtures and instructions for adding cases are in [src/test/README.md](src/test/README.md).

## Try the included grammar

From the repository root:

```sh
make -C data/examples DATA=french-animal-calls run
```

This builds the French animal calls example's `.fsa` / `.tbl` lexicon files under its `.elvex-build/` directory and runs the generator. See [data/examples/french-animal-calls/README.md](data/examples/french-animal-calls/README.md).

## Troubleshooting

- **Flex or Bison not found:** install the development tools and re-run `cmake -S . -B build`.
- **libxml2 not found:** install its development package and make it visible to CMake.
- **Stale build configuration:** remove the local `build/` directory and reconfigure; do not reuse a previous in-source `Makefile` or `CMakeCache.txt`.
- **`elvex: command not found` in an example:** the shared Makefile uses `build/bin/` by default; for the music examples, provide `ELVEX=/absolute/path/to/build/bin/elvex` if the executable is not on `PATH`.
- **Test failure:** use `ctest --test-dir build --output-on-failure` and inspect the failing fixture in `data/regression/`.
