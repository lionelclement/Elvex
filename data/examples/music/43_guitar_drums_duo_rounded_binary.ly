\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Guitar and Drums Study"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Guitar"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 104
    \key c \major
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    <c' e' g'>2 <g' b' d''>2 |
    c'8 ( g'8 c''4 ) e''2 |
    <c' e' g'>4 <f' a' c''>4 <g' b' d''>4 <c' e' g'>4 |
    g'4 c''8 e'8 c'2 |
    <c' e' g'>1 |
\bar "|."

  }
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

