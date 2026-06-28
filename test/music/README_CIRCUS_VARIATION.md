# Circus variation module

This version keeps the circus material structured rather than direct/ad-hoc.

## Main idea

The input still asks for:

```txt
form:circus_fanfare_8
rhythm:[topic:circus_galop, ostinato:oom_pah, articulation:staccato]
```

The rules then derive a shared 8-bar form:

```txt
A  A'  B  cadence
```

Each section has two measures. The same formal plan is realized differently by the generic roles:

- `lead`: principal call / answering call / contrast / cadence
- `countermelody`: short turns and echoes, with rests
- `harmonic_support`: brass fanfare calls
- `accent`: low brass afterbeats and answers
- `bass`: oom-pah bass with subdominant and dominant variants
- `rhythmic_pedal`: percussion pulse, breaks and cadential roll

## Why it should be less repetitive

The previous output used too many measures of plain eighth notes.
This correction keeps the same musical functions but adds local randomized alternatives:

```txt
$r = rand() % 100;
if ($r < 55) { ... } else { ... }
```

The alternatives change rhythm, register, and contour while preserving the same function.
For example, a tonic call may be a plain arpeggio, a dotted rhythm, or a dominant-upbeat call.

## Recommended tests

```bash
make 900_circus_sax_clarinet_brass_perc.ly
make 900_circus_sax_clarinet_brass_perc.pdf
```

To inspect Elvex directly:

```bash
elvex \
  --verbose \
  --trace-all \
  --max-time 20 \
  --max-usages 300 \
  --max-items 5000 \
  --rules-file music.rules \
  --lexicon-file music.lexicon \
  --input-file 900_circus_sax_clarinet_brass_perc.input \
  > 900_circus_sax_clarinet_brass_perc.ly \
  2> elvex_circus.trace.err
```

## Tempo

The example input is kept at `bpm:96`, because `168` was too fast.
If the result feels too slow but otherwise correct, try `bpm:108` or `bpm:112`.
