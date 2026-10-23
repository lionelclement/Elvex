\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Dotted Rhythm for Two Flutes"
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
    d''8. e''16 fis''4 a''2 |
     d''8. e''16 fis''4 a''2 |
     g''8. a''16 b''4 d'''2 |
     a''8. g''16 fis''4 d''2 |
     d''8. e''16 fis''4 a''2 |
     a''8. g''16 fis''4 d''2 |
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
    d'4 -. a'4 d'4 -. a'4 |
     d'8. a'16 fis'4 d'2 |
     d'4 -. a'4 d'4 -. a'4 |
     d'8. a'16 fis'4 d'2 |
     d'4 -. a'4 d'4 -. a'4 |
     d'8. a'16 fis'4 d'2 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

