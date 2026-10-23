\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Sarabande for Solo Flute in D Minor"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 64
    \key d \minor
    \time 3/4

    \clef treble
    s1*0\mf
    d''4 ges''8 g''8 a''4 |
     d''4 ges''8 g''8 a''4 |
     g''4 b''8 a''8 d'''4 |
     a''4 g''8 ges''8 d''4 |
     d''4 ges''8 g''8 a''4 |
     a''4 g''8 ges''8 d''4 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

