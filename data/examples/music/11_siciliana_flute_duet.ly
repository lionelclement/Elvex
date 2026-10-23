\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Siciliana for Two Flutes"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute I"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 72
    \key f \major
    \time 6/8

    \clef treble
    s1*0\mf
    f''8. g''16 a''8 c'''8. bes''16 a''8 |
     a''8. bes''16 c'''8 d'''8. c'''16 bes''8 |
     bes''8. c'''16 d'''8 f'''8. e'''16 d'''8 |
     c'''8. bes''16 a''8 g''8. f''16 f''8 |
     f''8. g''16 a''8 c'''8. bes''16 a''8 |
     c'''8. bes''16 a''8 g''8. f''16 f''8 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Flute II"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 72
    \key f \major
    \time 6/8

    \clef treble
    s1*0\mp
    f'8 c''8 a'8 f'8 c''8 a'8 |
     c''8 g''8 e''8 c''8 g''8 e''8 |
     f'8 c''8 a'8 f'8 c''8 a'8 |
     c''8 bes'8 a'8 g'8 f'8 f'8 |
     f'8 c''8 a'8 f'8 c''8 a'8 |
     c''8 bes'8 a'8 g'8 f'8 f'8 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

