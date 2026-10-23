\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Pop Guitar Song Sketch in C"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Alto sax melody"
    \set Staff.midiInstrument = "alto sax"
    \tempo 4 = 124
    \key c \major
    \time 4/4

    \clef alto
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
    \tempo 4 = 124
    \key c \major
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

