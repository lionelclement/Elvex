

## Size-2 duplicate gating

The general size:2 coordination rule now requires `distinct:true`, which is emitted by `scripts/generate_inputs.py` only for non-identical pairs. Exact duplicate pairs therefore match only the deduplication rule.
