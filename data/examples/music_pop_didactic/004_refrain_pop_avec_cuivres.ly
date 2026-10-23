\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Refrain pop avec cuivres"
  composer = "Elvex didactic pop"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Voice"
    \set Staff.midiInstrument = "voice oohs"
    \clef treble
    \tempo 4 = 108
    \key d \major
    \time 4/4

    s1*0\mf
r1 |
d'8 e'8 fis'4 e'8 d'4. |
fis'8 g'8 fis'4 e'4 d'4 |
a'8 b'8 a'4 fis'8 a'4. |
b'8 a'8 b'4 d'4 cis'4 |
g'8 fis'8 e'4 fis'8 d'4. |
a'8 b'8 a'4 fis'8 a'4. |
fis'8 g'8 fis'4 e'4 d'4 |
g'8 fis'8 e'4 fis'8 d'4. |
a'8 b'8 a'4 fis'8 a'4. |
g'4 a'8 b'8 a'2 |
g'4 a'4 b'4 d'4 |
fis'2 e'2 |
a'4 b'8 cis'8 b'2 |
g'4 fis'4 e'4 a'4 |
e'2 d'2 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Nylon guitar"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \clef "treble_8"
    \tempo 4 = 108
    \key d \major
    \time 4/4

    s1*0\mp
<d fis a>4 <d fis a>4 <d fis a>4 <d fis a>4 |
<d fis a>4 <d fis a>4 <d fis a>4 <d fis a>4 |
<d fis a>4 <d fis a>4 <d fis a>4 <d fis a>4 |
<a cis' e'>4 <a cis' e'>4 <a cis' e'>4 <a cis' e'>4 |
<b d' fis'>4 <b d' fis'>4 <b d' fis'>4 <b d' fis'>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
<a cis' e'>4 <a cis' e'>4 <a cis' e'>4 <a cis' e'>4 |
<d fis a>4 <d fis a>4 <d fis a>4 <d fis a>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
<a cis' e'>4 <a cis' e'>4 <a cis' e'>4 <a cis' e'>4 |
<d fis a>4 <d fis a>4 <d fis a>4 <d fis a>4 |
<b d' fis'>4 <b d' fis'>4 <b d' fis'>4 <b d' fis'>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
<d fis a>4 <d fis a>4 <d fis a>4 <d fis a>4 |
<a cis' e'>4 <a cis' e'>4 <a cis' e'>4 <a cis' e'>4 |
<d fis a>4 <d fis a>4 <d fis a>4 <d fis a>4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Bass"
    \set Staff.midiInstrument = "electric bass (finger)"
    \clef bass
    \tempo 4 = 108
    \key d \major
    \time 4/4

    s1*0\mf
d,4 d,4 a,4 d,4 |
d,4 d,4 a,4 d,4 |
d,4 d,4 a,4 d,4 |
a,4 a,4 e,4 a,4 |
b,4 b,4 fis,4 b,4 |
g,4 g,4 d,4 g,4 |
a,4 a,4 e,4 a,4 |
d,4 d,4 a,4 d,4 |
g,4 g,4 d,4 g,4 |
a,4 a,4 e,4 a,4 |
d,4 d,4 a,4 d,4 |
b,4 b,4 fis,4 b,4 |
g,4 g,4 d,4 g,4 |
d,4 d,4 a,4 d,4 |
a,4 a,4 e,4 a,4 |
d,4 d,4 a,4 d,4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Drums"
    \set Staff.midiInstrument = "woodblock"
    \clef percussion
    \tempo 4 = 108
    \key d \major
    \time 4/4

    s1*0\mf
r1 |
d4 a4 d4 a4 |
d4 a4 d4 a4 |
d8 d8 a8 d8 d8 a8 d8 a8 |
d4 a4 d4 a4 |
d4 a4 d4 a4 |
d4 a4 d4 a4 |
d8 d8 a8 d8 d8 a8 d8 a8 |
d4 a4 d4 a4 |
d4 a4 d4 a4 |
d8 d8 a8 d8 d8 a8 d8 a8 |
d4 a4 d4 a4 |
d4 a4 d4 a4 |
d4 a4 d4 a4 |
d8 d8 a8 d8 d8 a8 d8 a8 |
d4 a4 d4 a4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Trompette"
    \set Staff.midiInstrument = "trumpet"
    \clef treble
    \tempo 4 = 108
    \key d \major
    \time 4/4

    s1*0\mf
