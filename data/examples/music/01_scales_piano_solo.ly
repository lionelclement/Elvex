\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Scale Studies for Piano"
  composer = "Elvex"
}
\score {
<<
    \new Staff = "right" {
    \set Staff.instrumentName = "Piano"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 72
    \key c \major
    \time 4/4

    \clef treble
    s1*0\mp
    \set Staff.instrumentName = "Sons tenus"
    \set Staff.shortInstrumentName = "Sons tenus"
     c'1 \fermata |
     d'1 \fermata |
     e'1 \fermata |
     f'1 \fermata |
     g'1 \fermata |
     a'1 \fermata |
     b'1 \fermata |
     c''1 \fermata |
     d''1 \fermata |
     e''1 \fermata |
     f''1 \fermata |
     g''1 \fermata |
     a''1 \fermata |
     b''1 \fermata |
     c'''1 \fermata |
     d'''1 \fermata |
     e'''1 \fermata |
     f'''1 \fermata |
     g'''1 \fermata |
     a'''1 \fermata |
     b'''1 \fermata |
   \break
     \set Staff.instrumentName = "Gamme sans liaison"
    \set Staff.shortInstrumentName = "Gamme sans liaison"
     c'4 d'8 e'8 f'8 g'8 a'8 b'8 |
     c''4 d''8 e''8 f''8 g''8 a''8 b''8 |
     c'''4 d'''8 e'''8 f'''8 g'''8 a'''8 b'''8 |
     a'''4 g'''8 f'''8 e'''8 d'''8 c'''8 b''8 |
     a''4 g''8 f''8 e''8 d''8 c''8 b'8 |
     a'4 g'8 f'8 e'8 d'8 c'8 c'8 |
   \break
     \set Staff.instrumentName = "Gamme avec liaison"
    \set Staff.shortInstrumentName = "Gamme avec liaison"
     c'4 ( d'8 e'8 f'8 g'8 a'8 b'8 ) |
     c''4 ( d''8 e''8 f''8 g''8 a''8 b''8 ) |
     c'''4 ( d'''8 e'''8 f'''8 g'''8 a'''8 b'''8 ) |
     a'''4 ( g'''8 f'''8 e'''8 d'''8 c'''8 b''8 ) |
     a''4 ( g''8 f''8 e''8 d''8 c''8 b'8 ) |
     a'4 ( g'8 f'8 e'8 d'8 c'8 c'8 ) |
   \break
     \set Staff.instrumentName = "Tierces"
    \set Staff.shortInstrumentName = "Tierces"
     c'8 e'8 d'8 f'8 e'8 g'8 f'8 a'8 |
     g'8 b'8 a'8 c''8 b'8 d''8 c''8 e''8 |
     d''8 f''8 e''8 g''8 f''8 a''8 g''8 b''8 |
     a''8 c'''8 b''8 d'''8 c'''8 e'''8 d'''8 f'''8 |
     f'''8 d'''8 e'''8 c'''8 d'''8 b''8 c'''8 a''8 |
     b''8 g''8 a''8 f''8 g''8 e''8 f''8 d''8 |
     e''8 c''8 d''8 b'8 c''8 a'8 b'8 g'8 |
     a'8 f'8 g'8 e'8 f'8 d'8 e'8 c'8 |
   \break
     \set Staff.instrumentName = "Tonique"
    \set Staff.shortInstrumentName = "Tonique"
     c'8 e'8 g'8 c''8 e'8 g'8 c''8 e''8 |
     g'8 c''8 e''8 g''8 c''8 e''8 g''8 c'''8 |
     e''8 g''8 c'''8 e'''8 g''8 c'''8 e'''8 g'''8 |
     g'''8 e'''8 c'''8 g''8 e'''8 c'''8 g''8 e''8 |
     c'''8 g''8 e''8 c''8 g''8 e''8 c''8 g'8 |
     e''8 c''8 g'8 e'8 c''8 g'8 e'8 c'8 |
   \break
     \set Staff.instrumentName = "Dominante 7e"
    \set Staff.shortInstrumentName = "Dominante 7e"
     g'8 b'8 d''8 f''8 b'8 d''8 f''8 g''8 |
     d''8 f''8 g''8 b''8 f''8 g''8 b''8 d'''8 |
     g''8 b''8 d'''8 f'''8 b''8 d'''8 f'''8 g'''8 |
     g'''8 f'''8 d'''8 b''8 f'''8 d'''8 b''8 g''8 |
     d'''8 b''8 g''8 f''8 b''8 g''8 f''8 d''8 |
     g''8 f''8 d''8 b'8 f''8 d''8 b'8 g'8 |
\bar "|."

  }
    \new Staff = "left" {
    \set Staff.midiInstrument = "acoustic grand"
    \key c \major
    \time 4/4

    \clef bass
    s1*0\p
    c1 \fermata |
     d1 \fermata |
     e1 \fermata |
     f1 \fermata |
     g1 \fermata |
     a1 \fermata |
     b1 \fermata |
     c'1 \fermata |
     d'1 \fermata |
     e'1 \fermata |
     f'1 \fermata |
     g'1 \fermata |
     a'1 \fermata |
     b'1 \fermata |
     c''1 \fermata |
     d''1 \fermata |
     e''1 \fermata |
     f''1 \fermata |
     g''1 \fermata |
     a''1 \fermata |
     b''1 \fermata |
     c4 d8 e8 f8 g8 a8 b8 |
     c'4 d'8 e'8 f'8 g'8 a'8 b'8 |
     c''4 d''8 e''8 f''8 g''8 a''8 b''8 |
     a''4 g''8 f''8 e''8 d''8 c''8 b'8 |
     a'4 g'8 f'8 e'8 d'8 c'8 b8 |
     a4 g8 f8 e8 d8 c8 c8 |
     c4 d8 e8 f8 g8 a8 b8 |
     c'4 d'8 e'8 f'8 g'8 a'8 b'8 |
     c''4 d''8 e''8 f''8 g''8 a''8 b''8 |
     a''4 g''8 f''8 e''8 d''8 c''8 b'8 |
     a'4 g'8 f'8 e'8 d'8 c'8 b8 |
     a4 g8 f8 e8 d8 c8 c8 |
     c8 e8 d8 f8 e8 g8 f8 a8 |
     g8 b8 a8 c'8 b8 d'8 c'8 e'8 |
     d'8 f'8 e'8 g'8 f'8 a'8 g'8 b'8 |
     a'8 c''8 b'8 d''8 c''8 e''8 d''8 f''8 |
     f''8 d''8 e''8 c''8 d''8 b'8 c''8 a'8 |
     b'8 g'8 a'8 f'8 g'8 e'8 f'8 d'8 |
     e'8 c'8 d'8 b8 c'8 a8 b8 g8 |
     a8 f8 g8 e8 f8 d8 e8 c8 |
     c8 e8 g8 c'8 e8 g8 c'8 e'8 |
     g8 c'8 e'8 g'8 c'8 e'8 g'8 c''8 |
     e'8 g'8 c''8 e''8 g'8 c''8 e''8 g''8 |
     g''8 e''8 c''8 g'8 e''8 c''8 g'8 e'8 |
     c''8 g'8 e'8 c'8 g'8 e'8 c'8 g8 |
     e'8 c'8 g8 e8 c'8 g8 e8 c8 |
     g8 b8 d'8 f'8 b8 d'8 f'8 g'8 |
     d'8 f'8 g'8 b'8 f'8 g'8 b'8 d''8 |
     g'8 b'8 d''8 f''8 b'8 d''8 f''8 g''8 |
     g''8 f''8 d''8 b'8 f''8 d''8 b'8 g'8 |
     d''8 b'8 g'8 f'8 b'8 g'8 f'8 d'8 |
     g'8 f'8 d'8 b8 f'8 d'8 b8 g8 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

