\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Chanson française - récit bas"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Voix"
    \set Staff.midiInstrument = "voice oohs"
    \tempo 4 = 86
    \key a \minor
    \time 4/4

    \clef treble
    s1*0\mp
    r1 |
     a'2 c''2 |
     c''2 r4 b'8 a'8 |
     a'1 |
    a'2 c''2 |
     c''2 r4 b'8 a'8 |
     b'4 r4 a'8 c''4. |
     r1 |
     c''4 d''4 e''4 d''4 |
     c''2. b'4 |
     e''4 d''8 c''8 b'2 |
     d''2 b'2 |
     a'8 a'8 b'4 c''2 |
     d''2 r4 c''8 b'8 |
     b'4 r4 a'8 c''4. |
     r1 |
     f''4 e''8 d''8 c''2 |
     e''2 gis''2 |
     e''2 a'2 |
     a'1 |
    e''8 e''8 f''4 e''2 |
     d''2 c''2 |
     f''8 f''8 e''4 d''2 |
     c''2 r4 b'8 a'8 |
     g''4 f''4 e''4 d''4 |
     e''2 c''2 |
     f''8 e''8 d''4 c''2 |
     d''2 b'2 |
     e''8 e''8 f''4 e''2 |
     d''2 c''2 |
     f''8 f''8 e''4 d''2 |
     d''2 r4 c''8 b'8 |
     g''8 f''8 e''4 d''2 |
     e''2 gis''2 |
     e''2 a'2 |
     a''1 |
    a'8 a'8 b'4 c''2 |
     d''2 r4 c''8 b'8 |
     b'4 r4 a'8 c''4. |
     r1 |
     d''4 e''4 f''4 e''4 |
     c''2. b'4 |
     e''4 d''8 c''8 b'2 |
     d''2 b'2 |
     a'2 c''2 |
     c''2 r4 b'8 a'8 |
     b'4 r4 a'8 c''4. |
     r1 |
     f''4 e''8 d''8 c''2 |
     e''2 gis''2 |
     e''2 a'2 |
     a'1 |
    e''8 e''8 f''4 e''2 |
     d''2 c''2 |
     f''8 f''8 e''4 d''2 |
     c''2 r4 b'8 a'8 |
     a''4 g''4 f''4 e''4 |
     e''2 c''2 |
     f''8 e''8 d''4 c''2 |
     d''2 b'2 |
     e''8 e''8 f''4 e''2 |
     d''2 c''2 |
     f''8 f''8 e''4 d''2 |
     d''2 r4 c''8 b'8 |
     g''8 f''8 e''4 d''2 |
     e''2 gis''2 |
     e''2 a'2 |
     a''1 |
    e''4 d''8 c''8 b'2 |
     e''2 gis''2 |
     e''2 a'2 |
     a'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitare"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 86
    \key a \minor
    \time 4/4

    \clef "treble_8"
    s1*0\p
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