r1 |
r1 |
r1 |
r1 |
r1 |
g'2 b'2 |
r1 |
a'2 cis'2 |
r1 |
r1 |
g'2 d'2 |
a'2 cis'2 |
r1 |
b'2 a'2 |
a'2 cis'2 |
d'2 a'2 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Trombone"
    \set Staff.midiInstrument = "trombone"
    \clef bass
    \tempo 4 = 108
    \key d \major
    \time 4/4

    s1*0\mf
r1 |
r1 |
r1 |
r1 |
r1 |
g2 b2 |
r1 |
a2 cis2 |
r1 |
r1 |
g2 d2 |
a2 cis2 |
r1 |
b2 a2 |
a2 cis2 |
d2 a2 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Cor"
    \set Staff.midiInstrument = "french horn"
    \clef treble
    \tempo 4 = 108
    \key d \major
    \time 4/4

    s1*0\mp
<d fis a>1 |
<d fis a>1 |
<d fis a>1 |
<a cis' e'>1 |
<b d' fis'>1 |
<g b d'>1 |
<a cis' e'>1 |
<d fis a>1 |
<g b d'>1 |
<a cis' e'>1 |
<d fis a>1 |
<b d' fis'>1 |
<g b d'>1 |
<d fis a>1 |
<a cis' e'>1 |
<d fis a>1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Tuba"
    \set Staff.midiInstrument = "tuba"
    \clef bass
    \tempo 4 = 108
    \key d \major
    \time 4/4

    s1*0\mp
d,4 d,4 a,4 d,4 |
d,4 d,4 a,4 d,4 |
d,4 d,4 a,4 d,4 |
a,4 a,4 e,4 a,4 |
b,4 b,4 fis,4 b,4 |
g,4 g,4 d,4 g,4 |
a,4 a,4 e,4 a,4 |
d,4 d,4 a,4 d,4 |
g,4 g,4 d,4 g,4 |
a,4 a,4 e,4 a,4 |
d,4 d,4 a,4 d,4 |
b,4 b,4 fis,4 b,4 |
g,4 g,4 d,4 g,4 |
d,4 d,4 a,4 d,4 |
a,4 a,4 e,4 a,4 |
d,4 d,4 a,4 d,4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Clavier RH"
    \set Staff.midiInstrument = "electric piano 1"
    \clef treble
    \tempo 4 = 108
    \key d \major
    \time 4/4

    s1*0\p
r1 |
a'1 |
r1 |
a'2 fis'2 |
r1 |
g'2 fis'2 |
r1 |
e'2 d'2 |
r1 |
g'4 a'4 b'4 a'4 |
b'2 a'2 |
r1 |
fis'4 g'4 a'4 g'4 |
r1 |
a'2 cis'2 |
e'2 d'2 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Clavier LH"
    \set Staff.midiInstrument = "electric piano 1"
    \clef bass
    \tempo 4 = 108
    \key d \major
    \time 4/4

    s1*0\p
<d fis a>4 <d fis a>4 <d fis a>4 <d fis a>4 |
<d fis a>4 <d fis a>4 <d fis a>4 <d fis a>4 |
d,4 <d fis a>4 a,4 <d fis a>4 |
<a cis' e'>4 <a cis' e'>4 <a cis' e'>4 <a cis' e'>4 |
b,4 <b d' fis'>4 fis,4 <b d' fis'>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
a,4 <a cis' e'>4 e,4 <a cis' e'>4 |
<d fis a>4 <d fis a>4 <d fis a>4 <d fis a>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
a,4 <a cis' e'>4 e,4 <a cis' e'>4 |
<d fis a>4 <d fis a>4 <d fis a>4 <d fis a>4 |
b,4 <b d' fis'>4 fis,4 <b d' fis'>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
<d fis a>4 <d fis a>4 <d fis a>4 <d fis a>4 |
a,4 <a cis' e'>4 e,4 <a cis' e'>4 |
d,2 <d fis a>2 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

