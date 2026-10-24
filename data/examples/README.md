# ELVEX examples

The directories below demonstrate grammatical and lexical generation. Example names use lowercase hyphenated English descriptions and, where appropriate, the language being generated.

| Directory | Purpose |
| --- | --- |
| [`synthetic-large-lexicon/`](synthetic-large-lexicon/README.md) | A synthetic morphology and lexicon stress test, independent of any natural language. |
| [`english-sentences/`](english-sentences/README.md) | English sentence realization with morphology, agreement, and adjective ordering. |
| [`french-noun-phrases/`](french-noun-phrases/README.md) | A small French determiner–noun agreement example. |
| [`breton-morphology/`](breton-morphology/README.md) | Breton morphology and noun-phrase realization. |
| [`english-adjectives/`](english-adjectives/README.md) | English adjective ordering from semantic features. |
| [`french-animal-calls/`](french-animal-calls/README.md) | French sentences naming animals and the sounds they make. |
| [`french-lightness/`](french-lightness/README.md) | French light-verb and lexical-function constructions. |
| [`partial-word-order/`](partial-word-order/README.md) | Language-neutral partial-order constraints over grammatical constituents. |
| [`optional-constituents/`](optional-constituents/README.md) | Language-neutral optional-rule constituents and conditional features. |
| [`french-syntax/`](french-syntax/README.md) | A French syntax and morphology generation example. |
| [`music/`](music/README.md) | A collection of score-generation grammars and multiple independent musical input files. |
| [`pop-music-didactic/`](pop-music-didactic/README.md) | A multi-language collection of small pop-music score-generation examples. |

Build the project first as described in [INSTALL.md](../../INSTALL.md). For grammar examples, run:

```sh
make -C data/examples DATA=english-sentences run
make -C data/examples DATA=french-animal-calls run
```

The music directories are collections: they contain multiple inputs and their own Makefiles. See their README files for usage.
