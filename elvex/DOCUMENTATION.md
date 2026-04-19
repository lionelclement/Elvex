# ELVEX Interface — Field Documentation

This page explains the purpose of each field in the ELVEX interface.

---

## General Workflow

1. Define linguistic resources (Macros, Rules, Lexicon…)
2. Provide an Input (feature structure)
3. Run ELVEX
4. Read the generated Output

---

## Fields Description

### 1. Macros

Reusable shortcuts used inside rules.

* Define common structures or patterns
* Improve readability and maintainability

Example:

```
@s=	[number:singular];
@p=	[number:plural];
@m=	[gender:masc];
@f=	[gender:fem];
@ms= [@m, @s];
@mp= [@m, @p];
@fs= [@f, @s];
@fp= [@f, @p];
```

---

### 2. Rules

Core of the grammar.

* Describe constituent structures
* Describe constraints and functional structures

Example:

```
S → NP|cln VP dot
{
  [i:$i]; 
  // Check that the input (↑) contains attribute "i" and store it in $i

  ↓1 = $i; 
  // Pass $i to the first child (NP or cln)

  [number:$number, person:$person, selectional_restriction:$selectional_restriction] ⊂ ⇓1; 
  // Read features from child 1 and store them in variables

  ↓2 = ↑ U [SUBJ:[number:$number, person:$person, selectional_restriction:$selectional_restriction]]; 
  // Build the VP using the parent FS + subject features

  ↓3 = []; 
  // Give an empty structure to "dot"
}
```


---

### 3. Lexicon

Defines all words used by the system.

Each entry includes:

* lemma
* part of speech
* morphological features

Example:

```
dog    noun    DOG    [HEAD:DOG, @ms, selectional_restriction:[@anim]]
```

---

### 4. Pattern

Used to generate a lexicon automatically.

* High-level description of lexical entries
* Compiled using `elvexlexicon`

Example:

```
DOG	noun	CHIEN	[selectional_restriction:[@anim, domestic:yes, sound:hurler | aboyer | japper]]
DOG	noun	CHIOT	[selectional_restriction:[@anim, domestic:yes, sound:japper]]
```

---

### 5. Morpho

Used to generate a lexicon automatically.

* High-level description of lexical entries
* Compiled using `elvexlexicon`

Defines morphological transformations.

* Morphological variants of words

Example:

```
chien	noun	CHIEN	[@ms]
chienne	noun	CHIEN	[@fs]
chiens	noun	CHIEN	[@mp]
chiennes	noun	CHIEN	[@fp]
chiot	noun	CHIOT	[@ms]
chiots	noun	CHIOT	[@mp]
```

---

### 6. PostMorpho

Applied after morphology.

* Final adjustments
* Cleanup rules
* Orthographic corrections

Example:

```
(^| )de le => \1du
(^| )de les => \1des
(^| )à le => \1au
(^| )à les => \1aux
(^| )le (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1l'\2
(^| )la (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1l'\2
(^| )de (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1d'\2
(^| )je (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1j'\2
(^| )me (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1m'\2
(^| )te (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1t'\2
(^| )se (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1s'\2
(^| )ne (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1n'\2
(^| )que (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1qu'\2
(^| )ce (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1c'\2
(^| )si il => \1s'il
(^| )si ils => \1s'ils
^(.) => upper(\1)
\ \. => .
```

---

### 7. Input

Defines the meaning to express.

This is a **feature structure (FS)**.

Example:

```
S [HEAD:TO_BARK, i:[HEAD:DOG]]
```

This input is interpreted by the grammar to produce a phrase or a sentence.

---

## Output

* Generated natural language text
* Deterministic result

---

## Log

* Detailed execution trace (if enabled)
* Useful for debugging grammar or lexicon issues

---

## Notes

* Empty lines and comments (`//`) are allowed
* Comments are ignored during processing
* Be careful with consistency between:

  * Rules
  * Lexicon
  * Input

---

## Typical Workflow Example

1. Define Lexicon entries
2. Write Rules
3. Add Input structure
4. Click **Run ELVEX**
5. Inspect Output and Errors

---

## Tips

* Start with small grammars
* Test incrementally
* Use Logs to debug
* Keep rules specific to avoid combinatorial explosion

---

➡️ ELVEX is powerful but requires precise linguistic modeling.
