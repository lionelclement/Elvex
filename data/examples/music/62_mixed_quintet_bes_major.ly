\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Mixed Quintet in Bes Major"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 100
    \key bes \major
    \time 4/4

    \clef treble
    s1*0\mf
    bes''4 c'''4 d'''4 f'''4 |
    f'''4 ( g'''8 a'''8 ) bes'''2 |
    bes'''4 a'''4 g'''4 f'''4 |
    d'''4 ( ees'''8 f'''8 ) bes''2 |
    bes''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Violin"
    \set Staff.midiInstrument = "violin"
    \tempo 4 = 100
    \key bes \major
    \time 4/4

    \clef treble
    s1*0\mp
    d'''4 f'''4 ees'''4 d'''4 |
    d'''4 f'''4 ees'''4 d'''4 |
    f'''4 ees'''4 d'''4 c'''4 |
    c'''4 ( d'''8 ees'''8 ) d'''2 |
    d'''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Cello"
    \set Staff.midiInstrument = "cello"
    \tempo 4 = 100
    \key bes \major
    \time 4/4

    \clef bass
    s1*0\p
    bes4 bes4 f'4 f'4 |
    bes4 bes4 f'4 f'4 |
    ees'4 ees'4 f'4 f'4 |
    f'4 f'4 bes4 bes4 |
    bes1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Horn"
    \set Staff.midiInstrument = "french horn"
    \tempo 4 = 100
    \key bes \major
    \time 4/4

    \clef treble
    s1*0\mp
    bes'2 f''2 |
    bes'2 f''2 |
    ees''2 f''2 |
    f''2 bes'2 |
    bes'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Timpani"
    \set Staff.midiInstrument = "timpani"
    \tempo 4 = 100
    \key bes \major
    \time 4/4

    \clef percussion
    s1*0\p
    bes4 -. bes4 bes4 -. bes4 |
    bes4 -. bes4 bes4 -. bes4 |
    f'4 -. f'4 f'4 -. f'4 |
    bes4 -. bes4 f'4 -. bes4 |
    bes1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

