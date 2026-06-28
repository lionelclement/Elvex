# v35 args-based WebNLG sequences

This version removes list-valued `triples:<...>` sequence inputs.
Multi-triple inputs now use named arguments:

```elvex
S [HEAD:webnlg_sequence, size:2, i:T1, ii:T2]
S [HEAD:webnlg_sequence, size:3, i:T1, ii:T2, iii:T3]
```

The sequence rules in `user/rules/webnlg_sequence.rules` were updated to read
`i`, `ii`, `iii`, `iv`, and `v`.  The exact duplicate size-2 rule now matches
`i:$T1, ii:$T1` and realizes the triple only once.
