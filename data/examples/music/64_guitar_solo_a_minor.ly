\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Guitar Solo in A Minor"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Guitar"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 88
    \key a \minor
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    <a' cis'' e''>2 <e'' gis'' b''>2 |
    a'8 ( e''8 a''4 ) cis'''2 |
    <a' cis'' e''>4 <d'' fis'' a''>4 <e'' gis'' b''>4 <a' cis'' e''>4 |
    e''4 a''8 cis''8 a'2 |
    <a' cis'' e''>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

