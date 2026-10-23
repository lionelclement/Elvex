\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Guitar Chords with Drums in E minor"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Guitar"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 112
    \key e \minor
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    <e' gis' b'>2 <b' dis'' fis''>2 |
    e'8 ( b'8 e''4 ) gis''2 |
    <e' g' b'>4 <a' c'' e''>4 <b' dis'' fis''>4 <e' g' b'>4 |
    b'4 e''8 gis'8 e'2 |
    <e' g' b'>1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Drum Kit"
    \set Staff.midiInstrument = "standard kit"
    \tempo 4 = 112
    \key e \minor
    \time 4/4

    \clef percussion
    s1*0\mp
    e4 -. b4 e4 -. b4 |
    e4 -. b4 e4 -. b4 |
    b4 r4 b4 e4 |
    e4 -. b4 b4 -. e4 |
    e1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

