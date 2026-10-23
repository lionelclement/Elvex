\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Syncopation for Solo Flute"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 96
    \key a \minor
    \time 4/4

    \clef treble
    s1*0\mf
    a''4 ~ a''4 cis'''4 e'''4 |
     a''4 ~ a''4 cis'''4 e'''4 |
     d'''4 ~ d'''4 fis'''4 a'''4 |
     e'''4 ~ e'''4 cis'''4 a''4 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

