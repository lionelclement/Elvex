# Music `.input` authoring guide

This guide documents the feature structures used by the music-generation examples in ELVEX. An `.input` file specifies a piece of music—its title, style, form, rhythm, instrumentation, key and meter. The accompanying grammar transforms those features into LilyPond (`.ly`) notation.

The field names and enumeration values shown below are **ELVEX grammar identifiers**. Keep them exactly as written, even when they contain French words such as `chanson_francaise`. They are not natural-language prose and translating them would break grammar matching.

## 1. Reading ELVEX grammar rules

The `.rules` files describe how musical features are converted to LilyPond fragments. A typical rule has this shape:

```text
A → B C
{
  [feature:value, feature:$variable, $remaining_features];
    // Filter the attributes inherited by this rule.
    // Variables are bound by unification for later reuse.

  [feature:$variable, $remaining_features] ⊂ ↑;
    // Extract values from the inherited feature structure.

  ↓1 = ↑ ∪ [...];
    // Set the features inherited by the first child.

  ↓2 = ↑ ∪ [...];
    // Set the features inherited by the second child.

  ... ⇓1 ...;
    // Read the features synthesized by the first child.

  ... ⇓2 ...;
    // Read the features synthesized by the second child.

  ⇑ = ...;
    // Set the features synthesized by this rule.
}
```

| Symbol | Meaning |
| --- | --- |
| `↑` | Features inherited by the current rule |
| `↓1`, `↓2`, ... | Inherited features passed to each child |
| `⇓1`, `⇓2`, ... | Features synthesized by each child |
| `⇑` | Features synthesized by the current rule |

High-level modules select musical structures or instrumentation; lower-level modules construct measures, notes, chords, rests and LilyPond fragments.

## 2. Overall input structure

The root symbol is always `PIECE`. An input typically has the following structure:

```text
PIECE [
  generation:[syntax:instrument_roles, strict:false, fallback:true],
  title:"Piece title",
  composer:"Composer name",
  bpm:96,
  music:[...],
  ensemble:[...],
  key:[...],
  meter:[...]
]
```

Musical settings should not be chosen independently: `style`, `form`, `phrase_model` and the rhythm attributes must form a compatible combination. For example, a classical gigue commonly uses:

```text
style:classical_19c
form:long_gigue
phrase_model:periodic
rhythm:[topic:gallop, dance:gigue, density:active, articulation:detached]
```

A French verse/chorus song typically uses:

```text
style:chanson_francaise
form:chanson_francaise_couplet_refrain
phrase_model:verse_chorus
rhythm:[topic:chanson_syllabic, dance:none, density:medium, articulation:legato]
```

Start from a recommended profile (section 7), then change only the parameters needed by your piece.

## 3. `generation` and metadata

```text
generation:[syntax:instrument_roles, strict:false, fallback:true]
```

| Field | Values | Purpose |
| --- | --- | --- |
| `syntax` | `instrument_roles` | Public syntax: instruments are described by identifier, family and musical role |
| `strict` | `true`, `false` | With `false`, the grammar may fill certain missing fields with defaults |
| `fallback` | `true`, `false` | With `true`, a generic realization may be used when a specialized case is unavailable |

Recommended settings: `generation:[syntax:instrument_roles, strict:false, fallback:true]`.

```text
title:"Etude in G",
composer:"ELVEX",
bpm:96
```

| Field | Example | Purpose |
| --- | --- | --- |
| `title` | `"Etude in G"` | Title printed in the LilyPond score |
| `composer` | `"ELVEX"` | Composer printed in the score header |
| `bpm` | `96` | MIDI tempo and general tempo indication |

Typical tempo ranges are 60–84 BPM for slow studies, sicilianas and ballads; 88–112 for moderate classical works; 104–128 for marches, pop and chansons; and 120–144 for gigues and active rock.

## 4. The `music` block

```text
music:[
  style:classical_19c,
  form:rounded_binary,
  phrase_model:periodic,
  rhythm:[...]
]
```

### Styles

