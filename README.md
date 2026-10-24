# ELVEX — Constraint-based natural language generation

**ELVEX** is a rule-based natural language generation (NLG) engine written in C++11. It generates text from a structured input (a *feature structure*) using grammars and lexicons explicitly written for the application. It does not train a statistical language model or require a training corpus.

The name ELVEX refers to the software, its generation algorithm, the grammar-description language, and the associated linguistic formalism.

## Quick start

Download this repository with Git, or use **Code → Download ZIP** on GitHub and extract it. You need a C++ compiler, CMake, Flex, Bison, and the libxml2 development files; see [INSTALL.md](INSTALL.md) for platform notes.

```sh
git clone https://github.com/lionelclement/Elvex.git
cd Elvex
cmake -S . -B build
cmake --build build --parallel 8
ctest --test-dir build --output-on-failure
./build/bin/elvex --version
```

When using GitHub's ZIP download, run the commands beginning with `cmake` from the extracted project directory. Git is not required in that case.

The build produces four executables in `build/bin/`: `elvex` (text generation), `elvexlexicon` (compacted lexicon construction), and `elvexpostedition_en` / `elvexpostedition_fr` (post-editing).

## Run an example

The `french-animal-calls` example builds a compacted morphological lexicon and generates French text from a sample feature structure. After building ELVEX, run this **from the repository root**:

```sh
make -C data/examples DATA=french-animal-calls run
```

The shared Makefile uses `build/bin/elvex` and `build/bin/elvexlexicon` by default. Its build products go to `data/examples/french-animal-calls/.elvex-build/`. See the [French animal calls example guide](data/examples/french-animal-calls/README.md) for more commands.

ELVEX also includes examples for [music generation](data/examples/music/README.md) and [didactic pop music](data/examples/pop-music-didactic/README.md). Those examples use LilyPond to produce sheet music and, where supported, MIDI files; LilyPond is **not** required to build the core ELVEX engine.

## How ELVEX works

A generation project typically supplies:

1. **Grammar rules** (`.rules`), describing allowable structures and constraints.
2. **Lexical entries** (`.lexicon`), optionally supplemented by morphological data (`.morpho`) and patterns (`.pattern`) compiled into a compacted lexicon.
3. **Input** (`.input` or `.stdin`), describing what is to be expressed as a feature structure.
4. Optional **macros** (`.macros`) and related language resources.

The engine builds a shared derivation forest and can enumerate its possible surface realizations. Constraints are expressed through feature structures and unification. Generation is controlled by the provided resources: ELVEX does not infer an open-ended language model from examples.

For large forests, `elvex --forest-only` skips sentence enumeration; `--progress` writes progress information to standard error. XML forest output is supported by the normal libxml2-enabled build. The compiled lexicon lookup cache is enabled by default and can be disabled for comparison with `ELVEX_LEXICON_CACHE=0`.

### Illustrative generation example

An earlier ELVEX grammar demonstrates controlled French conditional sentences. Given an input such as:

```text
text [HEAD:cause, i:[HEAD:rain], ii:[HEAD:umbrella, i:[HEAD:_you]]]
```

one of the documented outputs is *« S’il pleut, tu prendras un parapluie. »* (“If it rains, you will take an umbrella.”). This is an **illustration of a domain-specific grammar**, not a promise that the `french-animal-calls` example produces this sentence.

## Repository layout

| Directory | Contents |
| --- | --- |
| `src/main/` | C++ engine, Flex scanners, and Bison grammar |
| `src/test/` | CTest declarations and regression-test scripts |
| `data/regression/` | Versioned inputs and expected outputs for regression tests |
| `data/examples/` | Example grammars, lexicons, and inputs |
| `doc/` | ELVEX language manual source (`doc-en.tex`) |
| `elvex-www/` | Optional browser-based grammar editing interface |
| `build/` | Locally generated binaries and intermediate files; not versioned |

The project is configured by the top-level `CMakeLists.txt`. Do not build directly in the source root.

## Documentation

- [Installation and requirements](INSTALL.md)
- [Testing and regression cases](src/test/README.md)
- [Grammar and input resources](data/regression/README.md)
- [Language manual source](doc/doc-en.tex)
- [Web interface and editor fields](elvex-www/README.md) and [field reference](DOCUMENTATION.md)
- [Project changes](CHANGELOG.md)
- [Release instructions for maintainers](RELEASING.md)

For experiments accompanying *A Constraint-Based Formalism for Controlled Text Generation* (INLG 2026), see the separate [reproducibility repository](https://github.com/lionelclement/Elvex-paper-reproducibility).

## Testing

The default CTest suite has **85 tests** in this source snapshot: 42 regression cases executed with the lexicon cache disabled and enabled, plus one forest/progress test. Tests compare generated lines against versioned reference outputs; they do not benchmark execution speed.

```sh
ctest --test-dir build --output-on-failure
ctest --test-dir build -R 'regression.31_animal_compacted_lexicon' --output-on-failure
```

Read [src/test/README.md](src/test/README.md) before adding or updating a test case.

## Scope and limitations

ELVEX is suited to controlled generation in domains where explicit grammars, lexical coverage, and predictable constraints are useful. Building those linguistic resources requires substantial effort. ELVEX does not automatically learn from text, complete arbitrary prompts, or guarantee that every possible input can be realized.

## Author and license

Developed by **Lionel Clément**, University of Bordeaux / LaBRI. See [AUTHORS.md](AUTHORS.md).

The ELVEX software is distributed under the **GNU General Public License, version 3**; see [LICENSE](LICENSE) for its terms. Licensing of independently authored linguistic resources should be checked separately.
