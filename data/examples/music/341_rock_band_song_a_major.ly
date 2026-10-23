\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Classic Rock Band Song in A"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Rock vocal guide"
    \set Staff.midiInstrument = "choir aahs"
    \tempo 4 = 124
    \key a \major
    \time 4/4

    \clef treble
    s1*0\ff
    a'1 |
     a'4 r4 c''4 e''4 |
     e''8 e''8 g''4 fis''8 e''8 c''4 |
     e''2 a''2 |
    a'8 c''8 d''4 e''8 d''8 c''4 |
     e''4 g''8 fis''8 e''2 |
     c''4 r4 d''4 e''4 |
     g''8 fis''8 e''4 d''2 |
     d''8 e''8 g''4 a''8 g''8 e''4 |
     a''4 g''8 e''8 d''2 |
     c''4 r4 d''4 e''4 |
     g''2 e''2 |
     a'8 c''8 d''4 e''8 d''8 c''4 |
     e''8 fis''8 g''8 a''8 b''4 a''4 |
     g''4 a''8 b''8 cis'''2 |
     g''2 e''2 |
    d''4 e''8 fis''8 g''2 |
     e''8 fis''8 g''8 a''8 g''4 fis''4 |
     g''4 a''8 b''8 cis'''2 |
     b''2 cis'''2 |
     d''4 e''8 fis''8 g''2 |
     e''8 fis''8 g''8 a''8 g''4 fis''4 |
     a''8 b''8 cis'''8 d'''8 cis'''4 b''4 |
     b''1 |
    cis'''8 cis'''8 b''8 a''8 b''8 a''8 g''8 a''8 |
     a''4 b''8 a''8 e''2 |
     cis'''8 cis'''8 b''8 a''8 b''8 a''8 g''8 a''8 |
     cis'''2 a''2 |
     e'''8 d'''8 cis'''4 b''8 cis'''8 e'''4 |
     a''4 b''8 a''8 e''2 |
     a''8 b''8 cis'''8 d'''8 e'''4 cis'''4 |
     cis'''2 a''2 |
     b''4 a''8 g''8 e''2 |
     e''8 g''8 a''4 g''2 |
     e''2 a'2 |
     a''1 |
    e''4 g''8 fis''8 e''2 |
     d''8 e''8 g''4 a''8 g''8 e''4 |
     c''4 r4 d''4 e''4 |
     c''4 d''8 e''8 g''2 |
     a'8 c''8 d''4 e''8 d''8 c''4 |
     a''4 g''8 e''8 d''2 |
     c''4 r4 d''4 e''4 |
     g''2 e''2 |
     d''8 e''8 g''4 a''8 g''8 e''4 |
     e''8 fis''8 g''8 a''8 b''4 a''4 |
     g''4 a''8 b''8 cis'''2 |
     g''2 e''2 |
    b'4 c''8 d''8 e''2 |
     e''8 d''8 c''4 d''8 e''8 g''4 |
     g''8 a''8 b''8 cis'''8 d'''4 cis'''4 |
     b''2 a''2 |
     d''4 e''8 g''8 a''2 |
     e''8 d''8 c''4 d''8 e''8 g''4 |
     a''8 b''8 cis'''8 d'''8 e'''4 cis'''4 |
     b''1 |
    cis'''8 cis'''8 b''8 a''8 b''8 a''8 g''8 a''8 |
     a''4 b''8 a''8 e''2 |
     e'''8 d'''8 cis'''4 b''8 cis'''8 e'''4 |
     cis'''2 a''2 |
     b''4 a''8 g''8 e''2 |
     e''8 g''8 a''4 g''2 |
     e''2 a'2 |
     a''1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Electric guitar"
    \set Staff.midiInstrument = "overdriven guitar"
    \tempo 4 = 124
    \key a \major
    \time 4/4

    \clef "treble_8"
    s1*0\mf
    a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     g'8 g'8 a'8 g'8 b'8 g'8 a'8 g'8 |
     d'8 d'8 f'8 d'8 g'8 d'8 a'8 g'8 |
     <a cis' e'>1 |
    a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     g'8 g'8 a'8 g'8 b'8 g'8 a'8 g'8 |
     d'8 d'8 f'8 d'8 g'8 d'8 a'8 g'8 |
     a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     g'8 g'8 a'8 g'8 b'8 g'8 a'8 g'8 |
     <e' gis' b'>1 |
     a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     g'8 g'8 a'8 g'8 b'8 g'8 a'8 g'8 |
     d'8 d'8 f'8 d'8 g'8 d'8 a'8 g'8 |
     <e' gis' b'>1 |
    <d' fis' a'>2 <g' b' d''>2 |
     <a cis' e'>2 <e' gis' b'>2 |
     <d' fis' a'>2 <g' b' d''>2 |
     <e' gis' b'>1 |
     <d' fis' a'>2 <g' b' d''>2 |
     <a cis' e'>2 <e' gis' b'>2 |
     d'8 e'8 fis'8 g'8 a'8 b'8 cis''8 d''8 |
     <e' gis' b'>1 |
    <a cis' e'>4 <g' b' d''>4 <d' fis' a'>4 <a cis' e'>4 |
     <a cis' e'>4 <e' gis' b'>4 <g' b' d''>4 <d' fis' a'>4 |
     <a cis' e'>4 <g' b' d''>4 <d' fis' a'>4 <a cis' e'>4 |
     <a cis' e'>1 |
     <a cis' e'>4 <g' b' d''>4 <d' fis' a'>4 <a cis' e'>4 |
     <a cis' e'>4 <e' gis' b'>4 <g' b' d''>4 <d' fis' a'>4 |
     d'8 d'8 f'8 d'8 g'8 d'8 a'8 g'8 |
     <a cis' e'>1 |
     <d' fis' a'>2 <g' b' d''>2 |
     <a cis' e'>2 <e' gis' b'>2 |
     d'8 e'8 fis'8 g'8 a'8 b'8 cis''8 d''8 |
     <a cis' e'>1 |
    a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     g'8 g'8 a'8 g'8 b'8 g'8 a'8 g'8 |
     d'8 d'8 f'8 d'8 g'8 d'8 a'8 g'8 |
     <a cis' e'>1 |
     a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     g'8 g'8 a'8 g'8 b'8 g'8 a'8 g'8 |
     <e' gis' b'>1 |
     a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     g'8 g'8 a'8 g'8 b'8 g'8 a'8 g'8 |
     d'8 d'8 f'8 d'8 g'8 d'8 a'8 g'8 |
     <e' gis' b'>1 |
    fis'8 fis'8 a'8 fis'8 b'8 fis'8 cis''8 b'8 |
     d'8 d'8 f'8 d'8 g'8 d'8 a'8 g'8 |
     a8 a8 c'8 a8 d'8 a8 e'8 d'8 |
     <e' gis' b'>1 |
     fis'8 fis'8 a'8 fis'8 b'8 fis'8 cis''8 b'8 |
     d'8 d'8 f'8 d'8 g'8 d'8 a'8 g'8 |
     d'8 e'8 fis'8 g'8 a'8 b'8 cis''8 d''8 |
     <e' gis' b'>1 |
    <a cis' e'>4 <g' b' d''>4 <d' fis' a'>4 <a cis' e'>4 |
     <a cis' e'>4 <e' gis' b'>4 <g' b' d''>4 <d' fis' a'>4 |
     <a cis' e'>4 <g' b' d''>4 <d' fis' a'>4 <a cis' e'>4 |
     <a cis' e'>1 |
     <d' fis' a'>2 <g' b' d''>2 |
     <a cis' e'>2 <e' gis' b'>2 |
     d'8 e'8 fis'8 g'8 a'8 b'8 cis''8 d''8 |
     <a cis' e'>1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Electric bass"
    \set Staff.midiInstrument = "electric bass (finger)"
    \tempo 4 = 124
    \key a \major
    \time 4/4

    \clef bass
    s1*0\mf
    a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     g8 g8 d'8 g8 e'8 d'8 b8 a8 |
     d8 d8 a8 d8 c'8 a8 g8 f8 |
     a,1 |
    a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     g8 g8 d'8 g8 e'8 d'8 b8 a8 |
     d8 d8 a8 d8 c'8 a8 g8 f8 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     g8 g8 d'8 g8 e'8 d'8 b8 a8 |
     e1 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     g8 g8 d'8 g8 e'8 d'8 b8 a8 |
     d8 d8 a8 d8 c'8 a8 g8 f8 |
     e1 |
    d8 d8 a8 d8 c'8 a8 g8 f8 |
     g8 g8 d'8 g8 e'8 d'8 b8 a8 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     e1 |
     d8 d8 a8 d8 c'8 a8 g8 f8 |
     g8 g8 d'8 g8 e'8 d'8 b8 a8 |
     d8 e8 fis8 g8 a8 b8 cis'8 d'8 |
     e1 |
    a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     g8 g8 d'8 g8 e'8 d'8 b8 a8 |
     d8 d8 a8 d8 c'8 a8 g8 f8 |
     a,1 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     g8 g8 d'8 g8 e'8 d'8 b8 a8 |
     d8 d8 a8 d8 c'8 a8 g8 f8 |
     a,1 |
     d8 d8 a8 d8 c'8 a8 g8 f8 |
     g8 g8 d'8 g8 e'8 d'8 b8 a8 |
     d8 e8 fis8 g8 a8 b8 cis'8 d'8 |
     a,1 |
    a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     g8 g8 d'8 g8 e'8 d'8 b8 a8 |
     d8 d8 a8 d8 c'8 a8 g8 f8 |
     a,1 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     g8 g8 d'8 g8 e'8 d'8 b8 a8 |
     e1 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     g8 g8 d'8 g8 e'8 d'8 b8 a8 |
     d8 d8 a8 d8 c'8 a8 g8 f8 |
     e1 |
    fis8 fis8 cis'8 fis8 e'8 cis'8 b8 a8 |
     d8 d8 a8 d8 c'8 a8 g8 f8 |
     a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     e1 |
     fis8 fis8 cis'8 fis8 e'8 cis'8 b8 a8 |
     d8 d8 a8 d8 c'8 a8 g8 f8 |
     d8 e8 fis8 g8 a8 b8 cis'8 d'8 |
     e1 |
    a,8 a,8 e8 a,8 g8 e8 d8 c8 |
     g8 g8 d'8 g8 e'8 d'8 b8 a8 |
     d8 d8 a8 d8 c'8 a8 g8 f8 |
     a,1 |
     d8 d8 a8 d8 c'8 a8 g8 f8 |
     g8 g8 d'8 g8 e'8 d'8 b8 a8 |
     d8 e8 fis8 g8 a8 b8 cis'8 d'8 |
     a,1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Drums"
    \set Staff.midiInstrument = "standard kit"
    \tempo 4 = 124
    \key a \major
    \time 4/4

    \clef percussion
    s1*0\mf
    a4 -. e'4 a4 -. e'4 |
     a4 -. e'4 a4 -. e'4 |
     a8 e'8 g'8 e'8 a8 e'8 g'8 a'8 |
     a1 |
    a4 -. e'4 a4 -. e'4 |
     a4 -. e'4 a4 -. e'4 |
     a4 r4 e'4 a4 |
     a8 e'8 g'8 e'8 a8 e'8 g'8 a'8 |
     a4 -. e'4 a4 -. e'4 |
     a4 -. e'4 a4 -. e'4 |
     a4 r4 e'4 a4 |
     a1 |
     a4 -. e'4 a4 -. e'4 |
     a4 -. e'4 a4 -. e'4 |
     a8 e'8 g'8 e'8 a8 e'8 g'8 a'8 |
     a1 |
    a4 r4 e'4 a4 |
     a4 -. a4 e'4 -. e'4 |
     a4 r4 e'4 a4 |
     a8 e'8 g'8 e'8 a8 e'8 g'8 a'8 |
     a4 r4 e'4 a4 |
     a4 -. a4 e'4 -. e'4 |
     a8 e'8 g'8 e'8 a8 e'8 g'8 a'8 |
     a1 |
    a4 -. e'4 a4 -. e'4 |
     a4 -. e'4 a4 -. e'4 |
     a8 e'8 g'8 e'8 a8 e'8 g'8 a'8 |
     a4 -. e'4 a4 -. e'4 |
     a4 -. e'4 a4 -. e'4 |
     a4 -. e'4 a4 -. e'4 |
     a8 e'8 g'8 e'8 a8 e'8 g'8 a'8 |
     a1 |
     a4 r4 e'4 a4 |
     a4 -. a4 e'4 -. e'4 |
     a8 e'8 g'8 e'8 a8 e'8 g'8 a'8 |
     a1 |
    a4 r4 e'4 a4 |
     a4 -. e'4 a4 -. e'4 |
     a4 r4 e'4 a4 |
     a8 e'8 g'8 e'8 a8 e'8 g'8 a'8 |
     a4 -. e'4 a4 -. e'4 |
     a4 -. e'4 a4 -. e'4 |
     a4 r4 e'4 a4 |
     a1 |
     a4 -. e'4 a4 -. e'4 |
     a4 -. e'4 a4 -. e'4 |
     a8 e'8 g'8 e'8 a8 e'8 g'8 a'8 |
     a1 |
    a4 r4 e'4 a4 |
     a4 -. a4 e'4 -. e'4 |
     a4 r4 e'4 a4 |
     a8 e'8 g'8 e'8 a8 e'8 g'8 a'8 |
     a4 r4 e'4 a4 |
     a4 -. a4 e'4 -. e'4 |
     a8 e'8 g'8 e'8 a8 e'8 g'8 a'8 |
     a1 |
    a4 -. e'4 a4 -. e'4 |
     a4 -. e'4 a4 -. e'4 |
     a8 e'8 g'8 e'8 a8 e'8 g'8 a'8 |
     a4 -. e'4 a4 -. e'4 |
     a4 -. e'4 a4 -. e'4 |
     a8 e'8 g'8 e'8 a8 e'8 g'8 a'8 |
     a4 -. e'4 a4 -. e'4 |
     a1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

