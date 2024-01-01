Elvex: A Rule-Based NLG System
===

1. No Need for Large Training Corpus: **Elvex** does not rely on vast text corpora for training, reducing storage and computational requirements.

2. Deterministic Responses: **Elvex** generates deterministic responses, ensuring consistent and predictable outcomes for a given input. This reliability is a fundamental strength, particularly in applications where consistency is paramount.

4. **Elvex** actively avoids generating unexpected or incorrect responses, steering clear of probabilistic pitfalls.

5. **Elvex** operates based on explicit input, significantly reducing the likelihood of ambiguous or misinterpreted responses. This intentional design choice adds a layer of precision to the text generation process.

7. Motivated by General Linguistics: **Elvex**'s approach is rooted in principles of general linguistics.

Elvex Project
===

The name **Elvex** encompasses the name of a **software**, the name of a Natural Text Generation (NLG) **algorithm**, the name of the **language** used to write natural language grammars and the name of a **linguistic formalism** for NLG.

What can you do with Elvex software?
-----------------------------

- **Write relevant and adequate texts**: Write automatically and quickly relevant and adequate texts in natural language, given a meaning and elements of speech. 

- **Avoid any misunderstanding**: Rest assured that **Elvex** avoids any misunderstanding, and it achieves this without the need for any training data. 

- **Efficient Resource Utilization**: Migrate this solution to an embedded system with limited resources and no connection to a massive data server.

What you cannot do with Elvex software?
-----------------------------

- **Contextual Adaptability**: Contextual Adaptability: Elvex, as a rule-based generator, is not designed for completing texts or deriving meaning from existing text. Instead, its strength lies in producing structured text based on provided meanings and enunciative situations. It operates within the confines of its predefined rules and may not perform well in situations requiring interpretation or adaptation beyond these rules. Its capabilities are centered around generating text from clear, specified contexts rather than inferring or adding context to partial or ambiguous inputs.

- **Learning from Data**: Unlike AI-driven models, Elvex does not learn from data over time. It cannot evolve or improve its outputs based on new information unless manually updated or reprogrammed with new rules.

- **Creativity and Innovation**: The software's capacity for creativity is limited to the boundaries of its rules. It cannot generate truly novel ideas or creative outputs that require 'thinking outside the box'.

Generative AI Language Model Comparison
-----------------------------

| **Elvex**                               | **Generative AI Language Model**                   |
|-----------------------------------------|-----------------------------------------------|
| - No Bias                                | - Potential biases in training data            |
| - Effective Input Context Handling       | - Limited contextual understanding            |
| - Cost Efficiency                        | - High development costs                      |
| - Environmental Sustainability           | - Significant environmental impact            |
| - Complex Grammar                        | - Lack of structured grammar                  |
| - Extensive Vocabulary                    | - Limited or no defined vocabulary             |


In practical terms, how can you use Elvex to build a Text Generator for an application (such as a Chatbot, Letter-writer, etc)?
--------------------

To use **Elvex** software for your purpose, you first need to create a **lexicon** and **grammatical rules** by using the **Elvex language** and adhering to the **Elvex formalism**.

The inputs will depend on the grammar built for your application, encompassing both the meaning and the enunciative intent.

a) The **lexicon**

Each time you want to use a word, it needs to be thoroughly defined in the lexicon, which can vary depending on the specific domain. This entails describing every word you intend to generate. Writing entries for all the basic words, compounds, and idiomatic phrases can be a time-consuming and expensive endeavor. Typically, this process takes several weeks to several months for one person in a specific domain.

**Elvex** is designed to compute huge lexicons (with hundreds of thousands of forms, tens of thousands of lemmas and lexemes, and hundreds of parts of speech) by distinguishing morphological forms from lemmas and lexemes.

b) The **grammatical rules**

In addition to the lexicon, you will also need to create a natural language grammar. This grammar serves as the language model for the NLG.

Elvex software
=====

**Elvex** is a **Natural Text Generator** engine written in C++ language

It is written by Lionel Clément at Bordeaux University - France and released by LaBRI under GNU GPL License.

**Elvex** uses custom-written lexicons and grammatical rules as file parameters, along with a **feature structure** as input. The lexicons and grammatical rules serve as linguistic resources used for sentence generation, while the **feature structure** represents the content to be expressed.

In the end, **Elvex** generates texts in Natural Language that accurately mirrors the input while adhering to the grammar's syntactic and lexical rules.

While **Elvex** is an Artificial Intelligence program, it operates without the need for extensive neural network training data, and its processes are fully deterministic, devoid of any randomness.

