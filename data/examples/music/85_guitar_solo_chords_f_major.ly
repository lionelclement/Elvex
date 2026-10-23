\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Guitar Chord Study in F major"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Guitar"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 88
    \key f \major
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    <f' a' c''>2 <c'' e'' g''>2 |
    f'8 ( c''8 f''4 ) a''2 |
    <f' aes' c''>4 <bes' des'' f''>4 <c'' e'' g''>4 <f' aes' c''>4 |
    c''4 f''8 a'8 f'2 |
    <f' aes' c''>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

