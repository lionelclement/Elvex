\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Chanson acoustique simple"
  composer = "Elvex didactic pop"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Voix"
    \set Staff.midiInstrument = "voice oohs"
    \clef treble
    \tempo 4 = 88
    \key a \minor
    \time 4/4

    s1*0\mf
r1 |
a''8 b''8 cis''4 b''8 a''4. |
cis''8 d''8 cis''4 b''4 a''4 |
e''8 fis''8 e''4 cis''8 e''4. |
fis''8 e''8 fis''4 a''4 gis''4 |
d''8 cis''8 b''4 cis''8 a''4. |
e''8 fis''8 e''4 cis''8 e''4. |
cis''8 d''8 cis''4 b''4 a''4 |
d''8 cis''8 b''4 cis''8 a''4. |
e''8 fis''8 e''4 cis''8 e''4. |
d''4 e''8 fis''8 e''2 |
d''4 e''4 fis''4 a''4 |
cis''2 b''2 |
e''4 fis''8 gis''8 fis''2 |
d''4 cis''4 b''4 e''4 |
b''2 a''2 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitare nylon"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \clef "treble_8"
    \tempo 4 = 88
    \key a \minor
    \time 4/4

    s1*0\mp
<a c' e'>4 <a c' e'>4 <a c' e'>4 <a c' e'>4 |
<a c' e'>4 <a c' e'>4 <a c' e'>4 <a c' e'>4 |
<a c' e'>4 <a c' e'>4 <a c' e'>4 <a c' e'>4 |
<e gis b>4 <e gis b>4 <e gis b>4 <e gis b>4 |
<f a c'>4 <f a c'>4 <f a c'>4 <f a c'>4 |
<d f a>4 <d f a>4 <d f a>4 <d f a>4 |
<e gis b>4 <e gis b>4 <e gis b>4 <e gis b>4 |
<a c' e'>4 <a c' e'>4 <a c' e'>4 <a c' e'>4 |
<d f a>4 <d f a>4 <d f a>4 <d f a>4 |
<e gis b>4 <e gis b>4 <e gis b>4 <e gis b>4 |
<a c' e'>4 <a c' e'>4 <a c' e'>4 <a c' e'>4 |
<f a c'>4 <f a c'>4 <f a c'>4 <f a c'>4 |
<d f a>4 <d f a>4 <d f a>4 <d f a>4 |
<a c' e'>4 <a c' e'>4 <a c' e'>4 <a c' e'>4 |
<e gis b>4 <e gis b>4 <e gis b>4 <e gis b>4 |
<a c' e'>4 <a c' e'>4 <a c' e'>4 <a c' e'>4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Contrebasse"
    \set Staff.midiInstrument = "contrabass"
    \clef bass
    \tempo 4 = 88
    \key a \minor
    \time 4/4

    s1*0\mp
a,4 a,4 e,4 a,4 |
a,4 a,4 e,4 a,4 |
a,4 a,4 e,4 a,4 |
e,4 e,4 b,4 e,4 |
f,4 f,4 c,4 f,4 |
d,4 d,4 a,4 d,4 |
e,4 e,4 b,4 e,4 |
a,4 a,4 e,4 a,4 |
d,4 d,4 a,4 d,4 |
e,4 e,4 b,4 e,4 |
a,4 a,4 e,4 a,4 |
f,4 f,4 c,4 f,4 |
d,4 d,4 a,4 d,4 |
a,4 a,4 e,4 a,4 |
e,4 e,4 b,4 e,4 |
a,4 a,4 e,4 a,4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Djembe"
    \set Staff.midiInstrument = "woodblock"
    \clef percussion
    \tempo 4 = 88
    \key a \minor
    \time 4/4

    s1*0\f
r8 a'8 r8 d'8 r8 a'8 r8 e'8 |
r8 a'8 r8 d'8 r8 a'8 r8 e'8 |
r8 d'8 r8 e'8 r8 d'8 r8 e'8 |
r8 a'8 r8 d'8 r8 a'8 r8 e'8 |
r8 a'8 r8 d'8 r8 a'8 r8 e'8 |
r8 d'8 r8 e'8 r8 d'8 r8 e'8 |
r8 a'8 r8 d'8 r8 a'8 r8 e'8 |
r8 d'8 r8 e'8 r8 d'8 r8 e'8 |
r8 d'8 r8 e'8 r8 d'8 r8 e'8 |
r8 a'8 r8 d'8 r8 a'8 r8 e'8 |
r8 d'8 r8 e'8 r8 d'8 r8 e'8 |
r8 a'8 d'8 r8 e'8 d'8 r8 e'8 |
r8 a'8 r8 d'8 r8 a'8 r8 e'8 |
r8 d'8 r8 e'8 r8 d'8 r8 e'8 |
r8 a'8 d'8 r8 e'8 d'8 r8 e'8 |
r8 a'8 r8 d'8 r8 a'8 r8 e'8 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

