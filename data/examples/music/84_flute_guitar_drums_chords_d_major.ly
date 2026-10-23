\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Flute Guitar and Drums in D major"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 112
    \key d \major
    \time 4/4

    \clef treble
    s1*0\mf
    d''4 e''4 fis''4 a''4 |
    a''4 ( b''8 cis'''8 ) d'''2 |
    d'''4 cis'''4 b''4 a''4 |
    fis''4 ( g''8 a''8 ) d''2 |
    d''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitar"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 112
    \key d \major
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    <d' fis' a'>2 <a' cis'' e''>2 |
    d'8 ( a'8 d''4 ) fis''2 |
    <d' f' a'>4 <g' ais' d''>4 <a' cis'' e''>4 <d' f' a'>4 |
    a'4 d''8 fis'8 d'2 |
    <d' f' a'>1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Drum Kit"
    \set Staff.midiInstrument = "standard kit"
    \tempo 4 = 112
    \key d \major
    \time 4/4

    \clef percussion
    s1*0\mp
    d4 -. a4 d4 -. a4 |
    d4 -. a4 d4 -. a4 |
    a4 r4 a4 d4 |
    d4 -. a4 a4 -. d4 |
    d1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