License
-------

The **Elvex** software is released under GNU GPL License V3.

In other words

- The source code must be made available when the software is distributed
- A copy of the license and the copyright manual must be included with the software
- Modifications must be released under the same license when the software is distributed. A similar or a related license must be used
- Changes made to the code must be documented

The language of **Elvex** formalism is not under licence (it belongs to the public domain), so the data you will write (new grammars, new lexicons) are not part of **Elvex software**.

Elvex language
=====

The lexicons, grammatical rules, and the content to be expressed are all described using the **Elvex language**, which is detailed in the manual documentation.

Elvex algorithm
=====

Given a feature structure (FS) that represents the content to be expressed, **Elvex** constructs a tagged shared forest whose boundary is the generated texts. The shared forest (which actually is a context-free grammar) is tagged with synthesized and inherited FS on each node. The synthesized FS constrain rules based on local properties (typically lexical properties), while inherited FS constrain local structures based on their context (typically semantical properties).

Key Algorithms Used in Developing **Elvex**:

-Equations and inequalities on FSs resolved through unification.

-Equivalence classes defined by an equivalence relation among items (NLG stages). This uses hash coding to build sets and maps.

-New NLG algorithm close to dynamic chart parsing algorithms.

-Dynamic programmation with memoization on serializable data.

The **Elvex** algorithm is deterministic and monotonic (each rule adds something and never removes the effect of the other rules).

The complexity of constructing the shared forest is $O(n^3)$, while the complexity of unifying and writing the boundaries becomes exponential due to combinatorial factors. This complexity can be reduced through a systematic approach to writing grammars to avoid combinatorial explosion.

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

Some of the most difficult stuff already done with Elvex
=====

- **Adjective order in English**

	*big yellow squared stuff*\
  	**squared yellow big stuff*

- **French slang language**
	
```python
   text [HEAD:TO_SELL,  
       i:[HEAD:HUMAN, number:sg, gender:fm],  
       ii:[HEAD:TROUBLESOME, number:sg, gender:ms, lexical_function:magn],  
       iii:[HEAD:CAR, number:sg, mod:<[HEAD:BROKEN]>],  
       language_register:slang]
```

=>
(Warning: This is explicit content)

"*La nana a fourgué une chiotte ruinée à un grand casse-burnes.*"\
"*La gosse a bicravé une chiotte naze à un putain d'emmerdeur.*"\
"*La nana a bicravé une tire explosée à un sale chieur.*"\
"*La nana a bicravé une tire fusillée à un grand casse-burnes.*"\
"*La gosse a bicravé une bagnole en bouillie à un gros boulet.*"\
"*La donzelle a bicravé une chiotte explosée à un grand casse-couilles.*"\
"*La meuf a bicravé une bagnole fusillée à un gros boulet.*"\
"*La gonzesse a camelotté une bagnole rétamée à un putain d'emmerdeur.*"\
"*La moukère a camelotté une bagnole ruinée à un grand casse-couilles.*"\
"*La meuf a bicravé une chignole en bouillie à un sale chieur.*"\
"*La gonzesse a bicravé une caisse en bouillie à un grand
casse-bonbons.*"

(something like "*The girl peddled a shot-up car to a major pain in the neck.*")

- **Anaphora resolution process between sentences with pronouns, synonyms and hypernyms, and more things in this more comprehensive example**
	
```
text [HEAD:TO_CAUSE, // Something(i) causes an effect(ii)
    i:[HEAD:TO_REPAIR, // Someone(i) repairs something(ii)
        i:[HEAD:MECHANIC, ID:1, number:sg, gender:ms, def:yes], // "1" is the identifier for the mechanic.
                   //We will now use 'ID:1' to refer to this entity.
        ii:[HEAD:CAR, number:sg, GEN:[HEAD:EGO], ID:3], // The genitive relationship of CAR is with EGO.
                   //"3" is the identifier for CAR.
        time:past // The repair action is in the past.
    ],
    ii:[HEAD:TO_PICK_UP, // Someone(i) picks up something(ii) somewhere(iii)
        i:_, // We don't create an entity for (i).
        ii:[ID:3], // (ii) co-refers to CAR.
        iii:[HEAD:GARAGE, GEN:[ID:1]], // The genitive relationship of GARAGE is with an element that
                    //co-refers to MECHANIC.
        modality:ability, // Modality: ability.
        time:tomorrow // The pick-up action will occur tomorrow.
    ]
]
```

