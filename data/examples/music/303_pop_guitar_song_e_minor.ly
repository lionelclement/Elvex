\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Pop Guitar Song Sketch in E minor"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Voice oohs melody"
    \set Staff.midiInstrument = "voice oohs"
    \tempo 4 = 120
    \key e \minor
    \time 4/4

    \clef treble
    s1*0\mf
    r2 e'8 fis'8 g'4 | b'4 g'8 fis'8 e'4 r4 |
      g'4 b'8 c''8 b'4 g'4 | fis'2 r2 |
      e'4 fis'8 g'8 b'4 c''4 | d''4 c''8 b'8 g'4 r4 |
      b'4 c''8 b'8 g'4 fis'4 | e'1 |
      b'4 b'8 c''8 d''4 e''4 | d''4 c''8 b'8 g'4 r4 |
      c''4 b'8 g'8 fis'4 g'4 | b'2 r2 |
      e''4 d''8 c''8 b'4 g'4 | c''4 b'8 g'8 fis'4 r4 |
      g'4 b'8 c''8 b'4 g'4 | e'1 |
      r2 e'8 fis'8 g'4 | b'4 g'8 fis'8 e'4 r4 |
      g'4 b'8 c''8 b'4 g'4 | fis'2 r2 |
      e'4 fis'8 g'8 b'4 c''4 | d''4 c''8 b'8 g'4 r4 |
      b'4 c''8 b'8 g'4 fis'4 | e'1 |
      b'4 b'8 c''8 d''4 e''4 | d''4 c''8 b'8 g'4 r4 |
      c''4 b'8 g'8 fis'4 g'4 | b'2 r2 |
      e''4 d''8 c''8 b'4 g'4 | c''4 b'8 g'8 fis'4 r4 |
      g'4 b'8 c''8 b'4 g'4 | e'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitar"
    \set Staff.midiInstrument = "acoustic guitar (steel)"
    \tempo 4 = 120
    \key e \minor
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    <e g b>4 <b d' fis'>4 <c' e' g'>4 <a c' e'>4 |
      <e g b>4 <d' fis' a'>4 <c' e' g'>4 <b d' fis'>4 |
      <c' e' g'>4 <d' fis' a'>4 <e g b>4 <b d' fis'>4 |
      <a c' e'>2 <b d' fis'>2 |
      <e g b>4 <b d' fis'>4 <c' e' g'>4 <a c' e'>4 |
      <a c' e'>4 <c' e' g'>4 <b d' fis'>4 <b d' fis'>4 |
      <c' e' g'>4 <d' fis' a'>4 <b d' fis'>4 <e g b>4 |
      <e g b>1 |
      <a c' e'>4 <e g b>4 <b d' fis'>4 <c' e' g'>4 |
      <a c' e'>4 <c' e' g'>4 <b d' fis'>4 <b d' fis'>4 |
      <e g b>4 <g b d'>4 <a c' e'>4 <b d' fis'>4 |
      <c' e' g'>2 <b d' fis'>2 |
      <e g b>4 <b d' fis'>4 <c' e' g'>4 <a c' e'>4 |
      <a c' e'>4 <b d' fis'>4 <g b d'>4 <c' e' g'>4 |
      <a c' e'>4 <b d' fis'>4 <c' e' g'>4 <b d' fis'>4 |
      <e g b>1 |
      <e g b>4 <b d' fis'>4 <c' e' g'>4 <a c' e'>4 |
      <e g b>4 <d' fis' a'>4 <c' e' g'>4 <b d' fis'>4 |
      <c' e' g'>4 <d' fis' a'>4 <e g b>4 <b d' fis'>4 |
      <a c' e'>2 <b d' fis'>2 |
      <e g b>4 <b d' fis'>4 <c' e' g'>4 <a c' e'>4 |
      <a c' e'>4 <c' e' g'>4 <b d' fis'>4 <b d' fis'>4 |
      <c' e' g'>4 <d' fis' a'>4 <b d' fis'>4 <e g b>4 |
      <e g b>1 |
      <a c' e'>4 <e g b>4 <b d' fis'>4 <c' e' g'>4 |
      <a c' e'>4 <c' e' g'>4 <b d' fis'>4 <b d' fis'>4 |
      <e g b>4 <g b d'>4 <a c' e'>4 <b d' fis'>4 |
      <c' e' g'>2 <b d' fis'>2 |
      <e g b>4 <b d' fis'>4 <c' e' g'>4 <a c' e'>4 |
      <a c' e'>4 <b d' fis'>4 <g b d'>4 <c' e' g'>4 |
      <a c' e'>4 <b d' fis'>4 <c' e' g'>4 <b d' fis'>4 |
      <e g b>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

