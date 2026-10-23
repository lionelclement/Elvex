\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Brass Trio in F Major"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Trumpet"
    \set Staff.midiInstrument = "trumpet"
    \tempo 4 = 92
    \key f \major
    \time 4/4

    \clef treble
    s1*0\mf
    f'4 g'4 a'4 c''4 |
    c''4 ( d''8 e''8 ) f''2 |
    f''4 e''4 d''4 c''4 |
    a'4 ( bes'8 c''8 ) f'2 |
    f'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Horn"
    \set Staff.midiInstrument = "french horn"
    \tempo 4 = 92
    \key f \major
    \time 4/4

    \clef treble
    s1*0\mp
    f'2 c''2 |
    f'2 c''2 |
    bes'2 c''2 |
    c''2 f'2 |
    f'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Trombone"
    \set Staff.midiInstrument = "trombone"
    \tempo 4 = 92
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

