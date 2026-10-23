\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Flute Guitar and Drums in A Minor"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 104
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
    \tempo 4 = 104
    \key a \minor
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    <a' cis'' e''>2 <e'' gis'' b''>2 |
    a'8 ( e''8 a''4 ) cis'''2 |
    <a' c'' e''>4 <d'' f'' a''>4 <e'' gis'' b''>4 <a' c'' e''>4 |
    e''4 a''8 cis''8 a'2 |
    <a' c'' e''>1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Drum Kit"
    \set Staff.midiInstrument = "standard kit"
    \tempo 4 = 104
    \key a \minor
    \time 4/4

    \clef percussion
    s1*0\mp
    a4 -. e'4 a4 -. e'4 |
    a4 -. e'4 a4 -. e'4 |
    e'4 r4 e'4 a4 |
    a4 -. e'4 e'4 -. a4 |
    a1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

