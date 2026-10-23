\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Mixed Quintet with Guitar Chords"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 104
    \key g \major
    \time 4/4

    \clef treble
    s1*0\mf
    g''4 a''4 b''4 d'''4 |
    d'''4 ( e'''8 fis'''8 ) g'''2 |
    g'''4 fis'''4 e'''4 d'''4 |
    b''4 ( c'''8 d'''8 ) g''2 |
    g''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Violin"
    \set Staff.midiInstrument = "violin"
    \tempo 4 = 104
    \key g \major
    \time 4/4

    \clef treble
    s1*0\mp
    b''4 d'''4 c'''4 b''4 |
    b''4 d'''4 c'''4 b''4 |
    d'''4 c'''4 b''4 a''4 |
    a''4 ( b''8 c'''8 ) b''2 |
    b''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Cello"
    \set Staff.midiInstrument = "cello"
    \tempo 4 = 104
    \key g \major
    \time 4/4

    \clef bass
    s1*0\p
    g4 g4 d'4 d'4 |
    g4 g4 d'4 d'4 |
    c'4 c'4 d'4 d'4 |
    d'4 d'4 g4 g4 |
    g1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Horn"
    \set Staff.midiInstrument = "french horn"
    \tempo 4 = 104
    \key g \major
    \time 4/4

    \clef treble
    s1*0\mp
    g'2 d''2 |
    g'2 d''2 |
    c''2 d''2 |
    d''2 g'2 |
    g'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitar"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 104
    \key g \major
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    g'4 a'4 b'4 d''4 |
    d''4 ( e''8 fis''8 ) g''2 |
    g''4 fis''4 e''4 d''4 |
    b'4 ( c''8 d''8 ) g'2 |
    g'1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

