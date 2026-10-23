\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Rounded Binary for Flute and Piano"
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
    c''8 d''8 e''4 g''8 f''8 e''4 |
    e''8 f''8 e''4 d''8 e''8 g''4 |
    d''4 e''4 fis''4 g''4 |
    g''4 e''4 d''4 c''4 |
    g''8 f''8 e''4 d''8 e''8 c''4 |
    g''4 e''4 d''4 c''4 |
    f''4 g''4 b''4 g''4 |
    g''8 e''8 d''4 c''2 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Piano"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 104
    \key c \major
    \time 4/4

    \clef treble
    s1*0\mp
    <c' dis' g'>2 <g' b' d''>2 |
    <f' a' c''>2 <c' e' g'>2 |
    <g' b' d''>2 <g' b' d''>2 |
    <c' dis' g'>2 <g' b' d''>2 |
    <c' e' g'>1 |
    <g' b' d''>2 <c' dis' g'>2 |
    <g' b' d''>2 <g' b' d''>2 |
    <c' e' g'>1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Piano LH"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 104
    \key c \major
    \time 4/4

    \clef bass
    s1*0\p
    c8 g8 e8 g8 c8 g8 e8 g8 |
    f4 c'4 a4 c'4 |
    g8 d'8 b8 d'8 g8 d'8 b8 d'8 |
    c4 g4 c'4 g4 |
    c8 g8 e8 g8 c8 g8 e8 g8 |
    g4 d'4 b4 d'4 |
    g2 g8 g8 g4 |
    c1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

