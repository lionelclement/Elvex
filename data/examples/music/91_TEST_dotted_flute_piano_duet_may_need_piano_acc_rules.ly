\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "TEST Dotted Rhythm for Flute and Piano"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 96
    \key d \major
    \time 4/4

    \clef treble
    s1*0\mf
    d''8. e''16 fis''4 a''2 |
     d''8. e''16 fis''4 a''2 |
     g''8. a''16 b''4 d'''2 |
     a''8. g''16 fis''4 d''2 |
     d''8. e''16 fis''4 a''2 |
     a''8. g''16 fis''4 d''2 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Piano"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 96
    \key d \major
    \time 4/4

    \clef treble
    s1*0\mp
    <d' fis' a'>8. <d' fis' a'>16 <a' cis'' e''>4 <d' fis' a'>2 |
     <d' fis' a'>8. <d' fis' a'>16 <a' cis'' e''>4 <d' fis' a'>2 |
     <d' fis' a'>8. <d' fis' a'>16 <a' cis'' e''>4 <d' fis' a'>2 |
     <a' cis'' e''>8. <a' cis'' e''>16 <d' fis' a'>4 <d' fis' a'>2 |
     <d' fis' a'>8. <d' fis' a'>16 <a' cis'' e''>4 <d' fis' a'>2 |
     <a' cis'' e''>8. <a' cis'' e''>16 <d' fis' a'>4 <d' fis' a'>2 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Piano LH"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 96
    \key d \major
    \time 4/4

    \clef bass
    s1*0\p
    d4 a4 d4 a4 |
     d4 a4 d4 a4 |
     d4 a4 d4 a4 |
     a4 d'4 a4 d4 |
     d4 a4 d4 a4 |
     a4 d'4 a4 d4 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

