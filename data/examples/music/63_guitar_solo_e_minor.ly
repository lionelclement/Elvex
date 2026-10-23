\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Guitar Solo in E Minor"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Guitar"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 92
    \key e \minor
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    <e' gis' b'>2 <b' dis'' fis''>2 |
    e'8 ( b'8 e''4 ) gis''2 |
    <e' gis' b'>4 <a' cis'' e''>4 <b' dis'' fis''>4 <e' gis' b'>4 |
    b'4 e''8 gis'8 e'2 |
    <e' g' b'>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

