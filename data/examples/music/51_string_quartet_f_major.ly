\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "String Quartet in F Major"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Violin I"
    \set Staff.midiInstrument = "violin"
    \tempo 4 = 104
    \key f \major
    \time 4/4

    \clef treble
    s1*0\mf
    f''4 g''4 a''4 c'''4 |
    c'''4 ( d'''8 e'''8 ) f'''2 |
    f'''4 e'''4 d'''4 c'''4 |
    a''4 ( bes''8 c'''8 ) f''2 |
    f''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Violin II"
    \set Staff.midiInstrument = "violin"
    \tempo 4 = 104
    \key f \major
    \time 4/4

    \clef treble
    s1*0\mp
    a''4 c'''4 bes''4 a''4 |
    a''4 c'''4 bes''4 a''4 |
    c'''4 bes''4 a''4 g''4 |
    g''4 ( a''8 bes''8 ) a''2 |
    a''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Viola"
    \set Staff.midiInstrument = "viola"
    \tempo 4 = 104
    \key f \major
    \time 4/4

    \clef alto
    s1*0\mp
    a'2 bes'2 |
    a'2 bes'2 |
    c''2 bes'2 |
    a'2 g'2 |
    f'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Cello"
    \set Staff.midiInstrument = "cello"
    \tempo 4 = 104
    \key f \major
    \time 4/4

    \clef bass
    s1*0\p
    f4 f4 c'4 c'4 |
    f4 f4 c'4 c'4 |
    bes4 bes4 c'4 c'4 |
    c'4 c'4 f4 f4 |
    f1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

