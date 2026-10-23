\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Chanson française - descendante"
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
     a''4 g''8 e''8 d''2 |
     c''4 d''8 c''8 b'2 |
     e'1 |
    a''4 g''8 e''8 d''2 |
     g''8 fis''8 e''4 d''8 c''8 b'4 |
     e''4 d''4 c''4 b'4 |
     b'2 r4 a'8 g'8 |
     c''4 d''8 c''8 b'2 |
     d''4 c''8 b'8 a'2 |
     e'1 |
     c''2 a'2 |
     b''4 a''8 g''8 e''2 |
     g''8 fis''8 e''4 d''8 c''8 b'4 |
     fis''4 e''8 d''8 c''2 |
     b'2 r4 a'8 g'8 |
     a'2 e'2 |
     b'4 dis''8 fis''8 dis''2 |
     b'2 e'2 |
     e'1 |
    b''2. a''4 |
     a''8 g''8 fis''4 e''8 d''8 c''4 |
     c''4 b'8 a'8 g'2 |
     b'2 r4 a'8 g'8 |
     d'''2. b''4 |
     b''8 a''8 g''4 fis''8 e''8 d''4 |
     e''8 d''8 c''4 b'2 |
     c''2 a'2 |
     b''2. a''4 |
     a''8 g''8 fis''4 e''8 d''8 c''4 |
     d''4 c''8 b'8 a'2 |
     b'2 r4 a'8 g'8 |
     g''8 e''8 d''4 c''2 |
     b'4 dis''8 fis''8 dis''2 |
     b'2 e'2 |
     e''1 |
    b''4 a''8 g''8 e''2 |
     g''8 fis''8 e''4 d''8 c''8 b'4 |
     e''4 d''4 c''4 b'4 |
     b'2 r4 a'8 g'8 |
     d''4 e''8 d''8 c''2 |
     d''4 c''8 b'8 a'2 |
     e'1 |
     c''2 a'2 |
     a''4 g''8 e''8 d''2 |
     g''8 fis''8 e''4 d''8 c''8 b'4 |
     fis''4 e''8 d''8 c''2 |
     b'2 r4 a'8 g'8 |
     a'2 e'2 |
     b'4 dis''8 fis''8 dis''2 |
     b'2 e'2 |
     e'1 |
    b''2. a''4 |
     a''8 g''8 fis''4 e''8 d''8 c''4 |
     c''4 b'8 a'8 g'2 |
     b'2 r4 a'8 g'8 |
     d'''2. b''4 |
     b''8 a''8 g''4 fis''8 e''8 d''4 |
     e''8 d''8 c''4 b'2 |
     c''2 a'2 |
     b''2. a''4 |
     a''8 g''8 fis''4 e''8 d''8 c''4 |
     d''4 c''8 b'8 a'2 |
     b'2 r4 a'8 g'8 |
     g''8 e''8 d''4 c''2 |
     b'4 dis''8 fis''8 dis''2 |
     b'2 e'2 |
     e''1 |
    a'2 e'2 |
     b'4 dis''8 fis''8 dis''2 |
     b'2 e'2 |
     e'1 |
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

