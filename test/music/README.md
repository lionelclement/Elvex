# Music generation with Elvex and LilyPond

This repository contains a collection of declarative music-generation examples. Each `.input` file describes a piece or exercise—such as a flute scale, a chamber work, a piano piece, or a pop/rock arrangement. **Elvex** interprets these descriptions using the supplied grammar (`.rules`) and lexicon (`.lexicon`) files and produces **LilyPond** notation. LilyPond then engraves printable sheet music and, when the score includes MIDI output, a MIDI file.

## Requirements

- **GNU Make**, or a compatible `make` implementation.
- **Elvex**, with the `elvex` executable available on your `PATH`. It must support the command-line options `--rules-file`, `--lexicon-file`, `--input-file`, and `-f` used by the Makefile.
- **LilyPond**, with the `lilypond` executable available on your `PATH`, for score engraving and MIDI export.
- A shell with standard Unix utilities (`test`, `grep`, `tail`, `rm`, and `printf`).

Elvex is a separate prerequisite: it is not installed by this repository. Check your setup with:

```sh
make --version
elvex --help
lilypond --version
```

## Where to run Make

The `Makefile`, `.input` files, and grammar files are in **`test/music/`** in the Git repository. Start there:

```sh
cd test/music
make list
```

If you are already in the directory containing the `Makefile`, no `cd` is needed. Alternatively, from the repository root, use `make -C test/music <target>`.

## Quick start

```sh
# Show the available input files, grouped by type.
make list

# Generate one example's LilyPond source.
make 00_scales_solo_flute.ly

# Engrave the example as a PDF.
make 00_scales_solo_flute.pdf

# Build all available examples (PDFs and MIDI targets).
make
```

The example-specific targets use the same basename as the corresponding `.input` file. For example, `00_scales_solo_flute.input` becomes `00_scales_solo_flute.ly` and then `00_scales_solo_flute.pdf`.

## Make targets

| Command | Purpose |
| --- | --- |
| `make` or `make all` | Run the input check and build all PDFs and MIDI targets. |
| `make ly` | Generate LilyPond `.ly` files only. |
| `make pdf` | Build the PDFs (and their prerequisite `.ly` files). |
| `make midi` | Request MIDI outputs for all examples. |
| `make <name>.ly` | Generate one LilyPond file. |
| `make <name>.pdf` | Generate one score PDF. |
| `make <name>.midi` | Request MIDI output for one example. |
| `make list` | List scale, general-music, and circus inputs. |
| `make check` | Warn if known obsolete or experimental inputs are present. |
| `make circus` | Build PDFs and MIDI targets for circus examples only. |
| `make circus-ly`, `make circus-pdf`, `make circus-midi` | Build the selected circus output type. |
| `make -k` | Continue building independent targets after an error. |
| `make clean` | Delete generated `.ly`, `.pdf`, `.midi`, stamp, and other intermediate files. |
| `make distclean` | Run `clean` and also remove `log.txt`. |
| `make rebuild` | Clean, then rebuild everything. |

## Expected results

For each input, the build can create the following files **in the same directory**:

| File | Meaning |
| --- | --- |
| `<name>.ly` | LilyPond source emitted by Elvex. |
| `<name>.pdf` | Engraved, printable score from LilyPond. |
| `<name>.midi` | MIDI playback data, **if the LilyPond score generates MIDI**. |
| `<name>.lilypond.stamp` | Internal build marker used by Make. |
| `log.txt` | Elvex diagnostics and LilyPond build output. |

**Not every example necessarily produces MIDI.** The Makefile prints a warning when LilyPond does not create a requested `.midi` file; that warning does not, by itself, mean the PDF generation failed. Conversely, a nonempty `.ly` file is not proof that the music has compiled successfully: building a PDF also checks whether LilyPond can process it.

You should see progress lines similar to:

```text
ELVEX-SCALE 00_scales_solo_flute.input -> 00_scales_solo_flute.ly
LILYPOND 00_scales_solo_flute.ly
```

The full `make` build can take longer than an individual example because it discovers all `*.input` files in the directory.

## How the sources fit together

- `*.input` — Piece specifications: musical style, form, instrumentation, key, meter, and other generation parameters.
- `music.rules` — Main grammar entry point, which includes the specialized `.rules` modules.
- `scale.rules` — Grammar entry point selected for input filenames containing `scales`.
- `music.lexicon` — Lexicon passed to Elvex for both general and scale builds.
- Other `*.rules` and `*.lexicon` files — Specialized musical rules and definitions referenced by the grammar.
- `Makefile` — Connects Elvex generation to LilyPond engraving.

To make a new example, copy a working `.input`, choose a new basename, and adjust its settings to values supported by the grammars. Run `make <new-name>.ly` first, then `make <new-name>.pdf`.

## Configuration

The Makefile allows these variables to be overridden from the command line:

```sh
make ELVEX=/path/to/elvex LILYPOND=/path/to/lilypond
make RULES=music.rules SCALE_RULES=scale.rules LEXICON=music.lexicon
make LOG=build.log 00_scales_solo_flute.pdf
```

The default values are `elvex`, `lilypond`, `music.rules`, `scale.rules`, `music.lexicon`, and `log.txt`, respectively.

## Troubleshooting

**`elvex: command not found` or `lilypond: command not found`:** install the missing program and ensure its executable is on `PATH`, or set `ELVEX` / `LILYPOND` explicitly.

**`make: *** [<name>.ly] Error 1`:** Elvex failed while generating the LilyPond file. Inspect the end of `log.txt`:

```sh
tail -80 log.txt
```

Syntax errors may originate in a `.rules` or `.lexicon` file, even when the error appears while processing a particular `.input` file. Identifiers in these files must not conflict with reserved Elvex keywords.

**`ERROR: LilyPond failed for <name>.ly`:** read the last lines of `log.txt` for the LilyPond diagnostic. Check the generated `.ly` file and the related grammar.

**Missing `.midi` file:** confirm that the generated LilyPond score includes a MIDI output block. The Makefile does not automatically insert one.

**Build artefacts seem stale:** use `make rebuild` to regenerate everything. Some indirectly included grammar modules are not individually tracked by Make's dependency list, so a clean rebuild is advisable after editing them.
