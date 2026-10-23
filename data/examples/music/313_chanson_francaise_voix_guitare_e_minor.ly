\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Chanson française mélancolique en mi mineur"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Voix"
    \set Staff.midiInstrument = "voice oohs"
    \tempo 4 = 88
    \key e \minor
    \time 4/4

    \clef treble
    s1*0\mp
    r1 |
     b'2 e''2 |
     fis''4 e''4 d''4 b'4 |
     b'1 |
    b'4 e''8 fis''8 e''2 |
     dis''4 r4 b'4 b'4 |
     b'4 e''8 g''8 fis''2 |
     e''2 r4 e''8 fis''8 |
     a''4 g''8 fis''8 e''2 |
     d''4 b'8 d''8 d''2 |
     e''4 g''8 fis''8 e''2 |
     dis''2 b'2 |
     b'4 e''8 fis''8 e''2 |
     dis''4 r4 b'4 b'4 |
     b'4 e''8 g''8 fis''2 |
     e''2 r4 e''8 fis''8 |
     g''4 fis''8 e''8 c''2 |
     b'4 dis''8 fis''8 dis''2 |
     e''2 b'2 |
     e''1 |
    g''4 g''8 fis''8 e''2 |
     fis''4 r4 d''4 b'4 |
     e''4 g''8 a''8 b''2 |
     fis''2 r4 fis''8 g''8 |
     a''4 g''8 fis''8 e''2 |
     b'4 d''8 e''8 fis''2 |
     e''4 c''8 e''8 a''2 |
     dis''2 b'2 |
     g''4 g''8 fis''8 e''2 |
     fis''4 r4 d''4 b'4 |
     e''4 g''8 a''8 b''2 |
     fis''2 r4 fis''8 g''8 |
     a''4 g''8 fis''8 e''2 |
     b'4 dis''8 fis''8 dis''2 |
     e''2 b'2 |
     e''1 |
    e''4 r4 e''4 fis''4 |
     dis''2 b'2 |
     b'4 e''8 g''8 fis''2 |
     e''2 r4 e''8 fis''8 |
     a''4 g''8 fis''8 e''2 |
     d''4 b'8 d''8 d''2 |
     e''4 g''8 fis''8 e''2 |
     dis''2 b'2 |
     b'4 e''8 fis''8 e''2 |
     dis''4 r4 b'4 b'4 |
     e''4 r4 g''4 fis''4 |
     e''2 r4 e''8 fis''8 |
     g''4 fis''8 e''8 c''2 |
     b'4 dis''8 fis''8 dis''2 |
     e''2 b'2 |
     e''1 |
    g''4 g''8 fis''8 e''2 |
     fis''4 r4 d''4 b'4 |
     e''4 g''8 a''8 b''2 |
     fis''2 r4 fis''8 g''8 |
     a''4 g''8 fis''8 e''2 |
     b'4 d''8 e''8 fis''2 |
     e''4 c''8 e''8 a''2 |
     dis''2 b'2 |
     g''4 g''8 fis''8 e''2 |
     fis''4 r4 d''4 b'4 |
     e''4 g''8 a''8 b''2 |
     fis''2 r4 fis''8 g''8 |
     a''4 g''8 fis''8 e''2 |
     b'4 dis''8 fis''8 dis''2 |
     e''2 b'2 |
     g''2 e''2 |
    e''4 c''8 e''8 a''2 |
     e''2 b'2 |
     b'4 dis''8 fis''8 dis''2 |
     e''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitare"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 88
    \key e \minor
    \time 4/4

    \clef "treble_8"
    s1*0\p
    e4 b4 e'4 g'4 |
     b4 fis'4 b'4 dis''4 |
     e4 b4 e'4 g'4 |
     b4 fis'4 b'4 dis''4 |
    <e g b>4 <e g b>4 <e g b>4 <e g b>4 |
     <b dis' fis'>4 <b dis' fis'>4 <b dis' fis'>4 <b dis' fis'>4 |
     <e g b>4 <e g b>4 <e g b>4 <e g b>4 |
     <a c' e'>4 <a c' e'>4 <a c' e'>4 <a c' e'>4 |
     <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 |
     <g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
     <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 |
     <b dis' fis'>4 <b dis' fis'>4 <b dis' fis'>4 <b dis' fis'>4 |
     e4 b4 e'4 g'4 |
     b4 fis'4 b'4 dis''4 |
     e4 b4 e'4 g'4 |
     a4 e'4 a'4 c''4 |
     <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 |
     <b dis' fis'>4 <b dis' fis'>4 <b dis' fis'>4 <b dis' fis'>4 |
     e4 b4 e'4 g'4 |
     <e g b>1 |
    g4 d'4 g'4 b'4 |
     d'4 fis'4 a'4 d''4 |
     e4 b4 e'4 g'4 |
     b4 fis'4 b'4 dis''4 |
     c'4 g'4 c''4 e''4 |
     g4 d'4 g'4 b'4 |
     a4 e'4 a'4 c''4 |
     b4 fis'4 b'4 dis''4 |
     <g b d'>2 <d' fis' a'>2 |
     <e g b>2 <b dis' fis'>2 |
     <a c' e'>2 <g b d'>2 |
     <a c' e'>2 <b dis' fis'>2 |
     c'4 g'4 c''4 e''4 |
     b4 fis'4 b'4 dis''4 |
     e4 b4 e'4 g'4 |
     <e g b>1 |
    <e g b>4 <e g b>4 <e g b>4 <e g b>4 |
     <b dis' fis'>4 <b dis' fis'>4 <b dis' fis'>4 <b dis' fis'>4 |
     <e g b>4 <e g b>4 <e g b>4 <e g b>4 |
     <a c' e'>4 <a c' e'>4 <a c' e'>4 <a c' e'>4 |
     <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 |
     <g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
     <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 |
     <b dis' fis'>4 <b dis' fis'>4 <b dis' fis'>4 <b dis' fis'>4 |
     e4 b4 e'4 g'4 |
     b4 fis'4 b'4 dis''4 |
     e4 b4 e'4 g'4 |
     a4 e'4 a'4 c''4 |
     <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 <c' e' g'>4 |
     <b dis' fis'>4 <b dis' fis'>4 <b dis' fis'>4 <b dis' fis'>4 |
     e4 b4 e'4 g'4 |
     <e g b>1 |
    g4 d'4 g'4 b'4 |
     d'4 fis'4 a'4 d''4 |
     e4 b4 e'4 g'4 |
     b4 fis'4 b'4 dis''4 |
     c'4 g'4 c''4 e''4 |
     g4 d'4 g'4 b'4 |
     a4 e'4 a'4 c''4 |
     b4 fis'4 b'4 dis''4 |
     <g b d'>2 <d' fis' a'>2 |
     <e g b>2 <b dis' fis'>2 |
     <a c' e'>2 <g b d'>2 |
     <a c' e'>2 <b dis' fis'>2 |
     c'4 g'4 c''4 e''4 |
     b4 fis'4 b'4 dis''4 |
     e4 b4 e'4 g'4 |
     <e g b>1 |
    a4 e'4 a'4 c''4 |
     e4 b4 e'4 g'4 |
     b4 fis'4 b'4 dis''4 |
     <e g b>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

