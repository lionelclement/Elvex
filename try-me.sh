make -s
(cd data/lefff ; make -s)

cd data

echo "--------------------------------------------------------"

#../src/elvex -t -compactDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon -inputFile fr-1.0.3.input
#../src/elvexdebug -compactDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon -inputFile fr-1.0.3.input -xml fr-1.0.3.xml 2> fr-1.0.3.html ; open fr-1.0.3.html
#../src/elvex  -maxCardinal 1000000 -maxUsages 100000 -compactDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon -inputFile fr-1.0.3.input | ../src/elvexpostedition |tr '@' "\n" |sed -e 's/^ *//'
../src/elvex  -maxCardinal 1000000 -maxUsages 100000 -compactDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon "text [PRED:hello, i:[FORM:\"`whoami`\"], ii:[PRED:see_you_soon, i:[PRED:installer, i:[PRED:_pro, number:sg, person:two], ii:[FORM:\"Elvex\"], tense:recent_past ]]]" | ../src/elvexpostedition |tr '@' "\n" |sed -e 's/^ *//'

cd ..
