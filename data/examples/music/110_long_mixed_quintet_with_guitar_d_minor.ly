\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Long Mixed Quintet with Guitar"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 96
    \key d \minor
    \time 4/4

    \clef treble
    s1*0\mf
    d''4 e''4 ges''4 a''4 |
    a''4 ( b''8 des'''8 ) d'''2 |
    d'''4 des'''4 b''4 a''4 |
    ges''4 ( g''8 a''8 ) d''2 |
    d''1 |
     d''4 e''4 ges''4 a''4 |
    a''4 ( b''8 des'''8 ) d'''2 |
    d'''4 des'''4 b''4 a''4 |
    ges''4 ( g''8 a''8 ) d''2 |
    d''1 |
     d''4 e''4 ges''4 a''4 |
    a''4 ( b''8 des'''8 ) d'''2 |
    d'''4 des'''4 b''4 a''4 |
    ges''4 ( g''8 a''8 ) d''2 |
    d''1 |
     d''4 e''4 ges''4 a''4 |
    a''4 ( b''8 des'''8 ) d'''2 |
    d'''4 des'''4 b''4 a''4 |
    ges''4 ( g''8 a''8 ) d''2 |
    d''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Violin"
    \set Staff.midiInstrument = "violin"
    \tempo 4 = 96
    \key d \minor
    \time 4/4

    \clef treble
    s1*0\mp
    r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     ges''4 a''4 g''4 ges''4 |
    ges''4 a''4 g''4 ges''4 |
    a''4 g''4 ges''4 e''4 |
    e''4 ( ges''8 g''8 ) ges''2 |
    ges''1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     ges''4 a''4 g''4 ges''4 |
    ges''4 a''4 g''4 ges''4 |
    a''4 g''4 ges''4 e''4 |
    e''4 ( ges''8 g''8 ) ges''2 |
    ges''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Cello"
    \set Staff.midiInstrument = "cello"
    \tempo 4 = 96
    \key d \minor
    \time 4/4

    \clef bass
    s1*0\p
    d4 d4 a4 a4 |
    d4 d4 a4 a4 |
    g4 g4 a4 a4 |
    a4 a4 d4 d4 |
    d1 |
     d4 d4 a4 a4 |
    d4 d4 a4 a4 |
    g4 g4 a4 a4 |
    a4 a4 d4 d4 |
    d1 |
     d4 d4 a4 a4 |
    d4 d4 a4 a4 |
    g4 g4 a4 a4 |
    a4 a4 d4 d4 |
    d1 |
     d4 d4 a4 a4 |
    d4 d4 a4 a4 |
    g4 g4 a4 a4 |
    a4 a4 d4 d4 |
    d1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Horn"
    \set Staff.midiInstrument = "french horn"
    \tempo 4 = 96
    \key d \minor
    \time 4/4

    \clef treble
    s1*0\mp
    d'4 d'4 a'4 a'4 |
    d'4 d'4 a'4 a'4 |
    g'4 g'4 a'4 a'4 |
    a'4 a'4 d'4 d'4 |
    d'1 |
     d'4 d'4 a'4 a'4 |
    d'4 d'4 a'4 a'4 |
    g'4 g'4 a'4 a'4 |
    a'4 a'4 d'4 d'4 |
    d'1 |
     d'4 d'4 a'4 a'4 |
    d'4 d'4 a'4 a'4 |
    g'4 g'4 a'4 a'4 |
    a'4 a'4 d'4 d'4 |
    d'1 |
     d'4 d'4 a'4 a'4 |
    d'4 d'4 a'4 a'4 |
    g'4 g'4 a'4 a'4 |
    a'4 a'4 d'4 d'4 |
    d'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitar"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 96
    \key d \minor
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    d'4 e'4 ges'4 a'4 |
    a'4 ( b'8 des''8 ) d''2 |
    d''4 des''4 b'4 a'4 |
    ges'4 ( g'8 a'8 ) d'2 |
    d'1 |
     d'4 e'4 ges'4 a'4 |
    a'4 ( b'8 des''8 ) d''2 |
    d''4 des''4 b'4 a'4 |
    ges'4 ( g'8 a'8 ) d'2 |
    d'1 |
     d'4 e'4 ges'4 a'4 |
    a'4 ( b'8 des''8 ) d''2 |
    d''4 des''4 b'4 a'4 |
    ges'4 ( g'8 a'8 ) d'2 |
    d'1 |
     d'4 e'4 ges'4 a'4 |
    a'4 ( b'8 des''8 ) d''2 |
    d''4 des''4 b'4 a'4 |
    ges'4 ( g'8 a'8 ) d'2 |
    d'1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

