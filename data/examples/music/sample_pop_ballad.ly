\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Sample Pop Ballad"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Lead melody"
    \set Staff.midiInstrument = "choir aahs"
    \tempo 4 = 78
    \key a \minor
    \time 4/4

    \clef treble
    s1*0\mp
    r2 g'8 a'8 b'4 | d''4 b'8 a'8 g'4 r4 |
      b'4 d''8 e''8 d''4 b'4 | a'2 r2 |
      g'4 a'8 b'8 d''4 e''4 | fis''4 e''8 d''8 b'4 r4 |
      d''4 e''8 d''8 b'4 a'4 | g'1 |
      d''4 d''8 e''8 fis''4 g''4 | fis''4 e''8 d''8 b'4 r4 |
      e''4 d''8 b'8 a'4 b'4 | d''2 r2 |
      g''4 fis''8 e''8 d''4 b'4 | e''4 d''8 b'8 a'4 r4 |
      b'4 d''8 e''8 d''4 b'4 | g'1 |
      r2 g'8 a'8 b'4 | d''4 b'8 a'8 g'4 r4 |
      b'4 d''8 e''8 d''4 b'4 | a'2 r2 |
      g'4 a'8 b'8 d''4 e''4 | fis''4 e''8 d''8 b'4 r4 |
      d''4 e''8 d''8 b'4 a'4 | g'1 |
      d''4 d''8 e''8 fis''4 g''4 | fis''4 e''8 d''8 b'4 r4 |
      e''4 d''8 b'8 a'4 b'4 | d''2 r2 |
      g''4 fis''8 e''8 d''4 b'4 | e''4 d''8 b'8 a'4 r4 |
      b'4 d''8 e''8 d''4 b'4 | g'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitar"
    \set Staff.midiInstrument = "acoustic guitar (steel)"
    \tempo 4 = 78
    \key a \minor
    \time 4/4

    \clef "treble_8"
    s1*0\p
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

