\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Scale Studies for Solo Flute in G"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 72
    \key g \major
    \time 4/4

    \clef treble
    s1*0\mf
    \set Staff.instrumentName = "Sons tenus"
    \set Staff.shortInstrumentName = "Sons tenus"
     g'1 \fermata |
     a'1 \fermata |
     b'1 \fermata |
     c''1 \fermata |
     d''1 \fermata |
     e''1 \fermata |
     fis''1 \fermata |
     g''1 \fermata |
     a''1 \fermata |
     b''1 \fermata |
     c'''1 \fermata |
     d'''1 \fermata |
     e'''1 \fermata |
     fis'''1 \fermata |
     g'''1 \fermata |
     a'''1 \fermata |
     b'''1 \fermata |
     c''''1 \fermata |
     d''''1 \fermata |
     e''''1 \fermata |
     fis''''1 \fermata |
   \break
     \set Staff.instrumentName = "Gamme sans liaison"
    \set Staff.shortInstrumentName = "Gamme sans liaison"
     g'4 a'8 b'8 c''8 d''8 e''8 fis''8 |
   \breathe
     g''4 a''8 b''8 c'''8 d'''8 e'''8 fis'''8 |
   \breathe
     g'''4 a'''8 b'''8 c''''8 d''''8 e''''8 fis''''8 |
   \breathe
     e''''4 d''''8 c''''8 b'''8 a'''8 g'''8 fis'''8 |
   \breathe
     e'''4 d'''8 c'''8 b''8 a''8 g''8 fis''8 |
   \breathe
     e''4 d''8 c''8 b'8 a'8 g'8 g'8 |
   \break
     \set Staff.instrumentName = "Gamme avec liaison"
    \set Staff.shortInstrumentName = "Gamme avec liaison"
     g'4 ( a'8 b'8 c''8 d''8 e''8 fis''8 ) |
   \breathe
     g''4 ( a''8 b''8 c'''8 d'''8 e'''8 fis'''8 ) |
   \breathe
     g'''4 ( a'''8 b'''8 c''''8 d''''8 e''''8 fis''''8 ) |
   \breathe
     e''''4 ( d''''8 c''''8 b'''8 a'''8 g'''8 fis'''8 ) |
   \breathe
     e'''4 ( d'''8 c'''8 b''8 a''8 g''8 fis''8 ) |
   \breathe
     e''4 ( d''8 c''8 b'8 a'8 g'8 g'8 ) |
   \break
     \set Staff.instrumentName = "Tierces"
    \set Staff.shortInstrumentName = "Tierces"
     g'8 b'8 a'8 c''8 b'8 d''8 c''8 e''8 |
   \breathe
     d''8 fis''8 e''8 g''8 fis''8 a''8 g''8 b''8 |
   \breathe
     a''8 c'''8 b''8 d'''8 c'''8 e'''8 d'''8 fis'''8 |
   \breathe
     e'''8 g'''8 fis'''8 a'''8 g'''8 b'''8 a'''8 c''''8 |
   \breathe
     c''''8 a'''8 b'''8 g'''8 a'''8 fis'''8 g'''8 e'''8 |
   \breathe
     fis'''8 d'''8 e'''8 c'''8 d'''8 b''8 c'''8 a''8 |
   \breathe
     b''8 g''8 a''8 fis''8 g''8 e''8 fis''8 d''8 |
   \breathe
     e''8 c''8 d''8 b'8 c''8 a'8 b'8 g'8 |
   \break
     \set Staff.instrumentName = "Tonique"
    \set Staff.shortInstrumentName = "Tonique"
     g'8 b'8 d''8 g''8 b'8 d''8 g''8 b''8 |
   \breathe
     d''8 g''8 b''8 d'''8 g''8 b''8 d'''8 g'''8 |
   \breathe
     b''8 d'''8 g'''8 b'''8 d'''8 g'''8 b'''8 d''''8 |
   \breathe
     d''''8 b'''8 g'''8 d'''8 b'''8 g'''8 d'''8 b''8 |
   \breathe
     g'''8 d'''8 b''8 g''8 d'''8 b''8 g''8 d''8 |
   \breathe
     b''8 g''8 d''8 b'8 g''8 d''8 b'8 g'8 |
   \break
     \set Staff.instrumentName = "Dominante 7e"
    \set Staff.shortInstrumentName = "Dominante 7e"
     d''8 fis''8 a''8 c'''8 fis''8 a''8 c'''8 d'''8 |
   \breathe
     a''8 c'''8 d'''8 fis'''8 c'''8 d'''8 fis'''8 a'''8 |
   \breathe
     d'''8 fis'''8 a'''8 c''''8 fis'''8 a'''8 c''''8 d''''8 |
   \breathe
     d''''8 c''''8 a'''8 fis'''8 c''''8 a'''8 fis'''8 d'''8 |
   \breathe
     a'''8 fis'''8 d'''8 c'''8 fis'''8 d'''8 c'''8 a''8 |
   \breathe
     d'''8 c'''8 a''8 fis''8 c'''8 a''8 fis''8 d''8 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

