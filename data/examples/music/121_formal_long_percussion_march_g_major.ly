\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Formal Long March for Percussion Ensemble in G"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Timpani"
    \set Staff.midiInstrument = "timpani"
    \tempo 4 = 120
    \key g \major
    \time 4/4

    \clef percussion
    s1*0\mf
    g4 -. g4 g4 -. g4 |
     g4 -. g4 g4 -. g4 |
     d'4 -. d'4 d'4 -. d'4 |
     g4 -. g4 d'4 -. g4 |
     g4 -. g4 g4 -. g4 |
     d'4 -. d'4 d'4 -. d'4 |
     g4 -. g4 d'4 -. g4 |
     g1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Snare Drum"
    \set Staff.midiInstrument = "snare drum"
    \tempo 4 = 120
    \key g \major
    \time 4/4

    \clef percussion
    s1*0\mp
    r1 |
     r1 |
     r1 |
     r1 |
     g'4 r4 d''4 g'4 |
     d''4 r4 g'4 d''4 |
     r1 |
     r1 |
     r1 |
     r1 |
     g'4 r4 d''4 g'4 |
     g'4 -. d''4 g'4 -. d''4 |
     g'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Bass Drum"
    \set Staff.midiInstrument = "bass drum"
    \tempo 4 = 120
    \key g \major
    \time 4/4

    \clef percussion
    s1*0\f
    g,4 r4 d4 g,4 |
     r1 |
     r1 |
     r1 |
     r1 |
     g,4 r4 d4 g,4 |
     d4 r4 g,4 d4 |
     r1 |
     r1 |
     r1 |
     r1 |
     g,4 -. d4 g,4 -. d4 |
     g,1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Cymbals"
    \set Staff.midiInstrument = "crash cymbal"
    \tempo 4 = 120
    \key g \major
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
     g'4 -. d''4 g'4 -. d''4 |
     r1 |
     r1 |
     r1 |
     r1 |
     g'4 -. d''4 g'4 -. d''4 |
     g'1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

