\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Lombard Rhythm for Solo Flute"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 104
    \key c \major
    \time 4/4

    \clef treble
    s1*0\mf
    c''16 d''8. e''4 g''2 |
     c''16 d''8. e''4 g''2 |
     f''16 g''8. a''4 c'''2 |
     g''16 f''8. e''4 c''2 |
     c''16 d''8. e''4 g''2 |
     g''16 f''8. e''4 c''2 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

