\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Chanson française nocturne en si mineur"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Voix"
    \set Staff.midiInstrument = "voice oohs"
    \tempo 4 = 78
    \key b \minor
    \time 4/4

    \clef treble
    s1*0\mp
    r1 |
     fis''2 b''2 |
     cis'''4 b''4 a''4 fis''4 |
     fis''1 |
    fis''4 b''8 cis'''8 b''2 |
     ais''4 r4 fis''4 fis''4 |
     fis''4 b''8 d'''8 cis'''2 |
     b''2 r4 b''8 cis'''8 |
     e'''4 d'''8 cis'''8 b''2 |
     a''4 fis''8 a''8 a''2 |
     b''4 d'''8 cis'''8 b''2 |
     ais''2 fis''2 |
     fis''4 b''8 cis'''8 b''2 |
     ais''4 r4 fis''4 fis''4 |
     fis''4 b''8 d'''8 cis'''2 |
     b''2 r4 b''8 cis'''8 |
     d'''4 cis'''8 b''8 g''2 |
     fis''4 ais''8 cis'''8 ais''2 |
     b''2 fis''2 |
     b''1 |
    d'''4 d'''8 cis'''8 b''2 |
     cis'''4 r4 a''4 fis''4 |
     b''4 d'''8 e'''8 fis'''2 |
     cis'''2 r4 cis'''8 d'''8 |
     e'''4 d'''8 cis'''8 b''2 |
     fis''4 a''8 b''8 cis'''2 |
     b''4 g''8 b''8 e'''2 |
     ais''2 fis''2 |
     d'''4 d'''8 cis'''8 b''2 |
     cis'''4 r4 a''4 fis''4 |
     b''4 d'''8 e'''8 fis'''2 |
     cis'''2 r4 cis'''8 d'''8 |
     e'''4 d'''8 cis'''8 b''2 |
     fis''4 ais''8 cis'''8 ais''2 |
     b''2 fis''2 |
     b''1 |
    b''4 r4 b''4 cis'''4 |
     ais''2 fis''2 |
     fis''4 b''8 d'''8 cis'''2 |
     b''2 r4 b''8 cis'''8 |
     e'''4 d'''8 cis'''8 b''2 |
     a''4 fis''8 a''8 a''2 |
     b''4 d'''8 cis'''8 b''2 |
     ais''2 fis''2 |
     fis''4 b''8 cis'''8 b''2 |
     ais''4 r4 fis''4 fis''4 |
     b''4 r4 d'''4 cis'''4 |
     b''2 r4 b''8 cis'''8 |
     d'''4 cis'''8 b''8 g''2 |
     fis''4 ais''8 cis'''8 ais''2 |
     b''2 fis''2 |
     b''1 |
    d'''4 d'''8 cis'''8 b''2 |
     cis'''4 r4 a''4 fis''4 |
     b''4 d'''8 e'''8 fis'''2 |
     cis'''2 r4 cis'''8 d'''8 |
     e'''4 d'''8 cis'''8 b''2 |
     fis''4 a''8 b''8 cis'''2 |
     b''4 g''8 b''8 e'''2 |
     ais''2 fis''2 |
     d'''4 d'''8 cis'''8 b''2 |
     cis'''4 r4 a''4 fis''4 |
     b''4 d'''8 e'''8 fis'''2 |
     cis'''2 r4 cis'''8 d'''8 |
     e'''4 d'''8 cis'''8 b''2 |
     fis''4 ais''8 cis'''8 ais''2 |
     b''2 fis''2 |
     d'''2 b''2 |
    b''4 g''8 b''8 e'''2 |
     b''2 fis''2 |
     fis''4 ais''8 cis'''8 ais''2 |
     b''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitare"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \tempo 4 = 78
    \key b \minor
    \time 4/4

    \clef "treble_8"
    s1*0\p
    b4 fis'4 b'4 d''4 |
     fis'4 cis''4 fis''4 ais''4 |
     b4 fis'4 b'4 d''4 |
     fis'4 cis''4 fis''4 ais''4 |
    <b d' fis'>4 <b d' fis'>4 <b d' fis'>4 <b d' fis'>4 |
     <fis' ais' cis''>4 <fis' ais' cis''>4 <fis' ais' cis''>4 <fis' ais' cis''>4 |
     <b d' fis'>4 <b d' fis'>4 <b d' fis'>4 <b d' fis'>4 |
     <e' g' b'>4 <e' g' b'>4 <e' g' b'>4 <e' g' b'>4 |
     <a' cis'' e''>4 <a' cis'' e''>4 <a' cis'' e''>4 <a' cis'' e''>4 |
     <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 |
     <g' b' d''>4 <g' b' d''>4 <g' b' d''>4 <g' b' d''>4 |
     <fis' ais' cis''>4 <fis' ais' cis''>4 <fis' ais' cis''>4 <fis' ais' cis''>4 |
     b4 fis'4 b'4 d''4 |
     fis'4 cis''4 fis''4 ais''4 |
     b4 fis'4 b'4 d''4 |
     e'4 b'4 e''4 g''4 |
     <g' b' d''>4 <g' b' d''>4 <g' b' d''>4 <g' b' d''>4 |
     <fis' ais' cis''>4 <fis' ais' cis''>4 <fis' ais' cis''>4 <fis' ais' cis''>4 |
     b4 fis'4 b'4 d''4 |
     <b d' fis'>1 |
    d'4 a'4 d''4 fis''4 |
     a'4 cis''4 e''4 a''4 |
     b4 fis'4 b'4 d''4 |
     fis'4 cis''4 fis''4 ais''4 |
     g'4 d''4 g''4 b''4 |
     d'4 a'4 d''4 fis''4 |
     e'4 b'4 e''4 g''4 |
     fis'4 cis''4 fis''4 ais''4 |
     <d' fis' a'>2 <a' cis'' e''>2 |
     <b d' fis'>2 <fis' ais' cis''>2 |
     <e' g' b'>2 <d' fis' a'>2 |
     <e' g' b'>2 <fis' ais' cis''>2 |
     g'4 d''4 g''4 b''4 |
     fis'4 cis''4 fis''4 ais''4 |
     b4 fis'4 b'4 d''4 |
     <b d' fis'>1 |
    <b d' fis'>4 <b d' fis'>4 <b d' fis'>4 <b d' fis'>4 |
     <fis' ais' cis''>4 <fis' ais' cis''>4 <fis' ais' cis''>4 <fis' ais' cis''>4 |
     <b d' fis'>4 <b d' fis'>4 <b d' fis'>4 <b d' fis'>4 |
     <e' g' b'>4 <e' g' b'>4 <e' g' b'>4 <e' g' b'>4 |
     <a' cis'' e''>4 <a' cis'' e''>4 <a' cis'' e''>4 <a' cis'' e''>4 |
     <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 <d' fis' a'>4 |
     <g' b' d''>4 <g' b' d''>4 <g' b' d''>4 <g' b' d''>4 |
     <fis' ais' cis''>4 <fis' ais' cis''>4 <fis' ais' cis''>4 <fis' ais' cis''>4 |
     b4 fis'4 b'4 d''4 |
     fis'4 cis''4 fis''4 ais''4 |
     b4 fis'4 b'4 d''4 |
     e'4 b'4 e''4 g''4 |
     <g' b' d''>4 <g' b' d''>4 <g' b' d''>4 <g' b' d''>4 |
     <fis' ais' cis''>4 <fis' ais' cis''>4 <fis' ais' cis''>4 <fis' ais' cis''>4 |
     b4 fis'4 b'4 d''4 |
     <b d' fis'>1 |
    d'4 a'4 d''4 fis''4 |
     a'4 cis''4 e''4 a''4 |
     b4 fis'4 b'4 d''4 |
     fis'4 cis''4 fis''4 ais''4 |
     g'4 d''4 g''4 b''4 |
     d'4 a'4 d''4 fis''4 |
     e'4 b'4 e''4 g''4 |
     fis'4 cis''4 fis''4 ais''4 |
     <d' fis' a'>2 <a' cis'' e''>2 |
     <b d' fis'>2 <fis' ais' cis''>2 |
     <e' g' b'>2 <d' fis' a'>2 |
     <e' g' b'>2 <fis' ais' cis''>2 |
     g'4 d''4 g''4 b''4 |
     fis'4 cis''4 fis''4 ais''4 |
     b4 fis'4 b'4 d''4 |
     <b d' fis'>1 |
    e'4 b'4 e''4 g''4 |
     b4 fis'4 b'4 d''4 |
     fis'4 cis''4 fis''4 ais''4 |
     <b d' fis'>1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

