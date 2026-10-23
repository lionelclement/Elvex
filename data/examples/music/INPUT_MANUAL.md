# Manuel d’écriture des fichiers `.input`

## Lire les règles Elvex

Les fichiers `.rules` définissent comment Elvex transforme les traits musicaux d’un `.input` en fragments LilyPond. Cette section donne les conventions de lecture utiles pour comprendre les règles sans répéter ce rappel dans chaque fichier `.rules`.

Syntaxe générale d’une règle Elvex :

```txt
A → B C
{
  [trait:valeur, trait:$valeur_variable, $reste_traits];
    // Filtre les traits hérités de la règle courante.
    // Les variables comme $valeur_variable et $reste_traits sont liées
    // par unification et peuvent être réutilisées ensuite.

  [trait:$valeur_variable, $reste_traits] ⊂ ↑;
    // Extrait depuis les traits hérités ↑ les valeurs utiles à la règle.
    // Les variables sont liées par unification à partir de ↑.
    // Cette forme sert généralement à récupérer des valeurs ou un reste
    // de structure de traits pour les réutiliser ensuite.

  ↓1 = ↑ ∪ [...];
    // Définit les traits hérités transmis au premier enfant.

  ↓2 = ↑ ∪ [...];
    // Définit les traits hérités transmis au second enfant.

  ... ⇓1 ...;
    // Utilise les traits synthétisés remontés par le premier enfant.

  ... ⇓2 ...;
    // Utilise les traits synthétisés remontés par le second enfant.

  ⇑ = ...;
    // Définit les traits synthétisés remontés par cette règle.
}
```

Conventions principales :

| Symbole | Sens |
|---|---|
| `↑` | traits hérités reçus par la règle courante |
| `↓1`, `↓2`, etc. | traits hérités transmis au premier, second, etc. enfant |
| `⇓1`, `⇓2`, etc. | traits synthétisés remontés par le premier, second, etc. enfant |
| `⇑` | traits synthétisés remontés par la règle courante |

Les modules de haut niveau choisissent généralement une structure musicale ou une instrumentation. Les modules de bas niveau réalisent ensuite des mesures, notes, accords, silences ou fragments LilyPond.

## Note importante : `count` dans `ensemble.instruments`

Le bloc `ensemble.instruments` utilise des entrées indexées `i1`, `i2`, `i3`, etc. Le champ `count` est obligatoire et doit indiquer le nombre d’instruments déclarés.

Exemple pour un instrument :

```txt
ensemble:[
  instruments:[
    count:1,
    i1:[id:flute, name:"Flute", family:woodwind, role:flute1, midi:"flute", clef:treble, octave:5, dynamic:mf]
  ]
]
```

Exemple pour trois instruments :

```txt
ensemble:[
  instruments:[
    count:3,
    i1:[id:flute, name:"Flute", family:woodwind, role:flute_piano_lead, midi:"flute", clef:treble, octave:5, dynamic:mf],
    i2:[id:piano_rh, name:"Piano RH", family:keyboard, role:piano_acc_rh, midi:"acoustic grand", clef:treble, octave:4, dynamic:mp],
    i3:[id:piano_lh, name:"Piano LH", family:keyboard, role:piano_acc_lh, midi:"acoustic grand", clef:bass, octave:3, dynamic:p]
  ]
]
```

`count` doit toujours correspondre au dernier indice utilisé. Par exemple, si l’ensemble contient `i1`, `i2` et `i3`, il faut écrire `count:3`.

Ce champ peut sembler redondant, mais il rend le routage grammatical déterministe : la grammaire choisit directement la règle `count:1`, `count:2`, `count:3`, etc., sans essayer des règles trop courtes ou trop longues.


Ce manuel décrit le format courant des fichiers `.input` utilisés par Elvex pour produire un fichier LilyPond `.ly`.

Un fichier `.input` décrit une pièce musicale : son titre, son style, sa forme, son rythme, son instrumentation, sa tonalité et sa mesure.

