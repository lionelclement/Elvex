\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Flute and Guitar Study"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 96
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
    \set Staff.instrumentName = "Guitar"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 96
    \key g \major
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    <g' b' d''>2 <d'' fis'' a''>2 |
    g'8 ( d''8 g''4 ) b''2 |
    <g' ais' d''>4 <c'' dis'' g''>4 <d'' fis'' a''>4 <g' ais' d''>4 |
    d''4 g''8 b'8 g'2 |
    <g' ais' d''>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

