**Elvex**
=====

The name **Elvex** encompasses the name of a software, the name of a natural text generation algorithm, the name of the language used to write natural language grammars and the name of a linguistic formalism.

What can be fun with **Elvex** software
-----------------------------

Write automatically and quickly relevant and adequate texts in natural language, given a meaning and elements of speech. Rest assured that **Elvex** avoids any misunderstanding, and it achieves this without the need for any training data. Migrate this solution to an embedded system with limited resources and no connection to a massive data server.

Practically speaking: to build Text Generator with **Elvex** for an application (Chatbot, Letter-writer, etc)
--------------------

Every time you use a word it has to be fully described in the lexicon, depending on a specific domain. It would be a long and costly process to write all the simple words, compounds and idiomatic phrases (several months for one person, several weeks in a restricted domain).

The grammar is more complex, but shorter to write (several weeks).

**Elvex** software
=====

**Elvex** is a **Natural Text Generator** engine wrotten in C++ language

It is written by Lionel Clément at Bordeaux University - France and released by LaBRI under GNU GPL License.

**Elvex** uses custom-written lexicons and grammatical rules as file parameters, along with a **feature structure** as input. The lexicons and grammatical rules serve as linguistic resources used for sentence generation, while the **feature structure** represents the content to be expressed.

In the end, **Elvex** generates texts in Natural Language that accurately mirrors the input while adhering to the grammar's syntactic and lexical rules.

Although it is an Artificial Intelligence program, **Elvex** doesn't rely on massive training data in neural networks.

License
-------

The **Elvex** software is released under GNU GPL License V3.

In other words

- The source code must be made available when the software is distributed
- A copy of the license and the copyright manual must be included with the software
- Modifications must be released under the same license when the software is distributed. A similar or a related license must be used
- Changes made to the code must be documented

The license shall cover **Elvex** software and the included data except LeFFF which is under another license.

The language of **Elvex** is not under licence (it belongs to the public domain), so the data you will write (new grammars, new lexicons) are not part of **Elvex**, it is under another license.

**Elvex** language
=====

The lexicons, grammatical rules, and the content to be expressed are all described using the **Elvex** language, which is detailed in the manual documentation.

**Elvex** algorithm
=====

Given a feature structure that represents the content to be expressed, **Elvex** constructs a tagged shared forest whose boundary is the generated texts."

Each node of the shared forest corresponds to a grammaticl rule 

$A \rightarrow $B$_1$ $B$_2$ \dots $B$_n$
$\Gamma(\uparrow)$
$\downarrow_i = \phi(\uparrow, \downarrow_k, \Downarrow_k)$, $k \ne i$
$\Uparrow = \psi(\uparrow, \downarrow_i, \Downarrow_i)$


**Elvex** 
I don’t explain the algorithm here. It’s efficient and monotonic (each rule adds something and never removes the effect of other rules).

**Elvex** formalism
-----------------

**Elvex** formalism is freely inspired by some syntactic formalisms such as:

-Lexique-Grammaire (M. Gross 1960)

-Functional Grammar (M. Kay 1979)

-Lexical-Functional Grammar (J. Bresnan and D. Kaplan 1982)

-Systemic Functional Grammar (M. Halliday 1994).

Citation
-----------------

*Linguistic Resources for the Automatic Generation of Texts in Natural Language: The Elvex Formalism* Lionel Clément 2023
forthcoming from Springer Max Silberztein ed.

One of the most difficult stuff already done with Elvex
-----------------------------------------------

- Adjective order in English (big yellow squared stuff, not squared yellow big stuff)
- Anaphora resolution process between sentences with pronouns, synonyms and hypernyms
- Complex idiomatic phrases (not always contiguous)
- Past participle aggrement in French with transitive verbs
- Lexical functions (based on Mel'čuk theory)
- Coordinations with Right-Node Raising and Gapping
- Morphology in standard Breton

An example of a solution to a NLG problem solved with **Elvex**: Causal clauses in a little French Grammar
-----------------------------------------------

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
### text [HEAD:cause, i:[HEAD:to_rain], ii:[HEAD:umbrella, i:[HEAD:_you]]
S'il pleut, tu prendras un parapluie.

// present or future & slang language
### text [HEAD:cause, i:[HEAD:rain], ii:[HEAD:umbrella, i:[HEAD:_you]], language_register:slang]
Il flotterait, tu prendrais un pépin.

// continuous present
### text [HEAD:cause, i:[PRED:rain], ii:[PRED:umbrella, i:[HEAD:_you]], tense:present, aspect:continuous]
S'il est en train de pleuvoir, tu prendras un parapluie.

### text [HEAD:cause, i:[PRED:rain], ii:[PRED:umbrella, illocutionary:ask, i:[HEAD:_you]]
S'il pleut, est-ce que tu prendras un parapluie ?

//past
### text [HEAD:cause, i:[HEAD:rain], ii:[HEAD:umbrella, i:[HEAD:_you]], tense:past]
S'il avait plu, tu aurais pris un parapluie.

//past & slang language
### text [HEAD:cause, i:[HEAD:rain], ii:[HEAD:umbrella, i:[HEAD:_you]], tense:past, language_register:slang]
Il aurait plu, tu aurais pris un parapluie.

### text [HEAD:cause, i:[HEAD:rain], ii:[HEAD:umbrella, i:[HEAD:_you]], tense:past, aspect:continuous]
S'il était en train de pleuvoir, tu aurais pris un parapluie.

//future
### text [HEAD:cause, i:[HEAD:rain], ii:[HEAD:umbrella, i:[HEAD:_you]], tense:future]
S'il pleuvait, tu prendrais un parapluie.

### text [HEAD:cause, i:[HEAD:rain], ii:[HEAD:umbrella, i:[HEAD:_you]], tense:future, aspect:continuous]
S'il était en train de pleuvoir, tu prendrais un parapluie.