La racine du fichier est toujours `PIECE`.

```txt
PIECE [
  generation:[syntax:instrument_roles, strict:false, fallback:true],

  title:"Titre de la pièce",
  composer:"Nom du compositeur",
  bpm:96,

  music:[...],
  ensemble:[...],
  key:[...],
  meter:[...]
]
```

## 1. Principe général

Les champs musicaux ne doivent pas être choisis comme une liste plate d’options indépendantes.

Les champs suivants vont généralement ensemble :

```txt
style
form
phrase_model
rhythm.topic
rhythm.dance
rhythm.density
rhythm.articulation
```

Par exemple, une gigue classique combine généralement :

```txt
style:classical_19c
form:long_gigue
phrase_model:periodic
rhythm:[topic:gallop, dance:gigue, density:active, articulation:detached]
```

Une chanson couplet/refrain combine plutôt :

```txt
style:chanson_francaise
form:chanson_francaise_couplet_refrain
phrase_model:verse_chorus
rhythm:[topic:chanson_syllabic, dance:none, density:medium, articulation:legato]
```

Le plus sûr est donc de partir d’un des profils recommandés ci-dessous, puis de modifier seulement les paramètres nécessaires.

## 2. Bloc `generation`

Le bloc `generation` indique comment l’input est organisé.

```txt
generation:[syntax:instrument_roles, strict:false, fallback:true]
```

### Champs

| Champ | Valeurs | Usage |
|---|---|---|
| `syntax` | `instrument_roles` | Les instruments sont décrits par identifiant, famille et rôle musical. C’est la syntaxe publique de cette version. |
| `strict` | `true`, `false` | Avec `false`, la grammaire peut compléter certains champs manquants par des valeurs par défaut. |
| `fallback` | `true`, `false` | Avec `true`, la grammaire peut utiliser une solution générique quand un cas spécialisé n’existe pas. |

Usage recommandé :

```txt
generation:[syntax:instrument_roles, strict:false, fallback:true]
```

## 3. Métadonnées

```txt
title:"Titre",
composer:"Compositeur",
bpm:96
```

| Champ | Exemple | Remarque |
|---|---|---|
| `title` | `"Étude en sol"` | Titre imprimé dans le fichier LilyPond. |
| `composer` | `"Elvex"` | Compositeur imprimé dans l’en-tête. |
| `bpm` | `96` | Tempo MIDI et indication générale. |

Le tempo dépend du style :

| Usage | `bpm` typique |
|---|---:|
| étude lente, sicilienne, ballade | `60`–`84` |
| classique modéré | `88`–`112` |
| marche, pop, chanson | `104`–`128` |
| gigue, rock actif | `120`–`144` |

## 4. Bloc `music`

Le bloc `music` décrit le matériau musical.

```txt
music:[
  style:classical_19c,
  form:rounded_binary,
  phrase_model:periodic,
  rhythm:[...]
]
```

### 4.1 `style`

| Valeur | Usage |
|---|---|
| `classical_19c` | Écriture classique, formes périodiques, danses, études, pièces instrumentales. |
| `pop_60s_80s` | Chanson pop avec couplet/refrain et accompagnement. |
| `chanson_francaise` | Chanson française, voix ou ligne mélodique + accompagnement. |
| `rock` | Groupe rock, backbeat, guitare, basse, batterie. |

### 4.2 `form`

Les formes compatibles dépendent fortement du style.

#### Formes classiques

