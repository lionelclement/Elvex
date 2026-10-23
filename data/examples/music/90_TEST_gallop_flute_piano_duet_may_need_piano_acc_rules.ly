\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "TEST Gigue for Flute and Piano"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 124
    \key g \major
    \time 6/8

    \clef treble
    s1*0\mf
    g''4 b''8 d'''4 b''8 |
     g''4 b''8 d'''4 b''8 |
     c'''4 e'''8 g'''4 e'''8 |
     d'''4 c'''8 b''4 g''8 |
     g''4 b''8 d'''4 b''8 |
     d'''4 c'''8 b''4 g''8 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Piano"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 124
    \key g \major
    \time 6/8

    \clef treble
    s1*0\mp
    <g' ais' d''>4 <g' ais' d''>8 <d'' fis'' a''>4 <d'' fis'' a''>8 |
     <g' ais' d''>4 <g' ais' d''>8 <d'' fis'' a''>4 <d'' fis'' a''>8 |
     <g' ais' d''>4 <g' ais' d''>8 <d'' fis'' a''>4 <d'' fis'' a''>8 |
     <d'' fis'' a''>4 <d'' fis'' a''>8 <g' ais' d''>4 <g' ais' d''>8 |
     <g' ais' d''>4 <g' ais' d''>8 <d'' fis'' a''>4 <d'' fis'' a''>8 |
     <d'' fis'' a''>4 <d'' fis'' a''>8 <g' b' d''>4 <g' b' d''>8 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Piano LH"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 124
    \key g \major
    \time 6/8

    \clef bass
    s1*0\p
    g4 d'8 g'4 d'8 |
     g4 d'8 g'4 d'8 |
     g4 d'8 g'4 d'8 |
     d'4 g'8 d'4 g8 |
     g4 d'8 g'4 d'8 |
     d'4 g'8 d'4 g8 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

