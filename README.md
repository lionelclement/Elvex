Elvex
=====

**Elvex** is a **Natural Text Generator**

It is written by Lionel Clément at Bordeaux - France and released by LaBRI under GNU GPL License.

The system, written in C++, is using handwritten *lexicon* and *grammar* as parameters, and also a *concept* (i.e. meaning + an elements of speech) as an input. Finally, the outputs of a text represent exactly the concept written in Natural Language.

License
-------

**Elvex** is released under GNU GPL License V3.

In other words

- The source code must be made available when the software is distributed
- A copy of the license and the copyright manual must be included with the software
- Modifications must be released under the same license when the software is distributed. A similar or a related license must be used
- Changes made to the code must be documented

The license shall cover **Elvex** software and the included data except LeFFF which is under another license.

The language of **Elvex** is not under licence (it belongs to the public domain), so the data you will write (new grammars, new lexicons) are not part of **Elvex**, it is under another license.

What you can't do with Elvex
-----------------------------

You should ask **Elvex** to interpret exactly what you expect. **Elvex** will translate your request but will not be in the position to understand the meaning of it. In short, **Elvex** does not know *what to say*.

**Elvex** will translate your request but will not be in the position to understand the meaning of it. In short, **Elvex** does not know

What you can do with Elvex
-----------------------------

Write automatically and quickly texts in a correct form of Natural Language, given a meaning and elements
of speech. Rest assured that **Elvex** avoids any misunderstanding.

Note that unlike other systems, the concepts that are expressed may not depend on prior lexical choices.

Theorical aspects
-----------------

**Elvex** is freely inspired by some syntactic formalisms such as: 

-Lexique-Grammaire (M. Gross 1960)
-Functional Grammar (M. Kay 1979)
-Lexical-Functional Grammar (J. Bresnan and D. Kaplan 1982) 
-Systemic Functional Grammar (M. Halliday 1994).

It's working with handwritten lexicons and grammars that are similar to the linguistic descriptions of the syntactic phenomenon but not with learning data.
I don’t explain the algorithms here. It’s efficient and monotonic (each rule add something and never delete the effects of another rule).

Practically speaking
--------------------

Every time you use a word it has to be fully described in the lexicon, depending on a specific domain. It would be a long and costly process (several months for one person in a restricted domain).

The grammar is more complex, but shorter to write (several weeks).

Sample: Causal clauses in a little French Grammar first
-----------------------------------------------

Causal clauses with tense aggrement.

In French, the basis of verbal tense and the conclusion of a causal clause depend on the aspect, the tense and even on the differences in language registers of a sentence

- present: 
if present => future
- present or future in slang language:
conditional without "if" => conditional
- past:
if past => past conditional
- past in slang language:
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

