\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Woodwind Trio in G Major"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Oboe"
    \set Staff.midiInstrument = "oboe"
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
    \set Staff.instrumentName = "Clarinet"
    \set Staff.midiInstrument = "clarinet"
    \tempo 4 = 104
    \key g \major
    \time 4/4

    \clef treble
    s1*0\mp
    b'4 d''4 c''4 b'4 |
    b'4 d''4 c''4 b'4 |
    d''4 c''4 b'4 a'4 |
    a'4 ( b'8 c''8 ) b'2 |
    b'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Bassoon"
    \set Staff.midiInstrument = "bassoon"
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
>>
  \layout { }
  \midi { }
}

