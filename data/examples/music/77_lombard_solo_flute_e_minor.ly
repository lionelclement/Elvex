\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Lombard Study for Solo Flute in E Minor"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 96
    \key e \minor
    \time 4/4

    \clef treble
    s1*0\mf
    e''16 fis''8. gis''4 b''2 |
     e''16 fis''8. gis''4 b''2 |
     a''16 b''8. cis'''4 e'''2 |
     b''16 a''8. gis''4 e''2 |
     e''16 fis''8. gis''4 b''2 |
     b''16 a''8. gis''4 e''2 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

