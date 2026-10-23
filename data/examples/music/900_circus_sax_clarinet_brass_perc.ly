\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Structured Circus Fanfare"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Alto Sax"
    \set Staff.midiInstrument = "alto sax"
    \tempo 4 = 96
    \key c \major
    \time 2/4

    \clef treble
    s1*0\f
    c'8 d'8 e'8 g'8 |
    a'8 g'8 b'8 g'8 |
    e'8 g'8 a'8 g'8 |
    b'4 g'4 |
    f'8 g'8 a'8 c''8 |
    d''8 ( c''8 a'8 ) b'8 |
    d''8 c''8 b'8 a'8 |
    g'4 c'4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Clarinet"
    \set Staff.midiInstrument = "clarinet"
    \tempo 4 = 96
    \key c \major
    \time 2/4

    \clef treble
    s1*0\mf
    r2 |
    e''8 r8 g''8 a''8 |
    r2 |
    a''8 r8 g''8 e''8 |
    c'''8 a''8 g''8 f''8 |
    a''8 r8 b''8 c'''8 |
    r2 |
    e''4 c''4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Trumpet"
    \set Staff.midiInstrument = "trumpet"
    \tempo 4 = 96
    \key c \major
    \time 2/4

    \clef treble
    s1*0\f
    g''4 c'''4 |
    g''4 b''4 |
    r2 |
    b''4 g''4 |
    f''4 c'''4 |
    a''4 b''4 |
    g''4 b''4 |
    c'''4 c''4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Trombone"
    \set Staff.midiInstrument = "trombone"
    \tempo 4 = 96
    \key c \major
    \time 2/4

    \clef bass
    s1*0\mf
    c8 r8 g8 c8 |
    r2 |
    c8 r8 e8 g8 |
    g4 g4 |
    f8 r8 a8 c'8 |
    r2 |
    g4 b4 |
    c4 c4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Tuba"
    \set Staff.midiInstrument = "tuba"
    \tempo 4 = 96
    \key c \major
    \time 2/4

    \clef bass
    s1*0\mf
    c,4 g,4 |
    g,4 d4 |
    c,4 g,4 |
    g,4 g,4 |
    f,4 c4 |
    d,4 g,4 |
    g,4 d4 |
    c,4 c,4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Percussion"
    \set Staff.midiInstrument = "woodblock"
    \tempo 4 = 96
    \key c \major
    \time 2/4

    \clef percussion
    s1*0\f
    c4 g4 |
    c8 r8 g8 c8 |
    c4 g4 |
    g8 r8 g8 c8 |
    c4 g4 |
    c8 r8 g8 c8 |
    c8 -. c8 g8 -. g8 |
    c4 c4 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

