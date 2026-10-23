\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Chanson française douce en fa"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Voix"
    \set Staff.midiInstrument = "voice oohs"
    \tempo 4 = 92
    \key f \major
    \time 4/4

    \clef treble
    s1*0\mf
    r1 |
     c''2 f''2 |
     g''4 f''4 ees''4 c''4 |
     c''1 |
    c''4 f''8 g''8 f''2 |
     e''4 r4 c''4 c''4 |
     c''4 f''8 aes''8 g''2 |
     f''2 r4 f''8 g''8 |
     bes''4 aes''8 g''8 f''2 |
     ees''4 c''8 ees''8 ees''2 |
     f''4 aes''8 g''8 f''2 |
     e''2 c''2 |
     c''4 f''8 g''8 f''2 |
     e''4 r4 c''4 c''4 |
     c''4 f''8 aes''8 g''2 |
     f''2 r4 f''8 g''8 |
     aes''4 g''8 f''8 des''2 |
     c''4 e''8 g''8 e''2 |
     f''2 c''2 |
     f''1 |
    aes''4 aes''8 g''8 f''2 |
     g''4 r4 ees''4 c''4 |
     f''4 aes''8 bes''8 c'''2 |
     g''2 r4 g''8 aes''8 |
     bes''4 aes''8 g''8 f''2 |
     c''4 ees''8 f''8 g''2 |
     f''4 des''8 f''8 bes''2 |
     e''2 c''2 |
     aes''4 aes''8 g''8 f''2 |
     g''4 r4 ees''4 c''4 |
     f''4 aes''8 bes''8 c'''2 |
     g''2 r4 g''8 aes''8 |
     bes''4 aes''8 g''8 f''2 |
     c''4 e''8 g''8 e''2 |
     f''2 c''2 |
     f''1 |
    f''4 r4 f''4 g''4 |
     e''2 c''2 |
     c''4 f''8 aes''8 g''2 |
     f''2 r4 f''8 g''8 |
     bes''4 aes''8 g''8 f''2 |
     ees''4 c''8 ees''8 ees''2 |
     f''4 aes''8 g''8 f''2 |
     e''2 c''2 |
     c''4 f''8 g''8 f''2 |
     e''4 r4 c''4 c''4 |
     f''4 r4 aes''4 g''4 |
     f''2 r4 f''8 g''8 |
     aes''4 g''8 f''8 des''2 |
     c''4 e''8 g''8 e''2 |
     f''2 c''2 |
     f''1 |
    aes''4 aes''8 g''8 f''2 |
     g''4 r4 ees''4 c''4 |
     f''4 aes''8 bes''8 c'''2 |
     g''2 r4 g''8 aes''8 |
     bes''4 aes''8 g''8 f''2 |
     c''4 ees''8 f''8 g''2 |
     f''4 des''8 f''8 bes''2 |
     e''2 c''2 |
     aes''4 aes''8 g''8 f''2 |
     g''4 r4 ees''4 c''4 |
     f''4 aes''8 bes''8 c'''2 |
     g''2 r4 g''8 aes''8 |
     bes''4 aes''8 g''8 f''2 |
     c''4 e''8 g''8 e''2 |
     f''2 c''2 |
     aes''2 f''2 |
    f''4 des''8 f''8 bes''2 |
     f''2 c''2 |
     c''4 e''8 g''8 e''2 |
     f''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitare"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 92
    \key f \major
    \time 4/4

    \clef "treble_8"
    s1*0\mp
    f4 c'4 f'4 aes'4 |
     c'4 g'4 c''4 e''4 |
     f4 c'4 f'4 aes'4 |
     c'4 g'4 c''4 e''4 |
    <f aes c'>4 <f aes c'>4 <f aes c'>4 <f aes c'>4 |
     <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 |
     <f aes c'>4 <f aes c'>4 <f aes c'>4 <f aes c'>4 |
     <bes des' f'>4 <bes des' f'>4 <bes des' f'>4 <bes des' f'>4 |
     <ees' g' bes'>4 <ees' g' bes'>4 <ees' g' bes'>4 <ees' g' bes'>4 |
     <aes c' ees'>4 <aes c' ees'>4 <aes c' ees'>4 <aes c' ees'>4 |
     <des' f' aes'>4 <des' f' aes'>4 <des' f' aes'>4 <des' f' aes'>4 |
     <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 |
     f4 c'4 f'4 aes'4 |
     c'4 g'4 c''4 e''4 |
     f4 c'4 f'4 aes'4 |
     bes4 f'4 bes'4 des''4 |
     <des' f' aes'>4 <des' f' aes'>4 <des' f' aes'>4 <des' f' aes'>4 |
     <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 |
     f4 c'4 f'4 aes'4 |
     <f aes c'>1 |
    aes4 ees'4 aes'4 c''4 |
     ees'4 g'4 bes'4 ees''4 |
     f4 c'4 f'4 aes'4 |
     c'4 g'4 c''4 e''4 |
     des'4 aes'4 des''4 f''4 |
     aes4 ees'4 aes'4 c''4 |
     bes4 f'4 bes'4 des''4 |
     c'4 g'4 c''4 e''4 |
     <aes c' ees'>2 <ees' g' bes'>2 |
     <f aes c'>2 <c' e' g'>2 |
     <bes des' f'>2 <aes c' ees'>2 |
     <bes des' f'>2 <c' e' g'>2 |
     des'4 aes'4 des''4 f''4 |
     c'4 g'4 c''4 e''4 |
     f4 c'4 f'4 aes'4 |
     <f aes c'>1 |
    <f aes c'>4 <f aes c'>4 <f aes c'>4 <f aes c'>4 |
     <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 |
     <f aes c'>4 <f aes c'>4 <f aes c'>4 <f aes c'>4 |
     <bes des' f'>4 <bes des' f'>4 <bes des' f'>4 <bes des' f'>4 |
     <ees' g' bes'>4 <ees' g' bes'>4 <ees' g' bes'>4 <ees' g' bes'>4 |
     <aes c' ees'>4 <aes c' ees'>4 <aes c' ees'>4 <aes c' ees'>4 |
     <des' f' aes'>4 <des' f' aes'>4 <des' f' aes'>4 <des' f' aes'>4 |
     <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 |
     f4 c'4 f'4 aes'4 |
     c'4 g'4 c''4 e''4 |
     f4 c'4 f'4 aes'4 |
     bes4 f'4 bes'4 des''4 |
     <des' f' aes'>4 <des' f' aes'>4 <des' f' aes'>4 <des' f' aes'>4 |
     <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 |
     f4 c'4 f'4 aes'4 |
     <f aes c'>1 |
    aes4 ees'4 aes'4 c''4 |
     ees'4 g'4 bes'4 ees''4 |
     f4 c'4 f'4 aes'4 |
     c'4 g'4 c''4 e''4 |
     des'4 aes'4 des''4 f''4 |
     aes4 ees'4 aes'4 c''4 |
     bes4 f'4 bes'4 des''4 |
     c'4 g'4 c''4 e''4 |
     <aes c' ees'>2 <ees' g' bes'>2 |
     <f aes c'>2 <c' e' g'>2 |
     <bes des' f'>2 <aes c' ees'>2 |
     <bes des' f'>2 <c' e' g'>2 |
     des'4 aes'4 des''4 f''4 |
     c'4 g'4 c''4 e''4 |
     f4 c'4 f'4 aes'4 |
     <f aes c'>1 |
    bes4 f'4 bes'4 des''4 |
     f4 c'4 f'4 aes'4 |
     c'4 g'4 c''4 e''4 |
     <f aes c'>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