| Forme | Usage recommandé |
|---|---|
| `scales` | Études de gammes. |
| `rounded_binary` | Petite forme binaire avec retour. |
| `ternary` | Forme ABA simple. |
| `minuet_trio` | Menuet/trio classique. |
| `theme_and_variations` | Thème et variations. |
| `long_rounded_binary` | Forme binaire plus longue. |
| `long_ternary` | Forme ABA plus longue. |
| `long_theme_and_variations` | Thème et variations développé. |
| `long_siciliana` | Sicilienne longue. |
| `long_gigue` | Gigue longue. |
| `long_march` | Marche longue. |
| `formal_long_rounded_binary` | Version plus formelle de `long_rounded_binary`. |
| `formal_long_ternary` | Version plus formelle de `long_ternary`. |
| `formal_long_theme_and_variations` | Version plus formelle du thème et variations. |
| `formal_long_siciliana` | Sicilienne longue formelle. |
| `formal_long_gigue` | Gigue longue formelle. |
| `formal_long_march` | Marche longue formelle. |

#### Formes pop

| Forme | Usage recommandé |
|---|---|
| `pop_song_verse_chorus` | Chanson pop avec couplet/refrain. |

#### Formes chanson française

| Forme | Usage recommandé |
|---|---|
| `chanson_francaise_couplet_refrain` | Forme standard couplet/refrain. |
| `chanson_francaise_couplet_refrain_lyrique` | Version plus chantée et lyrique. |
| `chanson_francaise_couplet_refrain_parle` | Version plus parlée/récitative. |
| `chanson_francaise_couplet_refrain_nostalgique` | Version nostalgique. |
| `chanson_francaise_couplet_refrain_refrain_hook` | Refrain plus accrocheur. |
| `chanson_francaise_couplet_refrain_recit_bas` | Récit dans un registre plus bas. |
| `chanson_francaise_couplet_refrain_grande_arche` | Grande arche mélodique. |
| `chanson_francaise_couplet_refrain_hook_syncopated` | Hook syncopé. |
| `chanson_francaise_couplet_refrain_descendante` | Ligne descendante. |

#### Formes rock

| Forme | Usage recommandé |
|---|---|
| `rock_song_verse_chorus` | Groupe rock couplet/refrain. |
| `rock_song_sax_choir` | Groupe rock avec saxophone et chœur. |
| `rock_direct_band` | Écriture rock directe pour groupe. |
| `rock_direct_sax_choir` | Écriture rock directe avec saxophone et chœur. |

### 4.3 `phrase_model`

| Valeur | Styles habituels | Usage |
|---|---|---|
| `periodic` | `classical_19c` | Phrases régulières, antécédent/conséquent, périodes classiques. |
| `verse_chorus` | `pop_60s_80s`, `chanson_francaise`, `rock` | Organisation couplet/refrain. |

### 4.4 Bloc `rhythm`

