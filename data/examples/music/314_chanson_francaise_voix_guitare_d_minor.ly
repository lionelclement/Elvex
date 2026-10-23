\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Chanson française sombre en ré mineur"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Voix"
    \set Staff.midiInstrument = "voice oohs"
    \tempo 4 = 84
    \key d \minor
    \time 4/4

    \clef treble
    s1*0\mf
    r1 |
     a'2 d''2 |
     e''4 d''4 c''4 a'4 |
     a'1 |
    a'4 d''8 e''8 d''2 |
     des''4 r4 a'4 a'4 |
     a'4 d''8 f''8 e''2 |
     d''2 r4 d''8 e''8 |
     g''4 f''8 e''8 d''2 |
     c''4 a'8 c''8 c''2 |
     d''4 f''8 e''8 d''2 |
     des''2 a'2 |
     a'4 d''8 e''8 d''2 |
     des''4 r4 a'4 a'4 |
     a'4 d''8 f''8 e''2 |
     d''2 r4 d''8 e''8 |
     f''4 e''8 d''8 bes'2 |
     a'4 des''8 e''8 des''2 |
     d''2 a'2 |
     d''1 |
    f''4 f''8 e''8 d''2 |
     e''4 r4 c''4 a'4 |
     d''4 f''8 g''8 a''2 |
     e''2 r4 e''8 f''8 |
     g''4 f''8 e''8 d''2 |
     a'4 c''8 d''8 e''2 |
     d''4 bes'8 d''8 g''2 |
     des''2 a'2 |
     f''4 f''8 e''8 d''2 |
     e''4 r4 c''4 a'4 |
     d''4 f''8 g''8 a''2 |
     e''2 r4 e''8 f''8 |
     g''4 f''8 e''8 d''2 |
     a'4 des''8 e''8 des''2 |
     d''2 a'2 |
     d''1 |
    d''4 r4 d''4 e''4 |
     des''2 a'2 |
     a'4 d''8 f''8 e''2 |
     d''2 r4 d''8 e''8 |
     g''4 f''8 e''8 d''2 |
     c''4 a'8 c''8 c''2 |
     d''4 f''8 e''8 d''2 |
     des''2 a'2 |
     a'4 d''8 e''8 d''2 |
     des''4 r4 a'4 a'4 |
     d''4 r4 f''4 e''4 |
     d''2 r4 d''8 e''8 |
     f''4 e''8 d''8 bes'2 |
     a'4 des''8 e''8 des''2 |
     d''2 a'2 |
     d''1 |
    f''4 f''8 e''8 d''2 |
     e''4 r4 c''4 a'4 |
     d''4 f''8 g''8 a''2 |
     e''2 r4 e''8 f''8 |
     g''4 f''8 e''8 d''2 |
     a'4 c''8 d''8 e''2 |
     d''4 bes'8 d''8 g''2 |
     des''2 a'2 |
     f''4 f''8 e''8 d''2 |
     e''4 r4 c''4 a'4 |
     d''4 f''8 g''8 a''2 |
     e''2 r4 e''8 f''8 |
     g''4 f''8 e''8 d''2 |
     a'4 des''8 e''8 des''2 |
     d''2 a'2 |
     f''2 d''2 |
    d''4 bes'8 d''8 g''2 |
     d''2 a'2 |
     a'4 des''8 e''8 des''2 |
     d''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitare"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 84
    \key d \minor
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    d4 a4 d'4 f'4 |
     a4 e'4 a'4 des''4 |
     d4 a4 d'4 f'4 |
     a4 e'4 a'4 des''4 |
    <d f a>4 <d f a>4 <d f a>4 <d f a>4 |
     <a des' e'>4 <a des' e'>4 <a des' e'>4 <a des' e'>4 |
     <d f a>4 <d f a>4 <d f a>4 <d f a>4 |
     <g bes d'>4 <g bes d'>4 <g bes d'>4 <g bes d'>4 |
     <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 |
     <f a c'>4 <f a c'>4 <f a c'>4 <f a c'>4 |
     <bes d' f'>4 <bes d' f'>4 <bes d' f'>4 <bes d' f'>4 |
     <a des' e'>4 <a des' e'>4 <a des' e'>4 <a des' e'>4 |
     d4 a4 d'4 f'4 |
     a4 e'4 a'4 des''4 |
     d4 a4 d'4 f'4 |
     g4 d'4 g'4 bes'4 |
     <bes d' f'>4 <bes d' f'>4 <bes d' f'>4 <bes d' f'>4 |
     <a des' e'>4 <a des' e'>4 <a des' e'>4 <a des' e'>4 |
     d4 a4 d'4 f'4 |
     <d f a>1 |
    f4 c'4 f'4 a'4 |
     c'4 e'4 g'4 c''4 |
     d4 a4 d'4 f'4 |
     a4 e'4 a'4 des''4 |
     bes4 f'4 bes'4 d''4 |
     f4 c'4 f'4 a'4 |
     g4 d'4 g'4 bes'4 |
     a4 e'4 a'4 des''4 |
     <f a c'>2 <c' e' g'>2 |
     <d f a>2 <a des' e'>2 |
     <g bes d'>2 <f a c'>2 |
     <g bes d'>2 <a des' e'>2 |
     bes4 f'4 bes'4 d''4 |
     a4 e'4 a'4 des''4 |
     d4 a4 d'4 f'4 |
     <d f a>1 |
    <d f a>4 <d f a>4 <d f a>4 <d f a>4 |
     <a des' e'>4 <a des' e'>4 <a des' e'>4 <a des' e'>4 |
     <d f a>4 <d f a>4 <d f a>4 <d f a>4 |
     <g bes d'>4 <g bes d'>4 <g bes d'>4 <g bes d'>4 |
     <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 |
     <f a c'>4 <f a c'>4 <f a c'>4 <f a c'>4 |
     <bes d' f'>4 <bes d' f'>4 <bes d' f'>4 <bes d' f'>4 |
     <a des' e'>4 <a des' e'>4 <a des' e'>4 <a des' e'>4 |
     d4 a4 d'4 f'4 |
     a4 e'4 a'4 des''4 |
     d4 a4 d'4 f'4 |
     g4 d'4 g'4 bes'4 |
     <bes d' f'>4 <bes d' f'>4 <bes d' f'>4 <bes d' f'>4 |
     <a des' e'>4 <a des' e'>4 <a des' e'>4 <a des' e'>4 |
     d4 a4 d'4 f'4 |
     <d f a>1 |
    f4 c'4 f'4 a'4 |
     c'4 e'4 g'4 c''4 |
     d4 a4 d'4 f'4 |
     a4 e'4 a'4 des''4 |
     bes4 f'4 bes'4 d''4 |
     f4 c'4 f'4 a'4 |
     g4 d'4 g'4 bes'4 |
     a4 e'4 a'4 des''4 |
     <f a c'>2 <c' e' g'>2 |
     <d f a>2 <a des' e'>2 |
     <g bes d'>2 <f a c'>2 |
     <g bes d'>2 <a des' e'>2 |
     bes4 f'4 bes'4 d''4 |
     a4 e'4 a'4 des''4 |
     d4 a4 d'4 f'4 |
     <d f a>1 |
    g4 d'4 g'4 bes'4 |
     d4 a4 d'4 f'4 |
     a4 e'4 a'4 des''4 |
     <d f a>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

