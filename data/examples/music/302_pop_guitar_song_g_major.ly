\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Pop Guitar Song Sketch in G"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Harmonica melody"
    \set Staff.midiInstrument = "harmonica"
    \tempo 4 = 128
    \key g \major
    \time 4/4

    \clef treble
    s1*0\mf
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
    \tempo 4 = 128
    \key g \major
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    <g b d'>4 <d' fis' a'>4 <e' g' b'>4 <c' e' g'>4 |
      <g b d'>4 <d' fis' a'>4 <c' e' g'>4 <c' e' g'>4 |
      <e' g' b'>4 <c' e' g'>4 <g b d'>4 <d' fis' a'>4 |
      <c' e' g'>2 <d' fis' a'>2 |
      <g b d'>4 <d' fis' a'>4 <e' g' b'>4 <c' e' g'>4 |
      <a c' e'>4 <c' e' g'>4 <d' fis' a'>4 <d' fis' a'>4 |
      <e' g' b'>4 <d' fis' a'>4 <c' e' g'>4 <g b d'>4 |
      <g b d'>1 |
      <c' e' g'>4 <g b d'>4 <d' fis' a'>4 <e' g' b'>4 |
      <a c' e'>4 <c' e' g'>4 <d' fis' a'>4 <d' fis' a'>4 |
      <g b d'>4 <b d' fis'>4 <c' e' g'>4 <d' fis' a'>4 |
      <e' g' b'>2 <d' fis' a'>2 |
      <g b d'>4 <d' fis' a'>4 <e' g' b'>4 <c' e' g'>4 |
      <c' e' g'>4 <d' fis' a'>4 <b d' fis'>4 <e' g' b'>4 |
      <a c' e'>4 <d' fis' a'>4 <c' e' g'>4 <d' fis' a'>4 |
      <g b d'>1 |
      <g b d'>4 <d' fis' a'>4 <e' g' b'>4 <c' e' g'>4 |
      <g b d'>4 <d' fis' a'>4 <c' e' g'>4 <c' e' g'>4 |
      <e' g' b'>4 <c' e' g'>4 <g b d'>4 <d' fis' a'>4 |
      <c' e' g'>2 <d' fis' a'>2 |
      <g b d'>4 <d' fis' a'>4 <e' g' b'>4 <c' e' g'>4 |
      <a c' e'>4 <c' e' g'>4 <d' fis' a'>4 <d' fis' a'>4 |
      <e' g' b'>4 <d' fis' a'>4 <c' e' g'>4 <g b d'>4 |
      <g b d'>1 |
      <c' e' g'>4 <g b d'>4 <d' fis' a'>4 <e' g' b'>4 |
      <a c' e'>4 <c' e' g'>4 <d' fis' a'>4 <d' fis' a'>4 |
      <g b d'>4 <b d' fis'>4 <c' e' g'>4 <d' fis' a'>4 |
      <e' g' b'>2 <d' fis' a'>2 |
      <g b d'>4 <d' fis' a'>4 <e' g' b'>4 <c' e' g'>4 |
      <c' e' g'>4 <d' fis' a'>4 <b d' fis'>4 <e' g' b'>4 |
      <a c' e'>4 <d' fis' a'>4 <c' e' g'>4 <d' fis' a'>4 |
      <g b d'>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

