\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Scale Studies for Piano in A Minor"
  composer = "Elvex"
}
\score {
<<
    \new Staff = "right" {
    \set Staff.instrumentName = "Piano"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 72
    \key a \minor
    \time 4/4

    \clef treble
    s1*0\mp
    \set Staff.instrumentName = "Sons tenus"
    \set Staff.shortInstrumentName = "Sons tenus"
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
     c''''1 \fermata |
     d''''1 \fermata |
     e''''1 \fermata |
     f''''1 \fermata |
     g''''1 \fermata |
   \break
     \set Staff.instrumentName = "Gamme sans liaison"
    \set Staff.shortInstrumentName = "Gamme sans liaison"
     a'4 b'8 c''8 d''8 e''8 f''8 g''8 |
     a''4 b''8 c'''8 d'''8 e'''8 f'''8 g'''8 |
     a'''4 b'''8 c''''8 d''''8 e''''8 f''''8 g''''8 |
     f''''4 e''''8 d''''8 c''''8 b'''8 a'''8 g'''8 |
     f'''4 e'''8 d'''8 c'''8 b''8 a''8 g''8 |
     f''4 e''8 d''8 c''8 b'8 a'8 a'8 |
   \break
     \set Staff.instrumentName = "Gamme avec liaison"
    \set Staff.shortInstrumentName = "Gamme avec liaison"
     a'4 ( b'8 c''8 d''8 e''8 f''8 g''8 ) |
     a''4 ( b''8 c'''8 d'''8 e'''8 f'''8 g'''8 ) |
     a'''4 ( b'''8 c''''8 d''''8 e''''8 f''''8 g''''8 ) |
     f''''4 ( e''''8 d''''8 c''''8 b'''8 a'''8 g'''8 ) |
     f'''4 ( e'''8 d'''8 c'''8 b''8 a''8 g''8 ) |
     f''4 ( e''8 d''8 c''8 b'8 a'8 a'8 ) |
   \break
     \set Staff.instrumentName = "Tierces"
    \set Staff.shortInstrumentName = "Tierces"
     a'8 c''8 b'8 d''8 c''8 e''8 d''8 f''8 |
     e''8 g''8 f''8 a''8 g''8 b''8 a''8 c'''8 |
     b''8 d'''8 c'''8 e'''8 d'''8 f'''8 e'''8 g'''8 |
     f'''8 a'''8 g'''8 b'''8 a'''8 c''''8 b'''8 d''''8 |
     d''''8 b'''8 c''''8 a'''8 b'''8 g'''8 a'''8 f'''8 |
     g'''8 e'''8 f'''8 d'''8 e'''8 c'''8 d'''8 b''8 |
     c'''8 a''8 b''8 g''8 a''8 f''8 g''8 e''8 |
     f''8 d''8 e''8 c''8 d''8 b'8 c''8 a'8 |
   \break
     \set Staff.instrumentName = "Tonique"
    \set Staff.shortInstrumentName = "Tonique"
     a'8 c''8 e''8 a''8 c''8 e''8 a''8 c'''8 |
     e''8 a''8 c'''8 e'''8 a''8 c'''8 e'''8 a'''8 |
     c'''8 e'''8 a'''8 c''''8 e'''8 a'''8 c''''8 e''''8 |
     e''''8 c''''8 a'''8 e'''8 c''''8 a'''8 e'''8 c'''8 |
     a'''8 e'''8 c'''8 a''8 e'''8 c'''8 a''8 e''8 |
     c'''8 a''8 e''8 c''8 a''8 e''8 c''8 a'8 |
   \break
     \set Staff.instrumentName = "Dominante 7e"
    \set Staff.shortInstrumentName = "Dominante 7e"
     e''8 gis''8 b''8 d'''8 gis''8 b''8 d'''8 e'''8 |
     b''8 d'''8 e'''8 gis'''8 d'''8 e'''8 gis'''8 b'''8 |
     e'''8 gis'''8 b'''8 d''''8 gis'''8 b'''8 d''''8 e''''8 |
     e''''8 d''''8 b'''8 gis'''8 d''''8 b'''8 gis'''8 e'''8 |
     b'''8 gis'''8 e'''8 d'''8 gis'''8 e'''8 d'''8 b''8 |
     e'''8 d'''8 b''8 gis''8 d'''8 b''8 gis''8 e''8 |
\bar "|."

  }
    \new Staff = "left" {
    \set Staff.midiInstrument = "acoustic grand"
    \key a \minor
    \time 4/4

    \clef bass
    s1*0\p
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
     c'''1 \fermata |
     d'''1 \fermata |
     e'''1 \fermata |
     f'''1 \fermata |
     g'''1 \fermata |
     a4 b8 c'8 d'8 e'8 f'8 g'8 |
     a'4 b'8 c''8 d''8 e''8 f''8 g''8 |
     a''4 b''8 c'''8 d'''8 e'''8 f'''8 g'''8 |
     f'''4 e'''8 d'''8 c'''8 b''8 a''8 g''8 |
     f''4 e''8 d''8 c''8 b'8 a'8 g'8 |
     f'4 e'8 d'8 c'8 b8 a8 a8 |
     a4 b8 c'8 d'8 e'8 f'8 g'8 |
     a'4 b'8 c''8 d''8 e''8 f''8 g''8 |
     a''4 b''8 c'''8 d'''8 e'''8 f'''8 g'''8 |
     f'''4 e'''8 d'''8 c'''8 b''8 a''8 g''8 |
     f''4 e''8 d''8 c''8 b'8 a'8 g'8 |
     f'4 e'8 d'8 c'8 b8 a8 a8 |
     a8 c'8 b8 d'8 c'8 e'8 d'8 f'8 |
     e'8 g'8 f'8 a'8 g'8 b'8 a'8 c''8 |
     b'8 d''8 c''8 e''8 d''8 f''8 e''8 g''8 |
     f''8 a''8 g''8 b''8 a''8 c'''8 b''8 d'''8 |
     d'''8 b''8 c'''8 a''8 b''8 g''8 a''8 f''8 |
     g''8 e''8 f''8 d''8 e''8 c''8 d''8 b'8 |
     c''8 a'8 b'8 g'8 a'8 f'8 g'8 e'8 |
     f'8 d'8 e'8 c'8 d'8 b8 c'8 a8 |
     a8 c'8 e'8 a'8 c'8 e'8 a'8 c''8 |
     e'8 a'8 c''8 e''8 a'8 c''8 e''8 a''8 |
     c''8 e''8 a''8 c'''8 e''8 a''8 c'''8 e'''8 |
     e'''8 c'''8 a''8 e''8 c'''8 a''8 e''8 c''8 |
     a''8 e''8 c''8 a'8 e''8 c''8 a'8 e'8 |
     c''8 a'8 e'8 c'8 a'8 e'8 c'8 a8 |
     e'8 gis'8 b'8 d''8 gis'8 b'8 d''8 e''8 |
     b'8 d''8 e''8 gis''8 d''8 e''8 gis''8 b''8 |
     e''8 gis''8 b''8 d'''8 gis''8 b''8 d'''8 e'''8 |
     e'''8 d'''8 b''8 gis''8 d'''8 b''8 gis''8 e''8 |
     b''8 gis''8 e''8 d''8 gis''8 e''8 d''8 b'8 |
     e''8 d''8 b'8 gis'8 d''8 b'8 gis'8 e'8 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

