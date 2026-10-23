\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Keyboard / Struck Strings Study"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Piano"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 96
    \key c \major
    \time 4/4

    \clef treble
    s1*0\mp
    <c' e' g'>8 <g' b' d''>8 <e' g' b'>4 <g' b' d''>2 |
    <f' gis' c''>2 <g' b' d''>2 |
    <g' b' d''>8 <b' d'' f''>8 <g' b' d''>4 <b' d'' f''>8 <g' b' d''>8 <g' b' d''>4 |
    <c' dis' g'>8 <dis' g' ais'>8 <g' b' d''>4 <dis' g' ais'>8 <g' b' d''>8 <c' dis' g'>4 |
    <c' dis' g'>8 <g' b' d''>8 <dis' g' ais'>4 <g' b' d''>8 <c' dis' g'>8 <g' b' d''>4 |
    <c' e' g'>4 <g' b' d''>4 <c' e' g'>4 <g' b' d''>4 |
    <f' gis' c''>4 <g' b' d''>4 <g' b' d''>4 <c' dis' g'>4 |
    <g' b' d''>4 <b' d'' f''>4 <g' b' d''>4 <g' b' d''>4 |
    <c' dis' g'>1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Piano LH"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 96
    \key c \major
    \time 4/4

    \clef bass
    s1*0\p
    c8 g8 e8 g8 c8 g8 e8 g8 |
    f2 g2 |
    g8 d'8 b8 d'8 g8 d'8 b8 d'8 |
    c4 c'4 g4 c4 |
    c4 c'4 g4 c4 |
    g8 d'8 g8 d'8 g8 d'8 b8 d'8 |
    c2 c2 |
    g4 d'4 b4 g4 |
    c1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

