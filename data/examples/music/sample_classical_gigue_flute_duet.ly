\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Sample Classical Gigue"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute I"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 132
    \key d \major
    \time 6/8

    \clef treble
    s1*0\mf
    d''4 fis''8 a''4 fis''8 |
     d''4 fis''8 a''4 fis''8 |
     g''4 b''8 d'''4 b''8 |
     a''4 g''8 fis''4 d''8 |
     d''4 fis''8 a''4 fis''8 |
     a''4 g''8 fis''4 d''8 |
    d''4 fis''8 a''4 fis''8 |
     d''4 fis''8 a''4 fis''8 |
     g''4 b''8 d'''4 b''8 |
     a''4 g''8 fis''4 d''8 |
     d''4 fis''8 a''4 fis''8 |
     a''4 g''8 fis''4 d''8 |
    d''4 fis''8 a''4 fis''8 |
     d''4 fis''8 a''4 fis''8 |
     g''4 b''8 d'''4 b''8 |
     a''4 g''8 fis''4 d''8 |
     d''4 fis''8 a''4 fis''8 |
     a''4 g''8 fis''4 d''8 |
    d''4 fis''8 a''4 fis''8 |
     d''4 fis''8 a''4 fis''8 |
     g''4 b''8 d'''4 b''8 |
     a''4 g''8 fis''4 d''8 |
     d''4 fis''8 a''4 fis''8 |
     a''4 g''8 fis''4 d''8 |
    d''4 fis''8 a''4 fis''8 |
     d''4 fis''8 a''4 fis''8 |
     g''4 b''8 d'''4 b''8 |
     a''4 g''8 fis''4 d''8 |
     d''4 fis''8 a''4 fis''8 |
     a''4 g''8 fis''4 d''8 |
    d''4 fis''8 a''4 fis''8 |
     d''4 fis''8 a''4 fis''8 |
     g''4 b''8 d'''4 b''8 |
     a''4 g''8 fis''4 d''8 |
     d''4 fis''8 a''4 fis''8 |
     a''4 g''8 fis''4 d''8 |
    d''4 fis''8 a''4 fis''8 |
     d''4 fis''8 a''4 fis''8 |
     g''4 b''8 d'''4 b''8 |
     a''4 g''8 fis''4 d''8 |
     d''4 fis''8 a''4 fis''8 |
     a''4 g''8 fis''4 d''8 |
    d''4 fis''8 a''4 fis''8 |
     d''4 fis''8 a''4 fis''8 |
     g''4 b''8 d'''4 b''8 |
     a''4 g''8 fis''4 d''8 |
     d''4 fis''8 a''4 fis''8 |
     a''4 g''8 fis''4 d''8 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Flute II"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 132
    \key d \major
    \time 6/8

    \clef treble
    s1*0\mp
    r2. |
     r2. |
     r2. |
     r2. |
     r2. |
     r2. |
    d'8 a'8 fis'8 d'8 a'8 fis'8 |
     a'8 e''8 cis''8 a'8 e''8 cis''8 |
     d'8 a'8 fis'8 d'8 a'8 fis'8 |
     a'8 g'8 fis'8 e'8 d'8 d'8 |
     d'8 a'8 fis'8 d'8 a'8 fis'8 |
     a'8 g'8 fis'8 e'8 d'8 d'8 |
    d'8 a'8 fis'8 d'8 a'8 fis'8 |
     a'8 e''8 cis''8 a'8 e''8 cis''8 |
     d'8 a'8 fis'8 d'8 a'8 fis'8 |
     a'8 g'8 fis'8 e'8 d'8 d'8 |
     d'8 a'8 fis'8 d'8 a'8 fis'8 |
     a'8 g'8 fis'8 e'8 d'8 d'8 |
    r2. |
     r2. |
     r2. |
     r2. |
     r2. |
     r2. |
    d'8 a'8 fis'8 d'8 a'8 fis'8 |
     a'8 e''8 cis''8 a'8 e''8 cis''8 |
     d'8 a'8 fis'8 d'8 a'8 fis'8 |
     a'8 g'8 fis'8 e'8 d'8 d'8 |
     d'8 a'8 fis'8 d'8 a'8 fis'8 |
     a'8 g'8 fis'8 e'8 d'8 d'8 |
    d'8 a'8 fis'8 d'8 a'8 fis'8 |
     a'8 e''8 cis''8 a'8 e''8 cis''8 |
     d'8 a'8 fis'8 d'8 a'8 fis'8 |
     a'8 g'8 fis'8 e'8 d'8 d'8 |
     d'8 a'8 fis'8 d'8 a'8 fis'8 |
     a'8 g'8 fis'8 e'8 d'8 d'8 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