| `style` value | Use |
| --- | --- |
| `classical_19c` | Classical forms, dance movements, studies and instrumental works |
| `pop_60s_80s` | Verse/chorus pop with accompaniment |
| `chanson_francaise` | French chanson with voice or melodic lead and accompaniment |
| `rock` | Rock band, backbeat, guitar, bass and drums |

### Forms (`form`)

The supported forms depend on `style`. Preserve the exact form identifiers in input files.

| Classical form | Intended use |
| --- | --- |
| `scales` | Scale studies |
| `rounded_binary` | Short rounded binary form |
| `ternary` | Simple ABA form |
| `minuet_trio` | Minuet and trio |
| `theme_and_variations` | Theme and variations |
| `long_rounded_binary` | Extended rounded binary form |
| `long_ternary` | Extended ABA form |
| `long_theme_and_variations` | Extended theme and variations |
| `long_siciliana` | Long siciliana |
| `long_gigue` | Long gigue |
| `long_march` | Long march |
| `formal_long_rounded_binary` | Formalized extended rounded binary |
| `formal_long_ternary` | Formalized extended ABA |
| `formal_long_theme_and_variations` | Formalized extended theme and variations |
| `formal_long_siciliana` | Formalized long siciliana |
| `formal_long_gigue` | Formalized long gigue |
| `formal_long_march` | Formalized long march |

| Pop form | Intended use |
| --- | --- |
| `pop_song_verse_chorus` | Verse/chorus pop song |

| French chanson form | Intended use |
| --- | --- |
| `chanson_francaise_couplet_refrain` | Standard verse/chorus chanson |
| `chanson_francaise_couplet_refrain_lyrique` | Lyrical, more fully sung variant |
| `chanson_francaise_couplet_refrain_parle` | Spoken/recitative variant |
| `chanson_francaise_couplet_refrain_nostalgique` | Nostalgic variant |
| `chanson_francaise_couplet_refrain_refrain_hook` | Hook-led refrain |
| `chanson_francaise_couplet_refrain_recit_bas` | Lower-register recitative |
| `chanson_francaise_couplet_refrain_grande_arche` | Broad melodic arch |
| `chanson_francaise_couplet_refrain_hook_syncopated` | Syncopated hook |
| `chanson_francaise_couplet_refrain_descendante` | Descending melodic line |

| Rock form | Intended use |
| --- | --- |
| `rock_song_verse_chorus` | Verse/chorus rock band |
| `rock_song_sax_choir` | Rock band with saxophone and choir |
| `rock_direct_band` | Direct rock-band scoring |
| `rock_direct_sax_choir` | Direct rock scoring with saxophone and choir |

### Phrase models (`phrase_model`)

| Value | Typical style | Use |
| --- | --- | --- |
| `periodic` | `classical_19c` | Regular antecedent/consequent phrasing and classical periods |
| `verse_chorus` | `pop_60s_80s`, `chanson_francaise`, `rock` | Verse/chorus organization |

### Rhythm (`rhythm`)

```text
rhythm:[
  topic:neutral,
  dance:none,
  density:medium,
  anacrusis:false,
  hemiola_at_cadence:false,
  ostinato:none,
  articulation:neutral
]
```

| `topic` value | Intended use |
| --- | --- |
| `neutral` | Safe neutral rhythm for general classical forms |
| `siciliana` | Gently swaying siciliana |
| `gallop` | Active triple-meter movement or gigue |
| `march` | March |
| `dotted` | Dotted rhythms |
| `lombard` | Lombard rhythm |
| `syncopation` | Syncopation |
| `sarabande` | Sarabande |
| `pop_backbeat` | Pop backbeat |
| `pop_ballad` | Pop ballad |
| `chanson_syllabic` | Syllabic chanson |
| `chanson_acoustic` | Acoustic chanson accompaniment |
| `chanson_lyrique` | Lyrical chanson |
| `chanson_parlee` | Spoken or recitative chanson |
| `chanson_nostalgique` | Nostalgic chanson |
| `chanson_hook` | Chanson with a prominent hook |
| `rock_backbeat` | Rock backbeat |
| `classic_rock_backbeat` | Classic rock |

