\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Percussion Ensemble in G"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Timpani"
    \set Staff.midiInstrument = "timpani"
    \tempo 4 = 104
    \key g \major
    \time 4/4

    \clef percussion
    s1*0\p
    g4 -. g4 g4 -. g4 |
    g4 -. g4 g4 -. g4 |
    d'4 -. d'4 d'4 -. d'4 |
    g4 -. g4 d'4 -. g4 |
    g1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Wood Block"
    \set Staff.midiInstrument = "woodblock"
    \tempo 4 = 104
    \key g \major
    \time 4/4

    \clef percussion
    s1*0\mp
    g'4 r4 d''4 g'4 |
    g'4 r4 d''4 g'4 |
    d''4 r4 g'4 d''4 |
    g'4 -. d''4 g'4 -. d''4 |
    g'1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

