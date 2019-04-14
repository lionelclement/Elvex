# Elvex
A Natural Language Generation engine

Elvex is an Natural Text Generator. It takes as an input a concept, a local lexicon, a compacted lexicon, and a grammar, and then outputs a text corresponding to the concept writing in Natural Language.

A little exemple in French grammar: causal clause with tense aggrement.

input:
// present
Start [PRED:cause, i:[PRED:pleuvoir], ii:[PRED:prendre, i:[PRED:_you], ii:[PRED:parapluie, def:no, number:sg]]]
--------------------------------------------------------
S'il pleut, alors tu prendras un parapluie.

Start [PRED:cause, i:[PRED:pleuvoir], ii:[PRED:prendre, i:[PRED:_you], ii:[PRED:parapluie, def:no, number:sg]], tense:present, aspect:continuous]
--------------------------------------------------------
S'il est en train de pleuvoir, alors tu prendras un parapluie.

Start [PRED:cause, i:[PRED:pleuvoir], ii:[PRED:prendre, illocutionary:ask, i:[PRED:_you], ii:[PRED:parapluie, def:no, number:sg]]]
--------------------------------------------------------
S'il pleut, alors est-ce que tu prendras un parapluie ?

//past
Start [PRED:cause, i:[PRED:pleuvoir], ii:[PRED:prendre, i:[PRED:_you], ii:[PRED:parapluie, def:no, number:sg]], tense:past]
--------------------------------------------------------
S'il avait plu, alors tu aurais pris un parapluie.

Start [PRED:cause, i:[PRED:pleuvoir], ii:[PRED:prendre, i:[PRED:_you], ii:[PRED:parapluie, def:no, number:sg]], tense:past, aspect:continuous]
--------------------------------------------------------
S'il était en train de pleuvoir, alors tu aurais pris un parapluie.


//future
Start [PRED:cause, i:[PRED:pleuvoir], ii:[PRED:prendre, i:[PRED:_you], ii:[PRED:parapluie, def:no, number:sg]], tense:future]
--------------------------------------------------------
S'il pleuvait, alors tu prendrais un parapluie.

Start [PRED:cause, i:[PRED:pleuvoir], ii:[PRED:prendre, i:[PRED:_you], ii:[PRED:parapluie, def:no, number:sg]], tense:future, aspect:continuous]
--------------------------------------------------------
S'il était en train de pleuvoir, alors tu prendrais un parapluie.