Some internal rhythm topics target individual instrumental parts, for example `piano_acc_siciliana_rh`, `piano_acc_siciliana_lh`, `gallop_support` and `march_support`. Use the general topics above for public inputs.

| `dance` | Use |
| --- | --- |
| `none` | No explicit dance |
| `gigue` | Use with `topic:gallop` and a gigue form |
| `sarabande` | Use with `topic:dotted` or `topic:sarabande` |
| `minuet` | Use with `form:minuet_trio` |

| `density` | Use |
| --- | --- |
| `sparse` | Very few notes and an open texture |
| `light` | Light texture |
| `low_medium` | Between light and medium; useful for restrained accompaniment |
| `medium` | Standard density |
| `active` | More animated writing |

| `articulation` | Use |
| --- | --- |
| `neutral` | No specialized articulation |
| `slurred` | Smooth, singing line |
| `detached` | Detached notes, for a gigue or lively dance |
| `marked` | Strongly articulated, for a march or sarabande |
| `legato` | Connected, singing pop or chanson |
| `accented` | Accents, rock or strong march |

| Other rhythm field | Typical values | Purpose |
| --- | --- | --- |
| `anacrusis` | `true`, `false` | Pickup before the first full measure |
| `hemiola_at_cadence` | `true`, `false` | Hemiola near a cadence |
| `ostinato` | `none`, `guitar_strum`, `guitar_riff` | Repeated pattern or accompaniment |

## 5. The `ensemble` block

The `ensemble.instruments` structure contains indexed entries `i1`, `i2`, `i3`, etc. **`count` is mandatory** and must equal the number of instruments declared. It makes grammar dispatch deterministic, so the grammar can select the `count:1`, `count:2`, `count:3` case directly.

For one instrument:

```text
ensemble:[
  instruments:[
    count:1,
    i1:[id:flute, name:"Flute", family:woodwind, role:flute1, midi:"flute", clef:treble, octave:5, dynamic:mf]
  ]
]
```

For three instruments:

```text
ensemble:[
  instruments:[
    count:3,
    i1:[id:flute, name:"Flute", family:woodwind, role:flute_piano_lead, midi:"flute", clef:treble, octave:5, dynamic:mf],
    i2:[id:piano_rh, name:"Piano RH", family:keyboard, role:piano_acc_rh, midi:"acoustic grand", clef:treble, octave:4, dynamic:mp],
    i3:[id:piano_lh, name:"Piano LH", family:keyboard, role:piano_acc_lh, midi:"acoustic grand", clef:bass, octave:3, dynamic:p]
  ]
]
```

If you declare `i1`, `i2` and `i3`, write `count:3`; with `i1` through `i4`, write `count:4`.

| Instrument field | Example | Purpose |
| --- | --- | --- |
| `id` | `flute`, `piano_rh` | Readable internal identifier |
| `name` | `"Flute"` | Name displayed in the score |
| `family` | `woodwind` | Instrument family |
| `role` | `lead` | Musical role |
| `midi` | `"flute"` | LilyPond MIDI instrument |
| `clef` | `treble` | Staff clef |
| `octave` | `5` | Principal register |
| `dynamic` | `mf` | Initial dynamic |

| `family` value | Instruments |
| --- | --- |
| `woodwind` | Flute, clarinet, oboe and saxophone |
| `brass` | Brass instruments |
| `bowed_strings` | Violin, viola, cello and double bass |
| `plucked_strings` | Guitar, harp and plucked strings |
| `keyboard` | Piano or keyboard |
| `percussion` | Percussion and drums |
| `voice` | Voice or vocal guide |
| `electric_bass` | Electric bass |
| `electric_strings` | Electric strings |
| `free_reed` | Accordion, harmonica, etc. |
| `synth`, `synth_bass`, `synth_brass`, `synth_strings` | Synthesizer parts |

