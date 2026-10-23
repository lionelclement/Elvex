\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Chanson française - grande arche"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Voix"
    \set Staff.midiInstrument = "voice oohs"
    \tempo 4 = 96
    \key c \major
    \time 4/4

    \clef treble
    s1*0\mf
    r1 |
     c'8 dis'8 g'4 c''8 d''8 dis''4 |
     dis''4 f''8 g''8 ais''2 |
     c''1 |
    c'8 dis'8 g'4 c''8 d''8 dis''4 |
     dis''4 f''8 g''8 ais''2 |
     ais''2. g''4 |
     g''2 r4 f''8 dis''8 |
     ais''8 g''8 f''4 dis''8 c''8 ais'4 |
     f''4 dis''8 c''8 g'2 |
     g'4 ais'8 gis'8 g'2 |
     dis''2 c''2 |
     dis'8 g'8 ais'4 dis''8 g''8 ais''4 |
     c''4 dis''8 g''8 c'''2 |
     c'''2. ais''4 |
     g''2 r4 f''8 dis''8 |
     g''4 f''4 dis''4 c''4 |
     d''4 f''8 g''8 b''2 |
     g''2 c''2 |
     c''1 |
    c''8 dis''8 g''8 ais''8 c'''8 ais''8 g''8 dis''8 |
     c'''2. ais''4 |
     g''8 f''8 dis''4 c''8 ais'8 g'4 |
     g''2 r4 f''8 dis''8 |
     dis''8 f''8 g''8 ais''8 c'''8 ais''8 g''8 f''8 |
     dis'''2. c'''4 |
     ais''4 g''8 f''8 dis''2 |
     dis''2 c''2 |
     c''8 dis''8 g''8 ais''8 c'''8 ais''8 g''8 dis''8 |
     c'''2. ais''4 |
     ais''8 g''8 f''4 dis''8 c''8 ais'4 |
     g''2 r4 f''8 dis''8 |
     f''8 g''8 ais''4 c'''2 |
     d''4 f''8 g''8 b''2 |
     c'''2 g''2 |
     c'''1 |
    dis'8 g'8 ais'4 dis''8 g''8 ais''4 |
     c''4 dis''8 g''8 c'''2 |
     ais''2. g''4 |
     g''2 r4 f''8 dis''8 |
     f''4 dis''8 c''8 g'2 |
     g''4 f''4 dis''4 c''4 |
     g'4 ais'8 gis'8 g'2 |
     dis''2 c''2 |
     c'8 dis'8 g'4 c''8 d''8 dis''4 |
     dis''4 f''8 g''8 ais''2 |
     c'''2. ais''4 |
     g''2 r4 f''8 dis''8 |
     ais''8 g''8 f''4 dis''8 c''8 ais'4 |
     d''4 f''8 g''8 b''2 |
     g''2 c''2 |
     c''1 |
    c''8 dis''8 g''8 ais''8 c'''8 ais''8 g''8 dis''8 |
     c'''2. ais''4 |
     g''8 f''8 dis''4 c''8 ais'8 g'4 |
     g''2 r4 f''8 dis''8 |
     dis''8 f''8 g''8 ais''8 c'''8 ais''8 g''8 f''8 |
     dis'''2. c'''4 |
     ais''4 g''8 f''8 dis''2 |
     dis''2 c''2 |
     c''8 dis''8 g''8 ais''8 c'''8 ais''8 g''8 dis''8 |
     c'''2. ais''4 |
     ais''8 g''8 f''4 dis''8 c''8 ais'4 |
     g''2 r4 f''8 dis''8 |
     f''8 g''8 ais''4 c'''2 |
     d''4 f''8 g''8 b''2 |
     c'''2 g''2 |
     c'''1 |
    g''4 f''4 dis''4 c''4 |
     d''4 f''8 g''8 b''2 |
     g''2 c''2 |
     c'''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitare"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 96
    \key c \major
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    c4 g4 c'4 dis'4 |
     g4 d'4 g'4 b'4 |
     c4 g4 c'4 dis'4 |
     g4 d'4 g'4 b'4 |
    <c dis g>4 <c dis g>4 <c dis g>4 <c dis g>4 |
     <g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
     <c dis g>4 <c dis g>4 <c dis g>4 <c dis g>4 |
     <f gis c'>4 <f gis c'>4 <f gis c'>4 <f gis c'>4 |
     <ais d' f'>4 <ais d' f'>4 <ais d' f'>4 <ais d' f'>4 |
     <dis g ais>4 <dis g ais>4 <dis g ais>4 <dis g ais>4 |
     <gis c' dis'>4 <gis c' dis'>4 <gis c' dis'>4 <gis c' dis'>4 |
     <g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
     c4 g4 c'4 dis'4 |
     g4 d'4 g'4 b'4 |
     c4 g4 c'4 dis'4 |
     f4 c'4 f'4 gis'4 |
     <gis c' dis'>4 <gis c' dis'>4 <gis c' dis'>4 <gis c' dis'>4 |
     <g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
     c4 g4 c'4 dis'4 |
     <c dis g>1 |
    dis4 ais4 dis'4 g'4 |
     ais4 d'4 f'4 ais'4 |
     c4 g4 c'4 dis'4 |
     g4 d'4 g'4 b'4 |
     gis4 dis'4 gis'4 c''4 |
     dis4 ais4 dis'4 g'4 |
     f4 c'4 f'4 gis'4 |
     g4 d'4 g'4 b'4 |
     <dis g ais>2 <ais d' f'>2 |
     <c dis g>2 <g b d'>2 |
     <f gis c'>2 <dis g ais>2 |
     <f gis c'>2 <g b d'>2 |
     gis4 dis'4 gis'4 c''4 |
     g4 d'4 g'4 b'4 |
     c4 g4 c'4 dis'4 |
     <c dis g>1 |
    <c dis g>4 <c dis g>4 <c dis g>4 <c dis g>4 |
     <g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
     <c dis g>4 <c dis g>4 <c dis g>4 <c dis g>4 |
     <f gis c'>4 <f gis c'>4 <f gis c'>4 <f gis c'>4 |
     <ais d' f'>4 <ais d' f'>4 <ais d' f'>4 <ais d' f'>4 |
     <dis g ais>4 <dis g ais>4 <dis g ais>4 <dis g ais>4 |
     <gis c' dis'>4 <gis c' dis'>4 <gis c' dis'>4 <gis c' dis'>4 |
     <g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
     c4 g4 c'4 dis'4 |
     g4 d'4 g'4 b'4 |
     c4 g4 c'4 dis'4 |
     f4 c'4 f'4 gis'4 |
     <gis c' dis'>4 <gis c' dis'>4 <gis c' dis'>4 <gis c' dis'>4 |
     <g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
     c4 g4 c'4 dis'4 |
     <c dis g>1 |
    dis4 ais4 dis'4 g'4 |
     ais4 d'4 f'4 ais'4 |
     c4 g4 c'4 dis'4 |
     g4 d'4 g'4 b'4 |
     gis4 dis'4 gis'4 c''4 |
     dis4 ais4 dis'4 g'4 |
     f4 c'4 f'4 gis'4 |
     g4 d'4 g'4 b'4 |
     <dis g ais>2 <ais d' f'>2 |
     <c dis g>2 <g b d'>2 |
     <f gis c'>2 <dis g ais>2 |
     <f gis c'>2 <g b d'>2 |
     gis4 dis'4 gis'4 c''4 |
     g4 d'4 g'4 b'4 |
     c4 g4 c'4 dis'4 |
     <c dis g>1 |
    f4 c'4 f'4 gis'4 |
     c4 g4 c'4 dis'4 |
     g4 d'4 g'4 b'4 |
     <c dis g>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

