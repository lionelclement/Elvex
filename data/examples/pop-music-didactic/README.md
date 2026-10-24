# Didactic Pop Music Generation with Elvex

This directory contains a small, self-contained set of **four didactic pop-music examples**. Elvex interprets the `.input` descriptions through a deliberately bounded music grammar and emits LilyPond scores. LilyPond then engraves printable sheet music and, where requested by the score, creates MIDI playback.

The grammar is intentionally smaller than the project's historical ensemble grammars. Its bounded number of alternative derivations is intended to reduce the risk of Elvex's `too much items build` error. Its main design goal is to demonstrate reusable musical roles—lead, guitar, bass, percussion, keyboard and brass—rather than hand-write each piece.

## Requirements

- **ELVEX** (`elvex`) with support for the grammar and lexicon syntax used here.
- **LilyPond** (`lilypond`) to engrave the scores and generate MIDI where supported.
- **GNU Make** or a compatible `make` implementation.
- Standard Unix shell tools: `test`, `grep`, `tail`, `rm`, `touch` and `printf`.

Build ELVEX from the repository root first ([installation](../../../INSTALL.md)). Check that the executables are on your `PATH` or pass their paths using Make variables:

```sh
command -v elvex
command -v lilypond
make --version
```

The Makefile allows the executable names to be overridden, e.g. `make ELVEX=/path/to/elvex LILYPOND=/path/to/lilypond`.

## Quick start

Run commands **from `data/examples/pop-music-didactic/`** (the directory containing the `Makefile`). From the repository root, first run `cd data/examples/pop-music-didactic`.

```sh
make list       # show the available input files
make ly         # generate LilyPond .ly sources with Elvex
make pdf        # engrave PDF scores with LilyPond
make midi       # generate MIDI files when present in LilyPond output
```

Or simply run `make` (equivalent to `make all`), which requests both PDF and MIDI targets.

To build just the French chanson example:

```sh
make 001_chanson_francaise_voix_guitare_djembe.ly
make 001_chanson_francaise_voix_guitare_djembe.pdf
```

## Example inputs

| Input file | Musical setup |
| --- | --- |
| `001_chanson_francaise_voix_guitare_djembe.input` | French chanson: voice, guitar, bass and djembe |
| `002_english_pop_piano_band.input` | English-language pop with piano and band |
| `003_couleurs_flute_clarinette_sax_violon.input` | Flute, clarinet, saxophone and violin ensemble |
| `004_refrain_pop_avec_cuivres.input` | Pop refrain with brass |

Each `.input` describes the piece, its instrumentation and musical parameters. Modify or add an input, then build the corresponding target with `make <name>.ly` or `make <name>.pdf`.

## Make targets

| Command | Action |
| --- | --- |
| `make` / `make all` | Request all PDFs and MIDI files |
| `make list` | List the available `.input` files |
| `make ly` | Convert every `.input` into a `.ly` file |
| `make pdf` | Build the engraved `.pdf` scores |
| `make midi` | Request the `.midi` targets |
| `make trace-001` through `make trace-004` | Produce a separate Elvex trace, `log-001.html` through `log-004.html` |
| `make clean` | Remove generated music files, stamps and build logs |
| `make rebuild` | Clean and rebuild all PDF and MIDI targets |

## Expected outputs

For each `<name>.input`, the build pipeline is:

```text
<name>.input  -- Elvex -->  <name>.ly  -- LilyPond -->  <name>.pdf
                                               \----->  <name>.midi (if produced)
```

The `.ly` file is LilyPond source; the `.pdf` is printable sheet music; and the `.midi`, when present, is playback data. LilyPond is run once per `.ly` file and the Makefile records successful processing in a `<name>.lilypond.stamp` file. `log.txt` collects Elvex diagnostic output and LilyPond output.

**MIDI caveat:** The Makefile warns if LilyPond does not produce a requested MIDI file, but its MIDI target check does not fail in that situation. Therefore `make midi` succeeding does **not** guarantee that every example has a `.midi` file. Check the actual outputs with `ls *.midi` (if any).

## Directory layout

```text
Makefile                 Build rules and trace targets
music.rules             Main grammar entry point (includes pop_didactic.rules)
pop_didactic.rules      Bounded music-generation grammar
music.lexicon           Main lexicon entry point
common.lexicon          Shared vocabulary
chords.lexicon          Chord definitions
001_...input to 004_...input  The four musical examples
README.md                This guide
.gitignore              Generated-file exclusions for Git
```

The generated `.ly`, `.pdf`, `.midi`, `.lilypond.stamp`, trace, and log files are build artifacts rather than original source files. Some `.ly` files may still be present in older checkouts, but users can regenerate them with this Makefile. Newly generated outputs should not be committed as source files. Run `make ly`, `make pdf`, or `make` to regenerate them.

## Tracing and troubleshooting

To inspect Elvex's processing of a single example:

```sh
make trace-001
# Open log-001.html in a browser, for example on macOS:
open log-001.html
```

If a target fails, inspect the end of the log:

```sh
tail -80 log.txt
```

- **`elvex: command not found`**: install Elvex or set `ELVEX=/path/to/elvex`.
- **`lilypond: command not found`**: install LilyPond or set `LILYPOND=/path/to/lilypond`.
- **Elvex grammar or lexicon error**: inspect `music.rules`, `pop_didactic.rules` and the included lexicons; ensure Elvex-reserved words are not used as conflicting identifiers.
- **Elvex `too much items build`**: this local grammar avoids including the larger historical role/stave/bar rule modules; avoid adding them without considering derivation growth.
- **Missing MIDI**: LilyPond may engrave a score without emitting MIDI. Inspect the `.ly` and `log.txt`; a warning alone is not proof of an engraving failure.

The grammar also includes a dedicated `LH_CHORD4` handling path: left-hand piano/keyboard bass notes can remain in octave 2 while the chord voicing is taken from the next octave, matching the chord lexicon's available register.

## Rebuilding and version control

```sh
make clean
make
```

Version the `Makefile`, grammar, lexicons, and `.input` examples; exclude build products and local logs from commits. Do not delete `.input`, `.rules` or `.lexicon` files when cleaning the directory.
