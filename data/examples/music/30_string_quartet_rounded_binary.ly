\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "String Quartet Study"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Violin I"
    \set Staff.midiInstrument = "violin"
    \tempo 4 = 96
    \key c \major
    \time 4/4

    \clef treble
    s1*0\mf
    c''4 d''4 e''4 g''4 |
    g''4 ( a''8 b''8 ) c'''2 |
    c'''4 b''4 a''4 g''4 |
    e''4 ( f''8 g''8 ) c''2 |
    c''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Violin II"
    \set Staff.midiInstrument = "violin"
    \tempo 4 = 96
    \key c \major
    \time 4/4

    \clef treble
    s1*0\mp
    e''4 g''4 f''4 e''4 |
    e''4 g''4 f''4 e''4 |
    g''4 f''4 e''4 d''4 |
    d''4 ( e''8 f''8 ) e''2 |
    e''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Viola"
    \set Staff.midiInstrument = "viola"
    \tempo 4 = 96
    \key c \major
    \time 4/4

    \clef alto
    s1*0\mp
    e'2 f'2 |
    e'2 f'2 |
    g'2 f'2 |
    e'2 d'2 |
    c'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Cello"
    \set Staff.midiInstrument = "cello"
    \tempo 4 = 96
    \key c \major
    \time 4/4

    \clef bass
    s1*0\p
    c4 c4 g4 g4 |
    c4 c4 g4 g4 |
    f4 f4 g4 g4 |
    g4 g4 c4 c4 |
    c1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

