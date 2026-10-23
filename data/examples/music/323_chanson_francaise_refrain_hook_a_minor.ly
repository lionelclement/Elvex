\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Chanson française à refrain"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Voix"
    \set Staff.midiInstrument = "voice oohs"
    \tempo 4 = 100
    \key a \minor
    \time 4/4

    \clef treble
    s1*0\mf
    r1 |
     a''4 a''8 c'''8 b''2 |
     g''4 e''8 g''8 a''2 |
     a''1 |
    e''4 g''8 a''8 g''2 |
     g''4 a''8 g''8 e''2 |
     a''4 c'''8 b''8 a''2 |
     a''2 r4 g''8 e''8 |
     c'''4 b''8 a''8 g''2 |
     f''4 g''8 a''8 g''2 |
     a''4 g''8 f''8 e''2 |
     gis''2 e''2 |
     e''4 a''8 b''8 a''2 |
     g''4 a''8 g''8 e''2 |
     a''4 b''8 c'''8 d'''2 |
     b''2 r4 a''8 g''8 |
     d'''4 c'''8 a''8 e''2 |
     e''4 gis''8 b''8 cis'''2 |
     a''2 e''2 |
     a''1 |
    a''4 a''8 c'''8 b''2 |
     g''4 e''8 g''8 a''2 |
     c'''4 c'''8 e'''8 d'''2 |
     a''2 r4 g''8 e''8 |
     a''4 a''8 c'''8 b''2 |
     cis'''4 b''8 a''8 g''2 |
     a''4 b''8 cis'''8 e'''2 |
     b''2 gis''2 |
     a''4 a''8 c'''8 b''2 |
     g''4 e''8 g''8 a''2 |
     d'''4 d'''8 fis'''8 e'''2 |
     b''2 r4 a''8 g''8 |
     b''4 cis'''8 e'''8 fis'''2 |
     e''4 gis''8 b''8 cis'''2 |
     cis'''2 a''2 |
     a''1 |
    e''4 a''8 b''8 a''2 |
     a''4 b''8 a''8 g''2 |
     a''4 c'''8 b''8 a''2 |
     a''2 r4 g''8 e''8 |
     b''4 c'''8 d'''8 c'''2 |
     f''4 g''8 a''8 g''2 |
     b''4 a''8 g''8 f''2 |
     gis''2 e''2 |
     e''4 g''8 a''8 g''2 |
     g''4 a''8 g''8 e''2 |
     a''4 b''8 c'''8 d'''2 |
     b''2 r4 a''8 g''8 |
     d'''4 c'''8 a''8 e''2 |
     e''4 gis''8 b''8 cis'''2 |
     a''2 e''2 |
     a''1 |
    a''4 a''8 c'''8 b''2 |
     g''4 e''8 g''8 a''2 |
     c'''4 c'''8 e'''8 d'''2 |
     a''2 r4 g''8 e''8 |
     a''4 a''8 c'''8 b''2 |
     cis'''4 b''8 a''8 g''2 |
     a''4 b''8 cis'''8 e'''2 |
     b''2 gis''2 |
     a''4 a''8 c'''8 b''2 |
     g''4 e''8 g''8 a''2 |
     d'''4 d'''8 fis'''8 e'''2 |
     b''2 r4 a''8 g''8 |
     b''4 cis'''8 e'''8 fis'''2 |
     e''4 gis''8 b''8 cis'''2 |
     cis'''2 a''2 |
     cis'''2 e'''2 |
    a''4 a''8 c'''8 b''2 |
     a''2 e''2 |
     g''4 e''8 g''8 a''2 |
     a''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitare"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 100
    \key a \minor
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    a4 e'4 a'4 c''4 |
     e'4 b'4 e''4 gis''4 |
     a4 e'4 a'4 c''4 |
     e'4 b'4 e''4 gis''4 |
    <a c' e'>4 <a c' e'>4 <a c' e'>4 <a c' e'>4 |
     <e' gis' b'>4 <e' gis' b'>4 <e' gis' b'>4 <e' gis' b'>4 |
     <a c' e'>4 <a c' e'>4 <a c' e'>4 <a c' e'>4 |
     <d' f' a'>4 <d' f' a'>4 <d' f' a'>4 <d' f' a'>4 |
     <g' b' d''>4 <g' b' d''>4 <g' b' d''>4 <g' b' d''>4 |
     <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 |
     <f' a' c''>4 <f' a' c''>4 <f' a' c''>4 <f' a' c''>4 |
     <e' gis' b'>4 <e' gis' b'>4 <e' gis' b'>4 <e' gis' b'>4 |
     a4 e'4 a'4 c''4 |
     e'4 b'4 e''4 gis''4 |
     a4 e'4 a'4 c''4 |
     d'4 a'4 d''4 f''4 |
     <f' a' c''>4 <f' a' c''>4 <f' a' c''>4 <f' a' c''>4 |
     <e' gis' b'>4 <e' gis' b'>4 <e' gis' b'>4 <e' gis' b'>4 |
     a4 e'4 a'4 c''4 |
     <a c' e'>1 |
    c'4 g'4 c''4 e''4 |
     g'4 b'4 d''4 g''4 |
     a4 e'4 a'4 c''4 |
     e'4 b'4 e''4 gis''4 |
     f'4 c''4 f''4 a''4 |
     c'4 g'4 c''4 e''4 |
     d'4 a'4 d''4 f''4 |
     e'4 b'4 e''4 gis''4 |
     <c' e' g'>2 <g' b' d''>2 |
     <a c' e'>2 <e' gis' b'>2 |
     <d' f' a'>2 <c' e' g'>2 |
     <d' f' a'>2 <e' gis' b'>2 |
     f'4 c''4 f''4 a''4 |
     e'4 b'4 e''4 gis''4 |
     a4 e'4 a'4 c''4 |
     <a c' e'>1 |
    <a c' e'>4 <a c' e'>4 <a c' e'>4 <a c' e'>4 |
     <e' gis' b'>4 <e' gis' b'>4 <e' gis' b'>4 <e' gis' b'>4 |
     <a c' e'>4 <a c' e'>4 <a c' e'>4 <a c' e'>4 |
     <d' f' a'>4 <d' f' a'>4 <d' f' a'>4 <d' f' a'>4 |
     <g' b' d''>4 <g' b' d''>4 <g' b' d''>4 <g' b' d''>4 |
     <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 |
     <f' a' c''>4 <f' a' c''>4 <f' a' c''>4 <f' a' c''>4 |
     <e' gis' b'>4 <e' gis' b'>4 <e' gis' b'>4 <e' gis' b'>4 |
     a4 e'4 a'4 c''4 |
     e'4 b'4 e''4 gis''4 |
     a4 e'4 a'4 c''4 |
     d'4 a'4 d''4 f''4 |
     <f' a' c''>4 <f' a' c''>4 <f' a' c''>4 <f' a' c''>4 |
     <e' gis' b'>4 <e' gis' b'>4 <e' gis' b'>4 <e' gis' b'>4 |
     a4 e'4 a'4 c''4 |
     <a c' e'>1 |
    c'4 g'4 c''4 e''4 |
     g'4 b'4 d''4 g''4 |
     a4 e'4 a'4 c''4 |
     e'4 b'4 e''4 gis''4 |
     f'4 c''4 f''4 a''4 |
     c'4 g'4 c''4 e''4 |
     d'4 a'4 d''4 f''4 |
     e'4 b'4 e''4 gis''4 |
     <c' e' g'>2 <g' b' d''>2 |
     <a c' e'>2 <e' gis' b'>2 |
     <d' f' a'>2 <c' e' g'>2 |
     <d' f' a'>2 <e' gis' b'>2 |
     f'4 c''4 f''4 a''4 |
     e'4 b'4 e''4 gis''4 |
     a4 e'4 a'4 c''4 |
     <a c' e'>1 |
    d'4 a'4 d''4 f''4 |
     a4 e'4 a'4 c''4 |
     e'4 b'4 e''4 gis''4 |
     <a c' e'>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

