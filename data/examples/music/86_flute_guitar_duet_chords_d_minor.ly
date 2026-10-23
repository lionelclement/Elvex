\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Flute and Guitar Chords in D minor"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 92
    \key d \minor
    \time 4/4

    \clef treble
    s1*0\mf
    d''4 e''4 ges''4 a''4 |
    a''4 ( b''8 des'''8 ) d'''2 |
    d'''4 des'''4 b''4 a''4 |
    ges''4 ( g''8 a''8 ) d''2 |
    d''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitar"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 92
    \key d \minor
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    <d' f' a'>2 <a' des'' e''>2 |
    d'8 ( a'8 d''4 ) ges''2 |
    <d' f' a'>4 <g' bes' d''>4 <a' des'' e''>4 <d' f' a'>4 |
    a'4 d''8 ges'8 d'2 |
    <d' ges' a'>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

