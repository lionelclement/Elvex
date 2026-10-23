\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Brass Trio in D Minor"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Trumpet"
    \set Staff.midiInstrument = "trumpet"
    \tempo 4 = 84
    \key d \minor
    \time 4/4

    \clef treble
    s1*0\mf
    d'4 e'4 ges'4 a'4 |
    a'4 ( b'8 des''8 ) d''2 |
    d''4 des''4 b'4 a'4 |
    ges'4 ( g'8 a'8 ) d'2 |
    d'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Horn"
    \set Staff.midiInstrument = "french horn"
    \tempo 4 = 84
    \key d \minor
    \time 4/4

    \clef treble
    s1*0\mp
    d'2 a'2 |
    d'2 a'2 |
    g'2 a'2 |
    a'2 d'2 |
    d'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Trombone"
    \set Staff.midiInstrument = "trombone"
    \tempo 4 = 84
    \key d \minor
    \time 4/4

    \clef bass
    s1*0\p
    d4 d4 a4 a4 |
    d4 d4 a4 a4 |
    g4 g4 a4 a4 |
    a4 a4 d4 d4 |
    d1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

