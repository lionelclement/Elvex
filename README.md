# ELVEX Web Interface

## What is this interface?

This web interface is a lightweight environment designed to **experiment with ELVEX grammars directly in your browser**.

It allows you to:

* Create and manage projects
* Edit some ELVEX resources (Macros, Rules, Lexicon, Pattern, Morpho, etc.)
* Run the ELVEX engine without leaving the interface
* Inspect outputs, errors, and execution traces
* Iterate quickly on grammar design

➡️ The goal is to provide a **practical workspace for grammar engineering**, not just a command-line tool.

---

## What is ELVEX?

**ELVEX** is a rule-based Natural Language Generation (NLG) system.

* It generates text from:

  * a **lexicon**
  * **grammar rules**
  * a structured **input (feature structure)**

* It is:

  * deterministic
  * ensuring consistent and predictable outcomes for a given input
  * independent from training data

👉 Source code and full project:
GitHub → https://github.com/lionelclement/Elvex

---

## What can you do here?

With this interface, you can:

* Build your own text generators
* Test linguistic rules interactively
* Debug grammars step by step
* Explore how inputs are transformed into sentences

Typical use cases:

* Controlled text generation
* Linguistic prototyping
* Educational purposes
* Domain-specific generators (chatbots, reports, etc.)

---

## How to use it

1. Sign in to use the project editor
2. Go to **Projects**
3. Create a new project
4. Fill in the different fields (Rules, Lexicon, Input, etc.)
5. Click **Run ELVEX**
6. Check:

   * Output (generated text)
   * Errors (if any)
   * Logs (for debugging)

---

## Philosophy

This interface follows the philosophy of ELVEX:

* **Explicit rules instead of statistical models and LLM**
* **Control over generation**
* **Reproducibility and transparency**

---

## Important note

This is **not a generative AI model**:

* It does not learn
* It does not guess
* It only produces what is explicitly described

➡️ The quality of the output depends entirely on the grammar you write — no more, no less.

---

## Next step

👉 Read the **Documentation** section to understand each field and start building your first generator.

[1]: https://github.com/lionelclement/Elvex?utm_source=chatgpt.com "lionelclement/Elvex: A Natural Language Generation System"
