\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Long Ternary for Two Flutes"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute I"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 96
    \key d \major
    \time 4/4

    \clef treble
    s1*0\mf
    d''4 e''4 fis''4 a''4 |
     a''4 b''8 a''8 g''2 |
     e''4 fis''4 gis''4 a''4 |
     a''4 g''4 fis''4 d''4 |
     d''4 e''4 fis''4 a''4 |
     fis''8 g''8 a''4 b''2 |
     e''4 fis''4 gis''4 a''4 |
     d''1 |
    a''4 b''8 cis'''8 d'''2 |
     fis''8 g''8 a''4 b''2 |
     d'''4 cis'''4 b''4 a''4 |
     e''4 fis''4 gis''4 a''4 |
     b''8 a''8 g''4 fis''2 |
     a''4 b''8 a''8 g''2 |
     e''4 fis''4 gis''4 a''4 |
     a''4 g''4 fis''4 d''4 |
    d''4 e''4 fis''4 a''4 |
     fis''8 a''8 b''4 a''2 |
     fis''8 g''8 a''4 b''2 |
     a''4 g''4 fis''4 d''4 |
     a''4 b''8 cis'''8 d'''2 |
     b''8 a''8 g''4 fis''2 |
     e''4 fis''4 gis''4 a''4 |
     d''1 |
    fis''8 g''8 a''4 b''2 |
     e''4 fis''4 gis''4 a''4 |
     d'''4 cis'''4 b''4 a''4 |
     a''4 g''4 fis''4 d''4 |
     b''8 a''8 g''4 fis''2 |
     e''4 fis''4 gis''4 a''4 |
     a''4 g''4 fis''4 d''4 |
     d''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Flute II"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 96
    \key d \major
    \time 4/4

    \clef treble
    s1*0\mp
    d'2 fis'2 |
     fis'2 a'2 |
     a'2 gis'2 |
     d'2 fis'2 |
     d'2 e'2 |
     fis'2 a'2 |
     a'2 gis'2 |
     d'1 |
    a'2 gis'2 |
     e'4 fis'4 g'4 a'4 |
     b'2 a'2 |
     a'2 gis'2 |
     d'2 e'2 |
     e'4 fis'4 g'4 a'4 |
     a'2 gis'2 |
     d'2 fis'2 |
    d'2 fis'2 |
     e'4 fis'4 g'4 a'4 |
     a'2 gis'2 |
     d'2 fis'2 |
     d'2 e'2 |
     fis'2 a'2 |
     a'2 gis'2 |
     d'1 |
    e'4 fis'4 g'4 a'4 |
     a'2 gis'2 |
     b'2 a'2 |
     a'2 gis'2 |
     d'2 e'2 |
     a'2 gis'2 |
     d'2 fis'2 |
     d'1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