```txt
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

#### `topic`

| Valeur | Usage |
|---|---|
| `neutral` | Rythme neutre, très sûr pour les formes classiques générales. |
| `siciliana` | Sicilienne, balancement doux. |
| `gallop` | Gigue ou mouvement ternaire actif. |
| `march` | Marche. |
| `dotted` | Rythmes pointés. |
| `lombard` | Rythme lombard. |
| `syncopation` | Syncopes. |
| `sarabande` | Sarabande. |
| `pop_backbeat` | Pop avec backbeat. |
| `pop_ballad` | Ballade pop. |
| `chanson_syllabic` | Chanson syllabique. |
| `chanson_acoustic` | Chanson accompagnée de manière acoustique. |
| `chanson_lyrique` | Chanson lyrique. |
| `chanson_parlee` | Chanson parlée/récitative. |
| `chanson_nostalgique` | Chanson nostalgique. |
| `chanson_hook` | Chanson avec hook marqué. |
| `rock_backbeat` | Rock avec backbeat. |
| `classic_rock_backbeat` | Rock classique. |

Certains topics internes sont destinés à des parties instrumentales précises, par exemple `piano_acc_siciliana_rh`, `piano_acc_siciliana_lh`, `gallop_support`, `march_support`. Pour un utilisateur, il vaut mieux choisir les topics généraux du tableau ci-dessus.

#### `dance`

| Valeur | Usage |
|---|---|
| `none` | Pas de danse explicite. |
| `gigue` | À utiliser avec `topic:gallop` et une forme de gigue. |
| `sarabande` | À utiliser avec `topic:dotted` ou `topic:sarabande`. |
| `minuet` | À utiliser avec `form:minuet_trio`. |

#### `density`

| Valeur | Usage |
|---|---|
| `sparse` | Très peu de notes, écriture aérée. |
| `light` | Léger. |
| `low_medium` | Entre léger et moyen, utile pour chanson ou accompagnement discret. |
| `medium` | Valeur standard. |
| `active` | Écriture plus animée. |

#### `articulation`

| Valeur | Usage |
|---|---|
| `neutral` | Articulation non spécialisée. |
| `slurred` | Lié, chantant. |
| `detached` | Détaché, utile pour gigue ou danse active. |
| `marked` | Articulé/marqué, utile pour marche ou sarabande. |
| `legato` | Chantant, pop, chanson. |
| `accented` | Accents, rock, marche forte. |

#### Autres champs rythmiques

| Champ | Valeurs usuelles | Usage |
|---|---|---|
| `anacrusis` | `true`, `false` | Départ en levée. |
| `hemiola_at_cadence` | `true`, `false` | Hémiole proche de la cadence. |
| `ostinato` | `none`, `guitar_strum`, `guitar_riff` | Motif répété ou accompagnement. |

## 5. Profils recommandés

Les profils ci-dessous ne sont pas des champs spéciaux : ce sont des combinaisons complètes et cohérentes à copier dans le bloc `music`.

### Classique neutre

```txt
music:[
  style:classical_19c,
  form:rounded_binary,
  phrase_model:periodic,
  rhythm:[topic:neutral, dance:none, density:medium, anacrusis:false, hemiola_at_cadence:false, ostinato:none, articulation:neutral]
]
```

### Étude de gammes

```txt
music:[
  style:classical_19c,
  form:scales,
  phrase_model:periodic,
  rhythm:[topic:neutral, dance:none, density:medium, anacrusis:false, hemiola_at_cadence:false, ostinato:none, articulation:neutral]
]
```

### Sicilienne classique

```txt
music:[
  style:classical_19c,
  form:long_siciliana,
  phrase_model:periodic,
  rhythm:[topic:siciliana, dance:none, density:medium, anacrusis:false, hemiola_at_cadence:false, ostinato:none, articulation:slurred]
]
```

### Gigue classique

```txt
music:[
  style:classical_19c,
  form:long_gigue,
  phrase_model:periodic,
  rhythm:[topic:gallop, dance:gigue, density:active, anacrusis:false, hemiola_at_cadence:false, ostinato:none, articulation:detached]
]
```

### Marche classique

```txt
music:[
  style:classical_19c,
  form:long_march,
  phrase_model:periodic,
  rhythm:[topic:march, dance:none, density:active, anacrusis:false, hemiola_at_cadence:false, ostinato:none, articulation:marked]
]
```

### Pop couplet/refrain

```txt
music:[
  style:pop_60s_80s,
  form:pop_song_verse_chorus,
  phrase_model:verse_chorus,
  rhythm:[topic:pop_backbeat, dance:none, density:medium, anacrusis:false, hemiola_at_cadence:false, ostinato:guitar_strum, articulation:legato]
]
```

### Ballade pop

```txt
music:[
  style:pop_60s_80s,
  form:pop_song_verse_chorus,
  phrase_model:verse_chorus,
  rhythm:[topic:pop_ballad, dance:none, density:low_medium, anacrusis:false, hemiola_at_cadence:false, ostinato:guitar_strum, articulation:legato]
]
```

### Chanson française lyrique

```txt
music:[
  style:chanson_francaise,
  form:chanson_francaise_couplet_refrain_lyrique,
  phrase_model:verse_chorus,
  rhythm:[topic:chanson_lyrique, dance:none, density:medium, anacrusis:false, hemiola_at_cadence:false, ostinato:none, articulation:legato]
]
```

### Chanson française parlée

```txt
music:[
  style:chanson_francaise,
  form:chanson_francaise_couplet_refrain_parle,
  phrase_model:verse_chorus,
  rhythm:[topic:chanson_parlee, dance:none, density:low_medium, anacrusis:false, hemiola_at_cadence:false, ostinato:none, articulation:legato]
]
```

### Rock classique

```txt
music:[
  style:rock,
  form:rock_song_verse_chorus,
  phrase_model:verse_chorus,
  rhythm:[topic:rock_backbeat, dance:none, density:active, anacrusis:false, hemiola_at_cadence:false, ostinato:guitar_riff, articulation:accented]
]
```

### Rock avec saxophone et chœur

```txt
music:[
  style:rock,
  form:rock_song_sax_choir,
  phrase_model:verse_chorus,
  rhythm:[topic:classic_rock_backbeat, dance:none, density:active, anacrusis:false, hemiola_at_cadence:false, ostinato:guitar_riff, articulation:accented]
]
```

## 6. Bloc `ensemble`

Le bloc `ensemble` décrit les instruments par ordre, avec des entrées `i1`, `i2`, `i3`, etc. Le champ `count` est obligatoire et indique combien d’instruments sont déclarés.

```txt
ensemble:[
  instruments:[
    count:2,
    i1:[id:flute, name:"Flute", family:woodwind, role:lead, midi:"flute", clef:treble, octave:5, dynamic:mf],
    i2:[id:piano_rh, name:"Piano RH", family:keyboard, role:harmonic_support, midi:"acoustic grand", clef:treble, octave:4, dynamic:mp]
  ]
]
```

`count` doit correspondre au nombre d’entrées `iN`. Si l’ensemble contient `i1` et `i2`, on écrit `count:2`; s’il contient `i1`, `i2`, `i3`, `i4`, on écrit `count:4`.

### Champs d’un instrument

| Champ | Exemple | Usage |
|---|---|---|
| `id` | `flute`, `piano_rh` | Identifiant interne lisible. |
| `name` | `"Flute"` | Nom affiché dans la partition. |
| `family` | `woodwind` | Famille instrumentale. |
| `role` | `lead` | Fonction musicale. |
| `midi` | `"flute"` | Instrument MIDI LilyPond. |
| `clef` | `treble` | Clé. |
| `octave` | `5` | Registre principal. |
| `dynamic` | `mf` | Nuance de départ. |

### `family`

| Valeur | Usage |
|---|---|
| `woodwind` | Flûte, clarinette, hautbois, saxophone. |
| `brass` | Cuivres. |
| `bowed_strings` | Violon, alto, violoncelle, contrebasse. |
| `plucked_strings` | Guitare, harpe, cordes pincées. |
| `keyboard` | Piano, clavier. |
| `percussion` | Percussions, batterie. |
| `voice` | Voix ou guide vocal. |
| `electric_bass` | Basse électrique. |
| `electric_strings` | Cordes électriques. |
| `free_reed` | Accordéon, harmonica, etc. |
| `synth`, `synth_bass`, `synth_brass`, `synth_strings` | Parties de synthétiseur. |

### `role`

Les rôles les plus généraux sont :

| Rôle | Usage |
|---|---|
| `lead` | Mélodie principale. |
| `countermelody` | Contrechant. |
| `inner_voice` | Voix intérieure. |
| `bass` | Basse. |
| `harmonic_support` | Accompagnement harmonique. |
| `rhythmic_pedal` | Pédale ou motif rythmique. |
| `accent`, `bass_accent`, `cadence_accent` | Accents ponctuels. |
| `guitar` | Partie de guitare générique. |
| `drum_kit` | Batterie/percussion. |

Rôles spécialisés utiles :

| Rôle | Usage |
|---|---|
| `flute1`, `flute2` | Duo ou écriture pour flûtes. |
| `flute_piano_lead` | Flûte soliste avec piano. |
| `piano_rh`, `piano_lh` | Piano solo, main droite/main gauche. |
| `piano_acc_rh`, `piano_acc_lh` | Piano accompagnateur, main droite/main gauche. |
| `chanson_voice`, `chanson_guitar` | Chanson française voix/guitare. |
| `rock_voice`, `rock_guitar`, `rock_bass`, `rock_drums` | Groupe rock. |
| `rock_sax`, `rock_choir` | Rock avec saxophone et chœur. |

### `clef`

| Valeur | Usage |
|---|---|
| `treble` | Clé de sol. |
| `bass` | Clé de fa. |
| `alto` | Clé d’ut alto. |
| `treble_8` | Clé de sol octaviée, utile pour guitare. |
| `percussion` | Percussion. |

### `dynamic`

| Valeur | Usage |
|---|---|
| `p` | doux |
| `mp` | mezzo-piano |
| `mf` | mezzo-forte |
| `f` | fort |
| `ff` | très fort |

## 7. Tonalité : bloc `key`

```txt
key:[tonic:c, mode:major]
```

### `tonic`

Valeurs utilisées couramment :

```txt
c, d, e, f, g, a, b, bes, ees
```

Exemples :

| Valeur | Signification |
|---|---|
| `c` | do |
| `d` | ré |
| `e` | mi |
| `f` | fa |
| `g` | sol |
| `a` | la |
| `b` | si |
| `bes` | si bémol |
| `ees` | mi bémol |

### `mode`

| Valeur | Usage |
|---|---|
| `major` | mode majeur |
| `minor` | mode mineur |

## 8. Mesure : bloc `meter`

```txt
meter:[num:4, den:4]
```

| Mesure | Usage |
|---|---|
| `meter:[num:4, den:4]` | Mesure générale, pop, rock, marche. |
| `meter:[num:3, den:4]` | Menuet, sarabande, formes ternaires. |
| `meter:[num:6, den:8]` | Sicilienne, gigue, balancement composé. |

## 9. Matrice de compatibilité rapide

| Style | Formes recommandées | `phrase_model` | Topics recommandés |
|---|---|---|---|
| `classical_19c` | `scales`, `rounded_binary`, `ternary`, `minuet_trio`, `theme_and_variations`, `long_*`, `formal_long_*` | `periodic` | `neutral`, `siciliana`, `gallop`, `march`, `dotted`, `lombard`, `syncopation`, `sarabande` |
| `pop_60s_80s` | `pop_song_verse_chorus` | `verse_chorus` | `pop_backbeat`, `pop_ballad` |
| `chanson_francaise` | `chanson_francaise_couplet_refrain*` | `verse_chorus` | `chanson_syllabic`, `chanson_acoustic`, `chanson_lyrique`, `chanson_parlee`, `chanson_nostalgique`, `chanson_hook` |
| `rock` | `rock_song_verse_chorus`, `rock_song_sax_choir`, `rock_direct_band`, `rock_direct_sax_choir` | `verse_chorus` | `rock_backbeat`, `classic_rock_backbeat` |

## 10. Exemples complets

Des exemples prêts à lancer sont fournis dans les fichiers :

```txt
sample_*.input
```

Ils couvrent plusieurs combinaisons sûres : classique, sicilienne, gigue, marche, pop, chanson française et rock.

## 11. Checklist avant génération

Avant de lancer Elvex, vérifier :

1. Le fichier commence par `PIECE [`.
2. Le bloc `generation` contient `syntax:instrument_roles`.
3. Les instruments sont dans `ensemble:[instruments:[count:N, i1:..., i2:...]]`.
4. Le champ `count` est présent et correspond au nombre d’instruments déclarés.
5. Les champs `style`, `form`, `phrase_model` et `rhythm` forment une combinaison cohérente.
6. Chaque instrument possède au moins `id`, `name`, `family`, `role`, `midi`, `clef`, `octave`, `dynamic`.
7. `key` contient `tonic` et `mode`.
8. `meter` contient `num` et `den`.
