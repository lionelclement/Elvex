\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Small English Pop Band"
  composer = "Elvex didactic pop"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Lead vocal"
    \set Staff.midiInstrument = "voice oohs"
    \clef treble
    \tempo 4 = 104
    \key g \major
    \time 4/4

    s1*0\mf
r1 |
g'8 a'8 b'4 a'8 g'4. |
b'8 c'8 b'4 a'4 g'4 |
d'8 e'8 d'4 b'8 d'4. |
e'8 d'8 e'4 g'4 fis'4 |
c'8 b'8 a'4 b'8 g'4. |
d'8 e'8 d'4 b'8 d'4. |
b'8 c'8 b'4 a'4 g'4 |
c'8 b'8 a'4 b'8 g'4. |
d'8 e'8 d'4 b'8 d'4. |
c'4 d'8 e'8 d'2 |
c'4 d'4 e'4 g'4 |
b'2 a'2 |
d'4 e'8 fis'8 e'2 |
c'4 b'4 a'4 d'4 |
a'2 g'2 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Piano RH"
    \set Staff.midiInstrument = "acoustic grand"
    \clef treble
    \tempo 4 = 104
    \key g \major
    \time 4/4

    s1*0\mp
r1 |
r1 |
b2 a2 |
r1 |
e4 d4 c4 b4 |
r1 |
d2 b2 |
r1 |
c4 d4 e4 d4 |
r1 |
g2 e2 |
d4 e4 fis4 g4 |
r1 |
b4 c4 d4 c4 |
d2 fis2 |
a2 g2 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Piano LH"
    \set Staff.midiInstrument = "acoustic grand"
    \clef bass
    \tempo 4 = 104
    \key g \major
    \time 4/4

    s1*0\mp
g,4 <g b d'>4 d,4 <g b d'>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
g,4 <g b d'>4 d,4 <g b d'>4 |
d,4 <d fis a>4 a,4 <d fis a>4 |
e,4 <e g b>4 b,4 <e g b>4 |
<c e g>4 <c e g>4 <c e g>4 <c e g>4 |
d,4 <d fis a>4 a,4 <d fis a>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
c,4 <c e g>4 g,4 <c e g>4 |
d,4 <d fis a>4 a,4 <d fis a>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
e,4 <e g b>4 b,4 <e g b>4 |
c,4 <c e g>4 g,4 <c e g>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
d,4 <d fis a>4 a,4 <d fis a>4 |
g,2 <g b d'>2 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Bass"
    \set Staff.midiInstrument = "electric bass (finger)"
    \clef bass
    \tempo 4 = 104
    \key g \major
    \time 4/4

    s1*0\mf
g,4 g,4 d,4 g,4 |
g,4 g,4 d,4 g,4 |
g,4 g,4 d,4 g,4 |
d,4 d,4 a,4 d,4 |
e,4 e,4 b,4 e,4 |
c,4 c,4 g,4 c,4 |
d,4 d,4 a,4 d,4 |
g,4 g,4 d,4 g,4 |
c,4 c,4 g,4 c,4 |
d,4 d,4 a,4 d,4 |
g,4 g,4 d,4 g,4 |
e,4 e,4 b,4 e,4 |
c,4 c,4 g,4 c,4 |
g,4 g,4 d,4 g,4 |
d,4 d,4 a,4 d,4 |
g,4 g,4 d,4 g,4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Drums"
    \set Staff.midiInstrument = "woodblock"
    \clef percussion
    \tempo 4 = 104
    \key g \major
    \time 4/4

    s1*0\mf
r1 |
g4 d4 g4 d4 |
g4 d4 g4 d4 |
g8 g8 d8 g8 g8 d8 g8 d8 |
g4 d4 g4 d4 |
g4 d4 g4 d4 |
g4 d4 g4 d4 |
g8 g8 d8 g8 g8 d8 g8 d8 |
g4 d4 g4 d4 |
g4 d4 g4 d4 |
g8 g8 d8 g8 g8 d8 g8 d8 |
g4 d4 g4 d4 |
g4 d4 g4 d4 |
g4 d4 g4 d4 |
g8 g8 d8 g8 g8 d8 g8 d8 |
g4 d4 g4 d4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Keyboard RH"
    \set Staff.midiInstrument = "electric piano 1"
    \clef treble
    \tempo 4 = 104
    \key g \major
    \time 4/4

    s1*0\p
r1 |
d'1 |
r1 |
d'2 b'2 |
r1 |
c'2 b'2 |
r1 |
a'2 g'2 |
r1 |
c'4 d'4 e'4 d'4 |
e'2 d'2 |
r1 |
b'4 c'4 d'4 c'4 |
r1 |
d'2 fis'2 |
a'2 g'2 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Keyboard LH"
    \set Staff.midiInstrument = "electric piano 1"
    \clef bass
    \tempo 4 = 104
    \key g \major
    \time 4/4

    s1*0\p
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
g,4 <g b d'>4 d,4 <g b d'>4 |
<d fis a>4 <d fis a>4 <d fis a>4 <d fis a>4 |
e,4 <e g b>4 b,4 <e g b>4 |
<c e g>4 <c e g>4 <c e g>4 <c e g>4 |
d,4 <d fis a>4 a,4 <d fis a>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
<c e g>4 <c e g>4 <c e g>4 <c e g>4 |
d,4 <d fis a>4 a,4 <d fis a>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
e,4 <e g b>4 b,4 <e g b>4 |
<c e g>4 <c e g>4 <c e g>4 <c e g>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
d,4 <d fis a>4 a,4 <d fis a>4 |
g,2 <g b d'>2 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

