\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Flute and Guitar Chords in A minor"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 96
    \key a \minor
    \time 4/4

    \clef treble
    s1*0\mf
    a''4 b''4 cis'''4 e'''4 |
    e'''4 ( fis'''8 gis'''8 ) a'''2 |
    a'''4 gis'''4 fis'''4 e'''4 |
    cis'''4 ( d'''8 e'''8 ) a''2 |
    a''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitar"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 96
    \key a \minor
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    <a' c'' e''>2 <e'' gis'' b''>2 |
    a'8 ( e''8 a''4 ) cis'''2 |
    <a' cis'' e''>4 <d'' fis'' a''>4 <e'' gis'' b''>4 <a' cis'' e''>4 |
    e''4 a''8 cis''8 a'2 |
    <a' c'' e''>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

