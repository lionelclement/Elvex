# ELVEX language manual

The authoritative language manual is [doc-en.tex](doc-en.tex), written in English for ELVEX **2.28.0**. The [PDF manual](doc-en.pdf) is generated from the same source. It documents the grammar formalism, feature structures, operational statements, generation options, and compacted lexicons.

## Rebuild the PDF

Install a LaTeX distribution that includes the packages `babel`, `amsmath`, `amssymb`, `listings`, `epsfig`, `hyperref`, `gb4e`, and `enumitem`. From the repository root, run:

```sh
cd doc
latexmk -pdf -interaction=nonstopmode -halt-on-error doc-en.tex
```

Commit `doc-en.pdf` whenever you change `doc-en.tex`, so readers who download from GitHub receive a PDF matching the source. Intermediate files (`.aux`, `.log`, `.fls`, `.fdb_latexmk`, `.out`, `.synctex.gz`) are generated and should remain ignored by Git.

For compilation, installation and tests of ELVEX itself, consult [INSTALL.md](../INSTALL.md) and [the test documentation](../src/test/README.md). The manual's French sentences are linguistic examples, not untranslated user instructions.
