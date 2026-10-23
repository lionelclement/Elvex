\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Scale Studies for Solo Flute"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 72
    \key c \minor
    \time 4/4

    \clef treble
    s1*0\mf
    \set Staff.instrumentName = "Sons tenus"
    \set Staff.shortInstrumentName = "Sons tenus"
     c'1 \fermata |
     d'1 \fermata |
     ees'1 \fermata |
     f'1 \fermata |
     g'1 \fermata |
     aes'1 \fermata |
     bes'1 \fermata |
     c''1 \fermata |
     d''1 \fermata |
     ees''1 \fermata |
     f''1 \fermata |
     g''1 \fermata |
     aes''1 \fermata |
     bes''1 \fermata |
     c'''1 \fermata |
     d'''1 \fermata |
     ees'''1 \fermata |
     f'''1 \fermata |
     g'''1 \fermata |
     aes'''1 \fermata |
     bes'''1 \fermata |
   \break
     \set Staff.instrumentName = "Gamme sans liaison"
    \set Staff.shortInstrumentName = "Gamme sans liaison"
     c'4 d'8 ees'8 f'8 g'8 aes'8 bes'8 |
   \breathe
     c''4 d''8 ees''8 f''8 g''8 aes''8 bes''8 |
   \breathe
     c'''4 d'''8 ees'''8 f'''8 g'''8 aes'''8 bes'''8 |
   \breathe
     aes'''4 g'''8 f'''8 ees'''8 d'''8 c'''8 bes''8 |
   \breathe
     aes''4 g''8 f''8 ees''8 d''8 c''8 bes'8 |
   \breathe
     aes'4 g'8 f'8 ees'8 d'8 c'8 c'8 |
   \break
     \set Staff.instrumentName = "Gamme avec liaison"
    \set Staff.shortInstrumentName = "Gamme avec liaison"
     c'4 ( d'8 ees'8 f'8 g'8 aes'8 bes'8 ) |
   \breathe
     c''4 ( d''8 ees''8 f''8 g''8 aes''8 bes''8 ) |
   \breathe
     c'''4 ( d'''8 ees'''8 f'''8 g'''8 aes'''8 bes'''8 ) |
   \breathe
     aes'''4 ( g'''8 f'''8 ees'''8 d'''8 c'''8 bes''8 ) |
   \breathe
     aes''4 ( g''8 f''8 ees''8 d''8 c''8 bes'8 ) |
   \breathe
     aes'4 ( g'8 f'8 ees'8 d'8 c'8 c'8 ) |
   \break
     \set Staff.instrumentName = "Tierces"
    \set Staff.shortInstrumentName = "Tierces"
     c'8 ees'8 d'8 f'8 ees'8 g'8 f'8 aes'8 |
   \breathe
     g'8 bes'8 aes'8 c''8 bes'8 d''8 c''8 ees''8 |
   \breathe
     d''8 f''8 ees''8 g''8 f''8 aes''8 g''8 bes''8 |
   \breathe
     aes''8 c'''8 bes''8 d'''8 c'''8 ees'''8 d'''8 f'''8 |
   \breathe
     f'''8 d'''8 ees'''8 c'''8 d'''8 bes''8 c'''8 aes''8 |
   \breathe
     bes''8 g''8 aes''8 f''8 g''8 ees''8 f''8 d''8 |
   \breathe
     ees''8 c''8 d''8 bes'8 c''8 aes'8 bes'8 g'8 |
   \breathe
     aes'8 f'8 g'8 ees'8 f'8 d'8 ees'8 c'8 |
   \break
     \set Staff.instrumentName = "Tonique"
    \set Staff.shortInstrumentName = "Tonique"
     c'8 ees'8 g'8 c''8 ees'8 g'8 c''8 ees''8 |
   \breathe
     g'8 c''8 ees''8 g''8 c''8 ees''8 g''8 c'''8 |
   \breathe
     ees''8 g''8 c'''8 ees'''8 g''8 c'''8 ees'''8 g'''8 |
   \breathe
     g'''8 ees'''8 c'''8 g''8 ees'''8 c'''8 g''8 ees''8 |
   \breathe
     c'''8 g''8 ees''8 c''8 g''8 ees''8 c''8 g'8 |
   \breathe
     ees''8 c''8 g'8 ees'8 c''8 g'8 ees'8 c'8 |
   \break
     \set Staff.instrumentName = "Dominante 7e"
    \set Staff.shortInstrumentName = "Dominante 7e"
     g'8 b'8 d''8 f''8 b'8 d''8 f''8 g''8 |
   \breathe
     d''8 f''8 g''8 b''8 f''8 g''8 b''8 d'''8 |
   \breathe
     g''8 b''8 d'''8 f'''8 b''8 d'''8 f'''8 g'''8 |
   \breathe
     g'''8 f'''8 d'''8 b''8 f'''8 d'''8 b''8 g''8 |
   \breathe
     d'''8 b''8 g''8 f''8 b''8 g''8 f''8 d''8 |
   \breathe
     g''8 f''8 d''8 b'8 f''8 d''8 b'8 g'8 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

