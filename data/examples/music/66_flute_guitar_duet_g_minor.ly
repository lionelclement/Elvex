\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Flute and Guitar in G Minor"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 84
    \key g \minor
    \time 4/4

    \clef treble
    s1*0\mf
    g''4 a''4 b''4 d'''4 |
    d'''4 ( e'''8 ges'''8 ) g'''2 |
    g'''4 ges'''4 e'''4 d'''4 |
    b''4 ( c'''8 d'''8 ) g''2 |
    g''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitar"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 84
    \key g \minor
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    <g' b' d''>2 <d'' ges'' a''>2 |
    g'8 ( d''8 g''4 ) b''2 |
    <g' bes' d''>4 <c'' ees'' g''>4 <d'' ges'' a''>4 <g' bes' d''>4 |
    d''4 g''8 b'8 g'2 |
    <g' b' d''>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

