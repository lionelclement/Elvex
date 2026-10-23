\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Classic Rock Band Song in E"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Rock vocal guide"
    \set Staff.midiInstrument = "choir aahs"
    \tempo 4 = 132
    \key e \major
    \time 4/4

    \clef treble
    s1*0\ff
    e'1 |
     e'4 r4 g'4 b'4 |
     b'8 b'8 d''4 cis''8 b'8 g'4 |
     b'2 e''2 |
    e'8 g'8 a'4 b'8 a'8 g'4 |
     b'4 d''8 cis''8 b'2 |
     g'4 r4 a'4 b'4 |
     d''8 cis''8 b'4 a'2 |
     a'8 b'8 d''4 e''8 d''8 b'4 |
     e''4 d''8 b'8 a'2 |
     g'4 r4 a'4 b'4 |
     d''2 b'2 |
     e'8 g'8 a'4 b'8 a'8 g'4 |
     b'8 cis''8 d''8 e''8 fis''4 e''4 |
     d''4 e''8 fis''8 gis''2 |
     d''2 b'2 |
    a'4 b'8 cis''8 d''2 |
     b'8 cis''8 d''8 e''8 d''4 cis''4 |
     d''4 e''8 fis''8 gis''2 |
     fis''2 gis''2 |
     a'4 b'8 cis''8 d''2 |
     b'8 cis''8 d''8 e''8 d''4 cis''4 |
     e''8 fis''8 gis''8 a''8 gis''4 fis''4 |
     fis''1 |
    gis''8 gis''8 fis''8 e''8 fis''8 e''8 d''8 e''8 |
     e''4 fis''8 e''8 b'2 |
     gis''8 gis''8 fis''8 e''8 fis''8 e''8 d''8 e''8 |
     gis''2 e''2 |
     b''8 a''8 gis''4 fis''8 gis''8 b''4 |
     e''4 fis''8 e''8 b'2 |
     e''8 fis''8 gis''8 a''8 b''4 gis''4 |
     gis''2 e''2 |
     fis''4 e''8 d''8 b'2 |
     b'8 d''8 e''4 d''2 |
     b'2 e'2 |
     e''1 |
    b'4 d''8 cis''8 b'2 |
     a'8 b'8 d''4 e''8 d''8 b'4 |
     g'4 r4 a'4 b'4 |
     g'4 a'8 b'8 d''2 |
     e'8 g'8 a'4 b'8 a'8 g'4 |
     e''4 d''8 b'8 a'2 |
     g'4 r4 a'4 b'4 |
     d''2 b'2 |
     a'8 b'8 d''4 e''8 d''8 b'4 |
     b'8 cis''8 d''8 e''8 fis''4 e''4 |
     d''4 e''8 fis''8 gis''2 |
     d''2 b'2 |
    fis'4 g'8 a'8 b'2 |
     b'8 a'8 g'4 a'8 b'8 d''4 |
     d''8 e''8 fis''8 gis''8 a''4 gis''4 |
     fis''2 e''2 |
     a'4 b'8 d''8 e''2 |
     b'8 a'8 g'4 a'8 b'8 d''4 |
     e''8 fis''8 gis''8 a''8 b''4 gis''4 |
     fis''1 |
    gis''8 gis''8 fis''8 e''8 fis''8 e''8 d''8 e''8 |
     e''4 fis''8 e''8 b'2 |
     b''8 a''8 gis''4 fis''8 gis''8 b''4 |
     gis''2 e''2 |
     fis''4 e''8 d''8 b'2 |
     b'8 d''8 e''4 d''2 |
     b'2 e'2 |
     e''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Electric guitar"
    \set Staff.midiInstrument = "overdriven guitar"
    \tempo 4 = 132
    \key e \major
    \time 4/4

    \clef "treble_8"
    s1*0\mf
    e8 e8 g8 e8 a8 e8 b8 a8 |
     d'8 d'8 e'8 d'8 fis'8 d'8 e'8 d'8 |
     a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     <e gis b>1 |
    e8 e8 g8 e8 a8 e8 b8 a8 |
     e8 e8 g8 e8 a8 e8 b8 a8 |
     d'8 d'8 e'8 d'8 fis'8 d'8 e'8 d'8 |
     a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     e8 e8 g8 e8 a8 e8 b8 a8 |
     e8 e8 g8 e8 a8 e8 b8 a8 |
     d'8 d'8 e'8 d'8 fis'8 d'8 e'8 d'8 |
     <b dis' fis'>1 |
     e8 e8 g8 e8 a8 e8 b8 a8 |
     d'8 d'8 e'8 d'8 fis'8 d'8 e'8 d'8 |
     a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     <b dis' fis'>1 |
    <a cis' e'>2 <d' fis' a'>2 |
     <e gis b>2 <b dis' fis'>2 |
     <a cis' e'>2 <d' fis' a'>2 |
     <b dis' fis'>1 |
     <a cis' e'>2 <d' fis' a'>2 |
     <e gis b>2 <b dis' fis'>2 |
     a8 b8 cis'8 d'8 e'8 fis'8 gis'8 a'8 |
     <b dis' fis'>1 |
    <e gis b>4 <d' fis' a'>4 <a cis' e'>4 <e gis b>4 |
     <e gis b>4 <b dis' fis'>4 <d' fis' a'>4 <a cis' e'>4 |
     <e gis b>4 <d' fis' a'>4 <a cis' e'>4 <e gis b>4 |
     <e gis b>1 |
     <e gis b>4 <d' fis' a'>4 <a cis' e'>4 <e gis b>4 |
     <e gis b>4 <b dis' fis'>4 <d' fis' a'>4 <a cis' e'>4 |
     a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     <e gis b>1 |
     <a cis' e'>2 <d' fis' a'>2 |
     <e gis b>2 <b dis' fis'>2 |
     a8 b8 cis'8 d'8 e'8 fis'8 gis'8 a'8 |
     <e gis b>1 |
    e8 e8 g8 e8 a8 e8 b8 a8 |
     d'8 d'8 e'8 d'8 fis'8 d'8 e'8 d'8 |
     a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     <e gis b>1 |
     e8 e8 g8 e8 a8 e8 b8 a8 |
     e8 e8 g8 e8 a8 e8 b8 a8 |
     d'8 d'8 e'8 d'8 fis'8 d'8 e'8 d'8 |
     <b dis' fis'>1 |
     e8 e8 g8 e8 a8 e8 b8 a8 |
     d'8 d'8 e'8 d'8 fis'8 d'8 e'8 d'8 |
     a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     <b dis' fis'>1 |
    cis'8 cis'8 e'8 cis'8 fis'8 cis'8 gis'8 fis'8 |
     a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     e8 e8 g8 e8 a8 e8 b8 a8 |
     <b dis' fis'>1 |
     cis'8 cis'8 e'8 cis'8 fis'8 cis'8 gis'8 fis'8 |
     a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     a8 b8 cis'8 d'8 e'8 fis'8 gis'8 a'8 |
     <b dis' fis'>1 |
    <e gis b>4 <d' fis' a'>4 <a cis' e'>4 <e gis b>4 |
     <e gis b>4 <b dis' fis'>4 <d' fis' a'>4 <a cis' e'>4 |
     <e gis b>4 <d' fis' a'>4 <a cis' e'>4 <e gis b>4 |
     <e gis b>1 |
     <a cis' e'>2 <d' fis' a'>2 |
     <e gis b>2 <b dis' fis'>2 |
     a8 b8 cis'8 d'8 e'8 fis'8 gis'8 a'8 |
     <e gis b>1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Electric bass"
    \set Staff.midiInstrument = "electric bass (finger)"
    \tempo 4 = 132
    \key e \major
    \time 4/4

    \clef bass
    s1*0\mf
    e,8 e,8 b,8 e,8 d8 b,8 a,8 g,8 |
     d8 d8 a8 d8 b8 a8 fis8 e8 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     e,1 |
    e,8 e,8 b,8 e,8 d8 b,8 a,8 g,8 |
     e,8 e,8 b,8 e,8 d8 b,8 a,8 g,8 |
     d8 d8 a8 d8 b8 a8 fis8 e8 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     e,8 e,8 b,8 e,8 d8 b,8 a,8 g,8 |
     e,8 e,8 b,8 e,8 d8 b,8 a,8 g,8 |
     d8 d8 a8 d8 b8 a8 fis8 e8 |
     b,1 |
     e,8 e,8 b,8 e,8 d8 b,8 a,8 g,8 |
     d8 d8 a8 d8 b8 a8 fis8 e8 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     b,1 |
    a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     d8 d8 a8 d8 b8 a8 fis8 e8 |
     e,8 e,8 b,8 e,8 d8 b,8 a,8 g,8 |
     b,1 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     d8 d8 a8 d8 b8 a8 fis8 e8 |
     a,8 b,8 cis8 d8 e8 fis8 gis8 a8 |
     b,1 |
    e,8 e,8 b,8 e,8 d8 b,8 a,8 g,8 |
     d8 d8 a8 d8 b8 a8 fis8 e8 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     e,1 |
     e,8 e,8 b,8 e,8 d8 b,8 a,8 g,8 |
     d8 d8 a8 d8 b8 a8 fis8 e8 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     e,1 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     d8 d8 a8 d8 b8 a8 fis8 e8 |
     a,8 b,8 cis8 d8 e8 fis8 gis8 a8 |
     e,1 |
    e,8 e,8 b,8 e,8 d8 b,8 a,8 g,8 |
     d8 d8 a8 d8 b8 a8 fis8 e8 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     e,1 |
     e,8 e,8 b,8 e,8 d8 b,8 a,8 g,8 |
     e,8 e,8 b,8 e,8 d8 b,8 a,8 g,8 |
     d8 d8 a8 d8 b8 a8 fis8 e8 |
     b,1 |
     e,8 e,8 b,8 e,8 d8 b,8 a,8 g,8 |
     d8 d8 a8 d8 b8 a8 fis8 e8 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     b,1 |
    cis8 cis8 gis8 cis8 b8 gis8 fis8 e8 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     e,8 e,8 b,8 e,8 d8 b,8 a,8 g,8 |
     b,1 |
     cis8 cis8 gis8 cis8 b8 gis8 fis8 e8 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     a,8 b,8 cis8 d8 e8 fis8 gis8 a8 |
     b,1 |
    e,8 e,8 b,8 e,8 d8 b,8 a,8 g,8 |
     d8 d8 a8 d8 b8 a8 fis8 e8 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     e,1 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     d8 d8 a8 d8 b8 a8 fis8 e8 |
     a,8 b,8 cis8 d8 e8 fis8 gis8 a8 |
     e,1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Drums"
    \set Staff.midiInstrument = "standard kit"
    \tempo 4 = 132
    \key e \major
    \time 4/4

    \clef percussion
    s1*0\mf
    e4 -. b4 e4 -. b4 |
     e4 -. b4 e4 -. b4 |
     e8 b8 d'8 b8 e8 b8 d'8 e'8 |
     e1 |
    e4 -. b4 e4 -. b4 |
     e4 -. b4 e4 -. b4 |
     e4 r4 b4 e4 |
     e8 b8 d'8 b8 e8 b8 d'8 e'8 |
     e4 -. b4 e4 -. b4 |
     e4 -. b4 e4 -. b4 |
     e4 r4 b4 e4 |
     e1 |
     e4 -. b4 e4 -. b4 |
     e4 -. b4 e4 -. b4 |
     e8 b8 d'8 b8 e8 b8 d'8 e'8 |
     e1 |
    e4 r4 b4 e4 |
     e4 -. e4 b4 -. b4 |
     e4 r4 b4 e4 |
     e8 b8 d'8 b8 e8 b8 d'8 e'8 |
     e4 r4 b4 e4 |
     e4 -. e4 b4 -. b4 |
     e8 b8 d'8 b8 e8 b8 d'8 e'8 |
     e1 |
    e4 -. b4 e4 -. b4 |
     e4 -. b4 e4 -. b4 |
     e8 b8 d'8 b8 e8 b8 d'8 e'8 |
     e4 -. b4 e4 -. b4 |
     e4 -. b4 e4 -. b4 |
     e4 -. b4 e4 -. b4 |
     e8 b8 d'8 b8 e8 b8 d'8 e'8 |
     e1 |
     e4 r4 b4 e4 |
     e4 -. e4 b4 -. b4 |
     e8 b8 d'8 b8 e8 b8 d'8 e'8 |
     e1 |
    e4 r4 b4 e4 |
     e4 -. b4 e4 -. b4 |
     e4 r4 b4 e4 |
     e8 b8 d'8 b8 e8 b8 d'8 e'8 |
     e4 -. b4 e4 -. b4 |
     e4 -. b4 e4 -. b4 |
     e4 r4 b4 e4 |
     e1 |
     e4 -. b4 e4 -. b4 |
     e4 -. b4 e4 -. b4 |
     e8 b8 d'8 b8 e8 b8 d'8 e'8 |
     e1 |
    e4 r4 b4 e4 |
     e4 -. e4 b4 -. b4 |
     e4 r4 b4 e4 |
     e8 b8 d'8 b8 e8 b8 d'8 e'8 |
     e4 r4 b4 e4 |
     e4 -. e4 b4 -. b4 |
     e8 b8 d'8 b8 e8 b8 d'8 e'8 |
     e1 |
    e4 -. b4 e4 -. b4 |
     e4 -. b4 e4 -. b4 |
     e8 b8 d'8 b8 e8 b8 d'8 e'8 |
     e4 -. b4 e4 -. b4 |
     e4 -. b4 e4 -. b4 |
     e8 b8 d'8 b8 e8 b8 d'8 e'8 |
     e4 -. b4 e4 -. b4 |
     e1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