=>

*Le garagiste a réparé ma voiture, on pourra récupérer **le véhicule** dans **son** garage demain.* (The mechanic has repaired my car, and we'll be able to pick it up from his garage to)

- **Complex idiomatic phrases**

	*They had **to bite the bullet** and face the overwhelming tasks ahead.*

- **Past participle aggrement in French with transitive verbs**

	*La lettre qu'a écrit Paul* (Paul's letter)\
	*La lettre que Paul a écrit**e*** (The letter Paul wrote)\
	*Paul a écrit la lettre* (Paul wrote the letter)

- **Lexical functions (based on Mel'čuk theory)**

	*Un **gros** fumeur* (A ++ smoker, litteraly **big** smoker)\
	*Un **grand** admirateur* (A ++ fan, litteraly **tail** fan)\
	*Un argument **solide*** (A ++ argument, litteraly **strong** argument)

- **Coordinations with Right-Node Raising and Gapping**
	
	*Les étudiants empruntent des livres sur 15 jours, alors que les enseignants sur 3 semaines.* (Students borrow books for 15 days, while teachers borrow them for 3 weeks.)

- **Morphology in standard Breton**

```python
text [HEAD:HOUSE]
```
=>
*tier / kalz a dier / un ti / an ti / hon tier / da dier / hon ti / ho ti / ma zi / o zi / ho tier / o zier / da di / ma zier / he zier / e tier / he zi / e ti*


A NLG problem solved with *Elvex*: Causal clauses in a little French Grammar
-----------------------------------------------

In French, the basis of verbal tense and the conclusion of a causal clause depend on the aspect, the tense and even on the differences in language registers of a sentence:

- present:
if present => future
- colloquial French for the present or future:
conditional without "if" => conditional
- past:
if past => past conditional
- colloquial French for the past:
past conditional without "if" => past conditional
- future:
 Imperfect => conditional

We have authored French grammar rules to handle causality. Here are the generation results using **Elvex**; please note that the English translations are done manually and not automatically:

Neutral
---
**text [HEAD:cause, i:[HEAD:to_rain], ii:[HEAD:umbrella, i:[HEAD:_you]]**

*S'il pleut, tu prendras un parapluie.*
(If it rains, you will take an umbrella.)

Slang language
---
**text [HEAD:cause, i:[HEAD:rain], ii:[HEAD:umbrella, i:[HEAD:_you]], language_register:slang_language]**

*Il flotterait, tu prendrais un pépin.*
(If it were drizzling, you would take a brolly.)

Continuous present
---
**text [HEAD:cause, i:[HEAD:rain], ii:[HEAD:umbrella, i:[HEAD:_you]], tense:present, aspect:continuous]**

*S'il est en train de pleuvoir, tu prendras un parapluie.*
(If it is raining, you will take an umbrella.)

Question
---
**text [HEAD:cause, i:[HEAD:rain], ii:[HEAD:umbrella, illocutionary:ask, i:[HEAD:_you]]**

*S'il pleut, est-ce que tu prendras un parapluie ?*
(If it rains, will you take an umbrella?)

Past
---
**text [HEAD:cause, i:[HEAD:rain], ii:[HEAD:umbrella, i:[HEAD:_you]], tense:past]**

*S'il avait plu, tu aurais pris un parapluie.*
(If it had rained, you would have taken an umbrella.)

Past & colloquial language
---
**text [HEAD:cause, i:[HEAD:rain], ii:[HEAD:umbrella, i:[HEAD:_you]], tense:past, language_register:colloquial]**

*Il aurait plu, tu aurais pris un parapluie.*
(If it had been raining, you would have taken an umbrella.)

Continuous past
---
**text [HEAD:cause, i:[HEAD:rain], ii:[HEAD:umbrella, i:[HEAD:_you]], tense:past, aspect:continuous]**

*S'il était en train de pleuvoir, tu aurais pris un parapluie.*
(If it were raining, you would have taken an umbrella.)

Future
---
**text [HEAD:cause, i:[HEAD:rain], ii:[HEAD:umbrella, i:[HEAD:_you]], tense:future]**

*S'il pleuvait, tu prendrais un parapluie.*
(If it were raining, you would take an umbrella.)

Continuous future
---
**text [HEAD:cause, i:[HEAD:rain], ii:[HEAD:umbrella, i:[HEAD:_you]], tense:future, aspect:continuous]**

*S'il était en train de pleuvoir, tu prendrais un parapluie.*
(If it were raining, you would take an umbrella.)
