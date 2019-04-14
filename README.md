# Elvex
A Natural Language Generation engine

Elvex is an Natural Text Generator. It takes as an input a concept, a local lexicon, a compacted lexicon, and a grammar, and then outputs a text corresponding to the concept writing in Natural Language.

A little exemple in French grammar: causal clause with tense aggrement.

// present
Start [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]]]
--------------------------------------------------------
S'il pleut, tu prendras un parapluie.

Start [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], tense:present, aspect:continuous]
--------------------------------------------------------
S'il est en train de pleuvoir, tu prendras un parapluie.

Start [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, illocutionary:ask, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]]]
--------------------------------------------------------
S'il pleut, est-ce que tu prendras un parapluie ?

//past
Start [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], tense:past]
--------------------------------------------------------
S'il avait plu, tu aurais pris un parapluie.

Start [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], tense:past, aspect:continuous]
--------------------------------------------------------
S'il était en train de pleuvoir, tu aurais pris un parapluie.


//future
Start [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], tense:future]
--------------------------------------------------------
S'il pleuvait, tu prendrais un parapluie.

Start [PRED:cause, i:[PRED:to_rain], ii:[PRED:to_take, i:[PRED:_you], ii:[PRED:umbrella, def:no, number:sg]], tense:future, aspect:continuous]
--------------------------------------------------------
S'il était en train de pleuvoir, tu prendrais un parapluie.

