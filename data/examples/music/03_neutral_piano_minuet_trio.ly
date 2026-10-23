\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Minuet Trio for Piano"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Piano"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 112
    \key c \major
    \time 3/4

    \clef treble
    s1*0\mp
    <c' e' g'>2 <g' b' d''>4 |
    <g' b' d''>2 <c' e' g'>4 |
    <f' gis' c''>8 <d' f' gis'>8 <f' gis' c''>4 <g' b' d''>4 |
    <g' b' d''>4 <g' b' d''>2 |
    <f' a' c''>4 <c' e' g'>8 <f' a' c''>8 <c' e' g'>4 |
    <g' b' d''>2 <c' dis' g'>4 |
    <c' e' g'>2 <g' b' d''>4 |
    <g' b' d''>2 <c' e' g'>4 |
    <g' b' d''>4 <g' b' d''>2 |
    <c' dis' g'>2 <c' dis' g'>4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Piano LH"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 112
    \key c \major
    \time 3/4

    \clef bass
    s1*0\p
    c2 g4 |
    g2 c4 |
    f8 c'8 a4 g4 |
    g4 d'2 |
    f4 c'8 f8 c'4 |
    g2 c4 |
    c2 g4 |
    g2 c4 |
    g4 d'2 |
    c2. |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

