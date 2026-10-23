\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Pop Guitar Song Sketch in A minor"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Clarinet melody"
    \set Staff.midiInstrument = "clarinet"
    \tempo 4 = 116
    \key a \minor
    \time 4/4

    \clef treble
    s1*0\mf
    r2 c'8 d'8 e'4 | g'4 e'8 d'8 c'4 r4 |
      e'4 g'8 a'8 g'4 e'4 | d'2 r2 |
      c'4 d'8 e'8 g'4 a'4 | b'4 a'8 g'8 e'4 r4 |
      g'4 a'8 g'8 e'4 d'4 | c'1 |
      g'4 g'8 a'8 b'4 c''4 | b'4 a'8 g'8 e'4 r4 |
      a'4 g'8 e'8 d'4 e'4 | g'2 r2 |
      c''4 b'8 a'8 g'4 e'4 | a'4 g'8 e'8 d'4 r4 |
      e'4 g'8 a'8 g'4 e'4 | c'1 |
      r2 c'8 d'8 e'4 | g'4 e'8 d'8 c'4 r4 |
      e'4 g'8 a'8 g'4 e'4 | d'2 r2 |
      c'4 d'8 e'8 g'4 a'4 | b'4 a'8 g'8 e'4 r4 |
      g'4 a'8 g'8 e'4 d'4 | c'1 |
      g'4 g'8 a'8 b'4 c''4 | b'4 a'8 g'8 e'4 r4 |
      a'4 g'8 e'8 d'4 e'4 | g'2 r2 |
      c''4 b'8 a'8 g'4 e'4 | a'4 g'8 e'8 d'4 r4 |
      e'4 g'8 a'8 g'4 e'4 | c'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitar"
    \set Staff.midiInstrument = "acoustic guitar (steel)"
    \tempo 4 = 116
    \key a \minor
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    <a c' e'>4 <e g' b'>4 <f a c'>4 <d f a>4 |
      <a c' e'>4 <g b d'>4 <f a c'>4 <e g' b'>4 |
      <f a c'>4 <g b d'>4 <a c' e'>4 <e g' b'>4 |
      <d f a>2 <e g' b'>2 |
      <a c' e'>4 <e g' b'>4 <f a c'>4 <d f a>4 |
      <d f a>4 <f a c'>4 <e g' b'>4 <e g' b'>4 |
      <f a c'>4 <g b d'>4 <e g' b'>4 <a c' e'>4 |
      <a c' e'>1 |
      <d f a>4 <a c' e'>4 <e g' b'>4 <f a c'>4 |
      <d f a>4 <f a c'>4 <e g' b'>4 <e g' b'>4 |
      <a c' e'>4 <c' e' g'>4 <d f a>4 <e g' b'>4 |
      <f a c'>2 <e g' b'>2 |
      <a c' e'>4 <e g' b'>4 <f a c'>4 <d f a>4 |
      <d f a>4 <e g' b'>4 <c' e' g'>4 <f a c'>4 |
      <d f a>4 <e g' b'>4 <f a c'>4 <e g' b'>4 |
      <a c' e'>1 |
      <a c' e'>4 <e g' b'>4 <f a c'>4 <d f a>4 |
      <a c' e'>4 <g b d'>4 <f a c'>4 <e g' b'>4 |
      <f a c'>4 <g b d'>4 <a c' e'>4 <e g' b'>4 |
      <d f a>2 <e g' b'>2 |
      <a c' e'>4 <e g' b'>4 <f a c'>4 <d f a>4 |
      <d f a>4 <f a c'>4 <e g' b'>4 <e g' b'>4 |
      <f a c'>4 <g b d'>4 <e g' b'>4 <a c' e'>4 |
      <a c' e'>1 |
      <d f a>4 <a c' e'>4 <e g' b'>4 <f a c'>4 |
      <d f a>4 <f a c'>4 <e g' b'>4 <e g' b'>4 |
      <a c' e'>4 <c' e' g'>4 <d f a>4 <e g' b'>4 |
      <f a c'>2 <e g' b'>2 |
      <a c' e'>4 <e g' b'>4 <f a c'>4 <d f a>4 |
      <d f a>4 <e g' b'>4 <c' e' g'>4 <f a c'>4 |
      <d f a>4 <e g' b'>4 <f a c'>4 <e g' b'>4 |
      <a c' e'>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

