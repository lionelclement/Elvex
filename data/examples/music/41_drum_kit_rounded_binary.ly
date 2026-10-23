\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Drum Kit Study"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Drum Kit"
    \set Staff.midiInstrument = "standard kit"
    \tempo 4 = 104
    \key c \major
    \time 4/4

    \clef percussion
    s1*0\mp
    c4 -. g4 c4 -. g4 |
    c4 -. g4 c4 -. g4 |
    g4 r4 g4 c4 |
    c4 -. g4 g4 -. c4 |
    c1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

