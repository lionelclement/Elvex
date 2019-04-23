Elvex
=====

**Elvex** is an **Natural Text Generator**

It is written by Lionel Clément at Bordeaux - France and released by LaBRI under GNU GPL License.

The system, written in C++, takes handwritten *lexicon* and *grammar* as parameters, a *concept* (i.e. meaning plus elements of discourse) as input, and then outputs a text corresponding exactly to the concept writing in Natural Language.

License
-------

**Elvex** is release under GNU GPL License V3.

That means that

- Source code must be made available when the sofware is distributed
- A copy of the licence and copyright notice must be included with the software
- Modifications must be released under the same license when distributing the software. A similar or related license must be used
- Changes made to the code must be documented 

The license shall cover **Elvex** software and the included data except LeFFF which is under another license.

But the language of **Elvex** is not under a licence (it is in the public domain), so the new data you will write (new grammars, new lexicons) are not a part of **Elvex** and is under any other license.

What you cannot do with Elvex
-----------------------------

You should ask **Elvex** to tell you exactly what you want to hear. **Elvex** will know what to do to tell it, but will not really understand what it is saying. In short, **Elvex** does not know *what to say*. 
You can ask to tell "It is raining" in any language you want, but **Elvex** will never know if it is raining or not... until the computer is in the water :-) 

What you can do with Elvex
-----------------------------

Write automatically and quickly texts in a correct Natural Language, from the meaning and elements of discourse and rest assured that **Elvex** avoids any misunderstanding.

Note that unlike other systems, the concepts to be expressed may not depend on prior lexical choices.

Theorical aspects
-----------------

**Elvex** is freely inspired by some syntactic formalisms: Lexique-Grammaire (M. Gross 1960), Functional Grammar (M. Kay 1979), Lexical-Functional Grammar (J. Bresnan and D. Kaplan 1982), Systemic Functional Grammar (M. Halliday 1994).

It works with handwritten lexicon and grammars close to the linguistic descriptions of syntactic phenomena, and not with learning data.

I do not explain the algorithms here. It is efficient and monotonic (in that each rule adds something and never delete the effect of another rule).

Practically speaking
--------------------

Each word, each use of the word has to be fully described in the lexicon, depending on the domain. It would be a long and costly process (several months for one person in a restricted domain). 

The grammar is more complex, but shorter to write (several weeks).

Sample: Causal clauses in a little French Grammar first
-----------------------------------------------

Causal clauses with tense aggrement.

In French, the verbal tense of premise and conclusion of a clausal clause
depends on the aspect, the tense and even on the language register of the sentence
- present: 
if present => future
- present or future in house or slang language:
conditional without "if" => conditional
- past:
if past => past conditional
- past in house or slang language:
past conditional without "if" => past conditional
- future:
 Imperfect => conditional

// present
### text [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]]]
S'il pleut, tu prendras un parapluie.

// present or future & slang language
### text [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], language_register:slang]
Il flotterait, tu prendrais un pépin.

// continuous present
### text [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], tense:present, aspect:continuous]
S'il est en train de pleuvoir, tu prendras un parapluie.

### text [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, illocutionary:ask, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]]]
S'il pleut, est-ce que tu prendras un parapluie ?

//past
### text [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], tense:past]
S'il avait plu, tu aurais pris un parapluie.

//past & slang language
### text [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], tense:past, language_register:slang]
Il aurait plu, tu aurais pris un parapluie.

### text [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], tense:past, aspect:continuous]
S'il était en train de pleuvoir, tu aurais pris un parapluie.

//future
### text [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], tense:future]
S'il pleuvait, tu prendrais un parapluie.

### text [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], tense:future, aspect:continuous]
S'il était en train de pleuvoir, tu prendrais un parapluie.

