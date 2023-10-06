Elvex Project
=====

The name **Elvex** encompasses the name of a software, the name of a natural text generation (NLG) algorithm, the name of the language used to write natural language grammars and the name of a linguistic formalism for NLG.

What can you do with Elvex software?
-----------------------------

Write automatically and quickly relevant and adequate texts in natural language, given a meaning and elements of speech. Rest assured that **Elvex** avoids any misunderstanding, and it achieves this without the need for any training data. Migrate this solution to an embedded system with limited resources and no connection to a massive data server.

In practical terms, how can you use Elvex to build a Text Generator for an application (such as a Chatbot, Letter-writer, etc)?
--------------------

To use **Elvex** software on your application, you first need to create a lexicon and a grammar by using the **Elvex** language and adhering to the **Elvex** formalism.

The inputs will depend on the **Elvex** grammar built for your application.

a) To write the lexicon

Each time you want to use a word, it needs to be thoroughly defined in the lexicon, which can vary depending on the specific domain. This entails describing every word you intend to generate. Writing entries for all the basic words, compounds, and idiomatic phrases can be a time-consuming and expensive endeavor (taking several months for one person or several weeks within a narrow domain).

b) To write the grammar

In addition to the lexicon, you'll need to create a natural language grammar. While the grammar may be more complex, it typically requires less time to develop (usually just several weeks).

The Elvex program is a software that can be compiled on any platform and launched from an application or operating system.

Elvex software
=====

**Elvex** is a **Natural Text Generator** engine written in C++ language

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

The language of **Elvex** formalism is not under licence (it belongs to the public domain), so the data you will write (new grammars, new lexicons) are not part of **Elvex**, it is under another license.

Elvex language
=====

The lexicons, grammatical rules, and the content to be expressed are all described using the **Elvex** language, which is detailed in the manual documentation.

Elvex algorithm
=====

I cannot elaborate on the algorithm here, but let's provide some elements to understand the mechanism in a general sense: 

Given a feature structure (FS) that represents the content to be expressed, **Elvex** constructs a tagged shared forest whose boundary is the generated texts. The shared forest (which actually is a context-free grammar) is tagged with synthesized and inherited FS on each node. The synthesized FS constrain rules based on local properties (typically lexical properties), while inherited FS constrain local structures based on their context (typically semantical properties).

The new algorithms used are

-Equations and inequalities on feature structures resolved through unification.

-Equivalence classes defined by an equivalence relation among items.

-Construction of a context-free grammar instance from a context-free grammar.

The **Elvex** algorithm is deterministic and monotonic (each rule adds something and never removes the effect of other rules).

Elvex formalism
=====

**Elvex** formalism is freely inspired by some syntactic formalisms such as:

-Lexique-Grammaire (M. Gross 1960)

-Functional Grammar (M. Kay 1979)

-Lexical-Functional Grammar (J. Bresnan and D. Kaplan 1982)

-Systemic Functional Grammar (M. Halliday 1994).

Citation
-----------------

*Linguistic Resources for the Automatic Generation of Texts in Natural Language: The Elvex Formalism*, by Lionel Clément, 2023, forthcoming in *Linguistic Resources for Natural Language Processing - On the Necessity of Using Linguistic Methods to Develop NLP Software*, edited by Max Silberztein, Springer.

One of the most difficult stuff already done with Elvex
=====

- Adjective order in English (big yellow squared stuff, not squared yellow big stuff)
- Anaphora resolution process between sentences with pronouns, synonyms and hypernyms
- Complex idiomatic phrases (not always contiguous)
- Past participle aggrement in French with transitive verbs
- Lexical functions (based on Mel'čuk theory)
- Coordinations with Right-Node Raising and Gapping
- Morphology in standard Breton

An example of a solution to a NLG problem solved with *Elvex*: Causal clauses in a little French Grammar
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

