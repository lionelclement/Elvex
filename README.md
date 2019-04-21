Elvex
=====

**Elvex** is an **Natural Text Generator**

It is written by Lionel Clément at Bordeaux - France and released by LaBRI under GNU GPL License.

The system, written in C++, takes handwritten *lexicon* and *grammar* as parameters, a *concept* as input, and then outputs a text corresponding exactly to the concept writing in Natural Language.

What you cannot do with Elvex
-----------------------------

You should ask **Elvex** to tell you exactly what you want to hear. **Elvex** will know what to do to tell it, but will never be known what it is saying. You can ask to tell "It is raining" in any language you want, but never **Elvex** knows if it is raining or not... until the computer is on the water :-) 

What you can do with Elvex
-----------------------------

Write automatically and quickly texts in a correct Natural Language, and rest assured that **Elvex** avoids any misunderstanding.

Theorical aspects
-----------------

**Elvex** is freely inspired by syntactic formalisms like lexique-grammaire (M. Gross 1960), Lexical-Functional Grammar (J. Bresnan and D. Kaplan 1982), Functional Grammar (M. Halliday 1994).

It works with handwritten lexicon and grammars, and not with learning data.

Practically speaking
--------------------

Each word, each use of the word has to be fully described in the lexicon, depending on the domain. It would be a long and costly process (several months for one person). 

The grammar is more complex, but shorter to write (several weeks).

A little French Grammar first
-----------------------------

Causal clauses with tense aggrement.

In French, the verbal tense of premise and conclusion of a clausal clause
depends on the aspect and the tense of the sentence
- present : 
present => future
- past:
past => past conditional
- future:
 preterit => conditional

### text [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]]]
S'il pleut, tu prendras un parapluie.

### text [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], tense:present, aspect:continuous]
S'il est en train de pleuvoir, tu prendras un parapluie.

### text [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, illocutionary:ask, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]]]
S'il pleut, est-ce que tu prendras un parapluie ?

//past

### text [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], tense:past]
S'il avait plu, tu aurais pris un parapluie.

### text [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], tense:past, aspect:continuous]
S'il était en train de pleuvoir, tu aurais pris un parapluie.

//future

### text [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], tense:future]
S'il pleuvait, tu prendrais un parapluie.

### text [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], tense:future, aspect:continuous]
S'il était en train de pleuvoir, tu prendrais un parapluie.

