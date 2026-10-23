\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Percussion Ensemble Study"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Timpani"
    \set Staff.midiInstrument = "timpani"
    \tempo 4 = 96
    \key c \major
    \time 4/4

    \clef percussion
    s1*0\p
    c4 -. c4 c4 -. c4 |
    c4 -. c4 c4 -. c4 |
    g4 -. g4 g4 -. g4 |
    c4 -. c4 g4 -. c4 |
    c1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Wood Block"
    \set Staff.midiInstrument = "woodblock"
    \tempo 4 = 96
    \key c \major
    \time 4/4

    \clef percussion
    s1*0\mp
    c'4 r4 g'4 c'4 |
    c'4 r4 g'4 c'4 |
    g'4 r4 c'4 g'4 |
    c'4 -. g'4 c'4 -. g'4 |
    c'1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