| General `role` | Purpose |
| --- | --- |
| `lead` | Main melody |
| `countermelody` | Countermelody |
| `inner_voice` | Inner voice |
| `bass` | Bass line |
| `harmonic_support` | Harmonic accompaniment |
| `rhythmic_pedal` | Pedal or rhythmic pattern |
| `accent`, `bass_accent`, `cadence_accent` | Local accent |
| `guitar` | General guitar part |
| `drum_kit` | Drum kit |

| Specialized `role` | Purpose |
| --- | --- |
| `flute1`, `flute2` | Flute parts in a duet |
| `flute_piano_lead` | Solo flute with piano accompaniment |
| `piano_rh`, `piano_lh` | Solo piano, right and left hands |
| `piano_acc_rh`, `piano_acc_lh` | Accompanying piano, right and left hands |
| `chanson_voice`, `chanson_guitar` | French chanson voice/guitar |
| `rock_voice`, `rock_guitar`, `rock_bass`, `rock_drums` | Rock band roles |
| `rock_sax`, `rock_choir` | Rock saxophone and choir |

| `clef` | Meaning |
| --- | --- |
| `treble` | Treble clef |
| `bass` | Bass clef |
| `alto` | Alto clef |
| `treble_8` | Octave-transposing treble clef, useful for guitar |
| `percussion` | Percussion clef |

| `dynamic` | Meaning |
| --- | --- |
| `p` | Piano (soft) |
| `mp` | Mezzo-piano |
| `mf` | Mezzo-forte |
| `f` | Forte (loud) |
| `ff` | Fortissimo |

## 6. Key and meter

The key is expressed with `tonic` and `mode`:

```text
key:[tonic:c, mode:major]
```

Common tonic values: `c`, `d`, `e`, `f`, `g`, `a`, `b`, `bes`, `ees`.

| Value | Pitch |
| --- | --- |
| `c` | C |
| `d` | D |
| `e` | E |
| `f` | F |
| `g` | G |
| `a` | A |
| `b` | B |
| `bes` | B-flat |
| `ees` | E-flat |

`mode` is either `major` or `minor`.

The meter is given by numerator and denominator:

```text
meter:[num:4, den:4]
```

| Meter | Common use |
| --- | --- |
| `meter:[num:4, den:4]` | General use, pop, rock or march |
| `meter:[num:3, den:4]` | Minuet, sarabande and triple-meter forms |
| `meter:[num:6, den:8]` | Siciliana, gigue and compound-metre movement |

## 7. Recommended complete `music` profiles

These are **combinations of existing fields**, not additional special syntax. Copy a compatible profile into the `music` block of your input.

### Neutral classical piece

```text
music:[
  style:classical_19c,
  form:rounded_binary,
  phrase_model:periodic,
  rhythm:[topic:neutral, dance:none, density:medium, anacrusis:false, hemiola_at_cadence:false, ostinato:none, articulation:neutral]
]
```

### Scale study

```text
music:[
  style:classical_19c,
  form:scales,
  phrase_model:periodic,
  rhythm:[topic:neutral, dance:none, density:medium, anacrusis:false, hemiola_at_cadence:false, ostinato:none, articulation:neutral]
]
```

### Classical siciliana

```text
music:[
  style:classical_19c,
  form:long_siciliana,
  phrase_model:periodic,
  rhythm:[topic:siciliana, dance:none, density:medium, anacrusis:false, hemiola_at_cadence:false, ostinato:none, articulation:slurred]
]
```

### Classical gigue

```text
music:[
  style:classical_19c,
  form:long_gigue,
  phrase_model:periodic,
  rhythm:[topic:gallop, dance:gigue, density:active, anacrusis:false, hemiola_at_cadence:false, ostinato:none, articulation:detached]
]
```

### Classical march

```text
music:[
  style:classical_19c,
  form:long_march,
  phrase_model:periodic,
  rhythm:[topic:march, dance:none, density:active, anacrusis:false, hemiola_at_cadence:false, ostinato:none, articulation:marked]
]
```

### Verse/chorus pop song

