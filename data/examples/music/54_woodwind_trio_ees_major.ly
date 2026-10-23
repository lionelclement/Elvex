\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Woodwind Trio in Ees Major"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Oboe"
    \set Staff.midiInstrument = "oboe"
    \tempo 4 = 96
    \key ees \major
    \time 4/4

    \clef treble
    s1*0\mf
    ees''4 f''4 g''4 bes''4 |
    bes''4 ( c'''8 d'''8 ) ees'''2 |
    ees'''4 d'''4 c'''4 bes''4 |
    g''4 ( aes''8 bes''8 ) ees''2 |
    ees''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Clarinet"
    \set Staff.midiInstrument = "clarinet"
    \tempo 4 = 96
    \key ees \major
    \time 4/4

    \clef treble
    s1*0\mp
    g'4 bes'4 aes'4 g'4 |
    g'4 bes'4 aes'4 g'4 |
    bes'4 aes'4 g'4 f'4 |
    f'4 ( g'8 aes'8 ) g'2 |
    g'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Bassoon"
    \set Staff.midiInstrument = "bassoon"
    \tempo 4 = 96
    \key ees \major
    \time 4/4

    \clef bass
    s1*0\p
    ees4 ees4 bes4 bes4 |
    ees4 ees4 bes4 bes4 |
    aes4 aes4 bes4 bes4 |
    bes4 bes4 ees4 ees4 |
    ees1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

