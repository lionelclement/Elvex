\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Chanson française lumineuse en sol"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Voix"
    \set Staff.midiInstrument = "voice oohs"
    \tempo 4 = 104
    \key g \major
    \time 4/4

    \clef treble
    s1*0\mf
    r1 |
     d''2 g''2 |
     a''4 g''4 f''4 d''4 |
     d''1 |
    d''4 g''8 a''8 g''2 |
     fis''4 r4 d''4 d''4 |
     d''4 g''8 ais''8 a''2 |
     g''2 r4 g''8 a''8 |
     c'''4 ais''8 a''8 g''2 |
     f''4 d''8 f''8 f''2 |
     g''4 ais''8 a''8 g''2 |
     fis''2 d''2 |
     d''4 g''8 a''8 g''2 |
     fis''4 r4 d''4 d''4 |
     d''4 g''8 ais''8 a''2 |
     g''2 r4 g''8 a''8 |
     ais''4 a''8 g''8 dis''2 |
     d''4 fis''8 a''8 fis''2 |
     g''2 d''2 |
     g''1 |
    ais''4 ais''8 a''8 g''2 |
     a''4 r4 f''4 d''4 |
     g''4 ais''8 c'''8 d'''2 |
     a''2 r4 a''8 ais''8 |
     c'''4 ais''8 a''8 g''2 |
     d''4 f''8 g''8 a''2 |
     g''4 dis''8 g''8 c'''2 |
     fis''2 d''2 |
     ais''4 ais''8 a''8 g''2 |
     a''4 r4 f''4 d''4 |
     g''4 ais''8 c'''8 d'''2 |
     a''2 r4 a''8 ais''8 |
     c'''4 ais''8 a''8 g''2 |
     d''4 fis''8 a''8 fis''2 |
     g''2 d''2 |
     g''1 |
    g''4 r4 g''4 a''4 |
     fis''2 d''2 |
     d''4 g''8 ais''8 a''2 |
     g''2 r4 g''8 a''8 |
     c'''4 ais''8 a''8 g''2 |
     f''4 d''8 f''8 f''2 |
     g''4 ais''8 a''8 g''2 |
     fis''2 d''2 |
     d''4 g''8 a''8 g''2 |
     fis''4 r4 d''4 d''4 |
     g''4 r4 ais''4 a''4 |
     g''2 r4 g''8 a''8 |
     ais''4 a''8 g''8 dis''2 |
     d''4 fis''8 a''8 fis''2 |
     g''2 d''2 |
     g''1 |
    ais''4 ais''8 a''8 g''2 |
     a''4 r4 f''4 d''4 |
     g''4 ais''8 c'''8 d'''2 |
     a''2 r4 a''8 ais''8 |
     c'''4 ais''8 a''8 g''2 |
     d''4 f''8 g''8 a''2 |
     g''4 dis''8 g''8 c'''2 |
     fis''2 d''2 |
     ais''4 ais''8 a''8 g''2 |
     a''4 r4 f''4 d''4 |
     g''4 ais''8 c'''8 d'''2 |
     a''2 r4 a''8 ais''8 |
     c'''4 ais''8 a''8 g''2 |
     d''4 fis''8 a''8 fis''2 |
     g''2 d''2 |
     ais''2 g''2 |
    g''4 dis''8 g''8 c'''2 |
     g''2 d''2 |
     d''4 fis''8 a''8 fis''2 |
     g''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitare"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 104
    \key g \major
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    g4 d'4 g'4 ais'4 |
     d'4 a'4 d''4 fis''4 |
     g4 d'4 g'4 ais'4 |
     d'4 a'4 d''4 fis''4 |
    <g ais d'>4 <g ais d'>4 <g ais d'>4 <g ais d'>4 |
     <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 |
     <g ais d'>4 <g ais d'>4 <g ais d'>4 <g ais d'>4 |
     <c' dis' g'>4 <c' dis' g'>4 <c' dis' g'>4 <c' dis' g'>4 |
     <f' a' c''>4 <f' a' c''>4 <f' a' c''>4 <f' a' c''>4 |
     <ais d' f'>4 <ais d' f'>4 <ais d' f'>4 <ais d' f'>4 |
     <dis' g' ais'>4 <dis' g' ais'>4 <dis' g' ais'>4 <dis' g' ais'>4 |
     <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 |
     g4 d'4 g'4 ais'4 |
     d'4 a'4 d''4 fis''4 |
     g4 d'4 g'4 ais'4 |
     c'4 g'4 c''4 dis''4 |
     <dis' g' ais'>4 <dis' g' ais'>4 <dis' g' ais'>4 <dis' g' ais'>4 |
     <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 |
     g4 d'4 g'4 ais'4 |
     <g ais d'>1 |
    ais4 f'4 ais'4 d''4 |
     f'4 a'4 c''4 f''4 |
     g4 d'4 g'4 ais'4 |
     d'4 a'4 d''4 fis''4 |
     dis'4 ais'4 dis''4 g''4 |
     ais4 f'4 ais'4 d''4 |
     c'4 g'4 c''4 dis''4 |
     d'4 a'4 d''4 fis''4 |
     <ais d' f'>2 <f' a' c''>2 |
     <g ais d'>2 <d' fis' a'>2 |
     <c' dis' g'>2 <ais d' f'>2 |
     <c' dis' g'>2 <d' fis' a'>2 |
     dis'4 ais'4 dis''4 g''4 |
     d'4 a'4 d''4 fis''4 |
     g4 d'4 g'4 ais'4 |
     <g ais d'>1 |
    <g ais d'>4 <g ais d'>4 <g ais d'>4 <g ais d'>4 |
     <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 |
     <g ais d'>4 <g ais d'>4 <g ais d'>4 <g ais d'>4 |
     <c' dis' g'>4 <c' dis' g'>4 <c' dis' g'>4 <c' dis' g'>4 |
     <f' a' c''>4 <f' a' c''>4 <f' a' c''>4 <f' a' c''>4 |
     <ais d' f'>4 <ais d' f'>4 <ais d' f'>4 <ais d' f'>4 |
     <dis' g' ais'>4 <dis' g' ais'>4 <dis' g' ais'>4 <dis' g' ais'>4 |
     <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 |
     g4 d'4 g'4 ais'4 |
     d'4 a'4 d''4 fis''4 |
     g4 d'4 g'4 ais'4 |
     c'4 g'4 c''4 dis''4 |
     <dis' g' ais'>4 <dis' g' ais'>4 <dis' g' ais'>4 <dis' g' ais'>4 |
     <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 |
     g4 d'4 g'4 ais'4 |
     <g ais d'>1 |
    ais4 f'4 ais'4 d''4 |
     f'4 a'4 c''4 f''4 |
     g4 d'4 g'4 ais'4 |
     d'4 a'4 d''4 fis''4 |
     dis'4 ais'4 dis''4 g''4 |
     ais4 f'4 ais'4 d''4 |
     c'4 g'4 c''4 dis''4 |
     d'4 a'4 d''4 fis''4 |
     <ais d' f'>2 <f' a' c''>2 |
     <g ais d'>2 <d' fis' a'>2 |
     <c' dis' g'>2 <ais d' f'>2 |
     <c' dis' g'>2 <d' fis' a'>2 |
     dis'4 ais'4 dis''4 g''4 |
     d'4 a'4 d''4 fis''4 |
     g4 d'4 g'4 ais'4 |
     <g ais d'>1 |
    c'4 g'4 c''4 dis''4 |
     g4 d'4 g'4 ais'4 |
     d'4 a'4 d''4 fis''4 |
     <g ais d'>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

