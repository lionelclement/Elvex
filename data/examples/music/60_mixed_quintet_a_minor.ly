\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Mixed Quintet in A Minor"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 88
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
    \set Staff.instrumentName = "Violin"
    \set Staff.midiInstrument = "violin"
    \tempo 4 = 88
    \key a \minor
    \time 4/4

    \clef treble
    s1*0\mp
    cis'''4 e'''4 d'''4 cis'''4 |
    cis'''4 e'''4 d'''4 cis'''4 |
    e'''4 d'''4 cis'''4 b''4 |
    b''4 ( cis'''8 d'''8 ) cis'''2 |
    cis'''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Cello"
    \set Staff.midiInstrument = "cello"
    \tempo 4 = 88
    \key a \minor
    \time 4/4

    \clef bass
    s1*0\p
    a4 a4 e'4 e'4 |
    a4 a4 e'4 e'4 |
    d'4 d'4 e'4 e'4 |
    e'4 e'4 a4 a4 |
    a1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Horn"
    \set Staff.midiInstrument = "french horn"
    \tempo 4 = 88
    \key a \minor
    \time 4/4

    \clef treble
    s1*0\mp
    a'2 e''2 |
    a'2 e''2 |
    d''2 e''2 |
    e''2 a'2 |
    a'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Timpani"
    \set Staff.midiInstrument = "timpani"
    \tempo 4 = 88
    \key a \minor
    \time 4/4

    \clef percussion
    s1*0\p
    a4 -. a4 a4 -. a4 |
    a4 -. a4 a4 -. a4 |
    e'4 -. e'4 e'4 -. e'4 |
    a4 -. a4 e'4 -. a4 |
    a1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