```text
music:[
  style:pop_60s_80s,
  form:pop_song_verse_chorus,
  phrase_model:verse_chorus,
  rhythm:[topic:pop_backbeat, dance:none, density:medium, anacrusis:false, hemiola_at_cadence:false, ostinato:guitar_strum, articulation:legato]
]
```

### Pop ballad

```text
music:[
  style:pop_60s_80s,
  form:pop_song_verse_chorus,
  phrase_model:verse_chorus,
  rhythm:[topic:pop_ballad, dance:none, density:low_medium, anacrusis:false, hemiola_at_cadence:false, ostinato:guitar_strum, articulation:legato]
]
```

### Lyrical French chanson

```text
music:[
  style:chanson_francaise,
  form:chanson_francaise_couplet_refrain_lyrique,
  phrase_model:verse_chorus,
  rhythm:[topic:chanson_lyrique, dance:none, density:medium, anacrusis:false, hemiola_at_cadence:false, ostinato:none, articulation:legato]
]
```

### Spoken French chanson

```text
music:[
  style:chanson_francaise,
  form:chanson_francaise_couplet_refrain_parle,
  phrase_model:verse_chorus,
  rhythm:[topic:chanson_parlee, dance:none, density:low_medium, anacrusis:false, hemiola_at_cadence:false, ostinato:none, articulation:legato]
]
```

### Classic rock

```text
music:[
  style:rock,
  form:rock_song_verse_chorus,
  phrase_model:verse_chorus,
  rhythm:[topic:rock_backbeat, dance:none, density:active, anacrusis:false, hemiola_at_cadence:false, ostinato:guitar_riff, articulation:accented]
]
```

### Rock with saxophone and choir

```text
music:[
  style:rock,
  form:rock_song_sax_choir,
  phrase_model:verse_chorus,
  rhythm:[topic:classic_rock_backbeat, dance:none, density:active, anacrusis:false, hemiola_at_cadence:false, ostinato:guitar_riff, articulation:accented]
]
```

## 8. Compatibility quick reference

| Style | Recommended forms | `phrase_model` | Typical rhythm topics |
| --- | --- | --- | --- |
| `classical_19c` | `scales`, `rounded_binary`, `ternary`, `minuet_trio`, `theme_and_variations`, `long_*`, `formal_long_*` | `periodic` | `neutral`, `siciliana`, `gallop`, `march`, `dotted`, `lombard`, `syncopation`, `sarabande` |
| `pop_60s_80s` | `pop_song_verse_chorus` | `verse_chorus` | `pop_backbeat`, `pop_ballad` |
| `chanson_francaise` | `chanson_francaise_couplet_refrain*` | `verse_chorus` | `chanson_syllabic`, `chanson_acoustic`, `chanson_lyrique`, `chanson_parlee`, `chanson_nostalgique`, `chanson_hook` |
| `rock` | `rock_song_verse_chorus`, `rock_song_sax_choir`, `rock_direct_band`, `rock_direct_sax_choir` | `verse_chorus` | `rock_backbeat`, `classic_rock_backbeat` |

## 9. Complete input examples

Ready-to-run examples are supplied as `sample_*.input` in this directory. They cover classical forms, sicilianas, gigues, marches, pop, French chansons and rock.

Build the desired example from `data/examples/music/`:

```sh
make sample_classical_gigue_flute_duet.ly
make sample_classical_gigue_flute_duet.pdf
```

See [README.md](README.md) for tool installation, target names and generated-file conventions.

## 10. Before running ELVEX

Check that:

1. The input starts with `PIECE [`.
2. `generation` specifies `syntax:instrument_roles`.
3. Instrument entries appear inside `ensemble:[instruments:[count:N, i1:..., i2:...]]`.
4. `count` is present and equals the number of indexed instruments.
5. `style`, `form`, `phrase_model` and `rhythm` are compatible.
6. Every instrument defines `id`, `name`, `family`, `role`, `midi`, `clef`, `octave` and `dynamic`.
7. `key` includes `tonic` and `mode`.
8. `meter` includes `num` and `den`.

If ELVEX reports an unsupported or missing feature, start from the closest working `.input` and change one attribute at a time.
