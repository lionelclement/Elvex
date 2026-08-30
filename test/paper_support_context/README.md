# English support-verb context experiment

This test follows the style of the simple Elvex grammars: the lexicon contains
only lexical items, while syntax and information flow are in `.rules`.

## Linguistic phenomenon

The semantic input specifies only `HEAD:ATTENTION` for the object. The local
lexicon offers two realizations:

- `attention` -> `[support:PAY]`
- `notice` -> `[support:TAKE]`

The corresponding support verbs are:

- `pays` -> `[HEAD:PAY]`
- `takes` -> `[HEAD:TAKE]`

The FULL grammar has the surface rule `VP -> V NP`, but only the inherited
structure of the object NP is initially available. Once that NP has been
realized, its synthesized `support` feature determines the inherited `HEAD` of
V. Thus computation proceeds NP-before-V while surface order remains V-before-NP.

Expected FULL realizations for N=1 are:

    John pays attention .
    John takes notice .

The NO-CONTEXT grammar removes only the reuse of the synthesized `support`
feature. It therefore also licenses the collocationally invalid combinations:

    John pays notice .
    John takes attention .

## Scaling

`N1.input` ... `N5.input` repeat the same sentence template 1 to 5 times.
With two lexical choices per clause:

- FULL: 2^N outputs, all collocationally valid.
- NO-CONTEXT: 4^N outputs, of which 2^N are valid.
- Valid fraction without synthesized-context reuse: (1/2)^N.
- Contextual pruning factor: 2^N.

This gives a controlled ablation for the paper and can be combined with the
instrumented metrics: runtime, chart items, packed nodes, saturation passes, etc.

## Run

From the project root, with metrics enabled:

    test/paper_support_context/run.sh ./bin/elvex

or from this directory:

    ./run.sh /absolute/path/to/bin/elvex

The script writes `results.tsv`.
