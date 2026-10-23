\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Gigue for Two Flutes"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute I"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 124
    \key g \major
    \time 6/8

    \clef treble
    s1*0\mf
    g''4 b''8 d'''4 b''8 |
     g''4 b''8 d'''4 b''8 |
     c'''4 e'''8 g'''4 e'''8 |
     d'''4 c'''8 b''4 g''8 |
     g''4 b''8 d'''4 b''8 |
     d'''4 c'''8 b''4 g''8 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Flute II"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 124
    \key g \major
    \time 6/8

    \clef treble
    s1*0\mp
    g'8 d''8 b'8 g'8 d''8 b'8 |
     d''8 a''8 fis''8 d''8 a''8 fis''8 |
     g'8 d''8 b'8 g'8 d''8 b'8 |
     d''8 c''8 b'8 a'8 g'8 g'8 |
     g'8 d''8 b'8 g'8 d''8 b'8 |
     d''8 c''8 b'8 a'8 g'8 g'8 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

