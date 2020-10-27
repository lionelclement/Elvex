Elvex Data
=====

French Toy grammar demonstration (work in progress)
-------
fr-x.x.x.*

English Toy grammar
-------
en-x.x.x.*

To compile
-------
bin/elvexbuildLexicon -compactLexiconDirectory data -compactLexiconFile en-x.x.x -patternFile data/en-x.x.x.pattern -morphoFile data/en-x.x.x.morpho build

To use
-------
In *.input, uncomment a line begining with //text[...
and within this directory data, call elvex like this:

bin/elvex -compactLexiconDirectory data -compactLexiconFile en-x.x.x -grammarFile en-x.x.x.grammar -lexiconFile en-x.x.x.lexicon -inputFile en-x.x.x.input
| bin/elvexpostedition | sed 's/^ *//'
