\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Formal Long March for Percussion Ensemble"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Timpani"
    \set Staff.midiInstrument = "timpani"
    \tempo 4 = 112
    \key c \major
    \time 4/4

    \clef percussion
    s1*0\mf
    c4 -. c4 c4 -. c4 |
     c4 -. c4 c4 -. c4 |
     g4 -. g4 g4 -. g4 |
     c4 -. c4 g4 -. c4 |
     c4 -. c4 c4 -. c4 |
     g4 -. g4 g4 -. g4 |
     c4 -. c4 g4 -. c4 |
     c1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Snare Drum"
    \set Staff.midiInstrument = "snare drum"
    \tempo 4 = 112
    \key c \major
    \time 4/4

    \clef percussion
    s1*0\mp
    r1 |
     r1 |
     r1 |
     r1 |
     c'4 r4 g'4 c'4 |
     g'4 r4 c'4 g'4 |
     r1 |
     r1 |
     r1 |
     r1 |
     c'4 r4 g'4 c'4 |
     c'4 -. g'4 c'4 -. g'4 |
     c'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Bass Drum"
    \set Staff.midiInstrument = "bass drum"
    \tempo 4 = 112
    \key c \major
    \time 4/4

    \clef percussion
    s1*0\f
    c,4 r4 g,4 c,4 |
     r1 |
     r1 |
     r1 |
     r1 |
     c,4 r4 g,4 c,4 |
     g,4 r4 c,4 g,4 |
     r1 |
     r1 |
     r1 |
     r1 |
     c,4 -. g,4 c,4 -. g,4 |
     c,1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Cymbals"
    \set Staff.midiInstrument = "crash cymbal"
    \tempo 4 = 112
    \key c \major
    \time 4/4

    \clef percussion
    s1*0\mf
    r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     r1 |
     c'4 -. g'4 c'4 -. g'4 |
     r1 |
     r1 |
     r1 |
     r1 |
     c'4 -. g'4 c'4 -. g'4 |
     c'1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

