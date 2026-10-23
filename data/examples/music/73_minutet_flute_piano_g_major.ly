\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Minuet for Flute and Piano in G Major"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 112
    \key g \major
    \time 3/4

    \clef treble
    s1*0\mf
    g''8 a''8 b''4 d'''4 |
    b''4. a''8 g''4 |
    d'''4 e'''8 d'''8 c'''4 |
    a''4 b''8 c'''8 d'''4 |
    c'''4. e'''8 g'''4 |
    d'''4 b''8 g''4. |
    e'''4 d'''8 c'''8 b''4 |
    d'''4 b''8 g''4. |
    a''4 b''8 cis'''8 d'''4 |
    b''4. a''8 g''4 |
    g''8 b''8 d'''4 e'''4 |
    a''4 b''8 c'''8 d'''4 |
    d'''8 b''8 g''2 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Piano"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 112
    \key g \major
    \time 3/4

    \clef treble
    s1*0\mp
    <g' b' d''>4 <d'' fis'' a''>4 <g' b' d''>4 |
    <d'' fis'' a''>4 <d'' fis'' a''>4 <g' ais' d''>4 |
    <c'' e'' g''>4 <g' b' d''>4 <c'' e'' g''>4 |
    <d'' fis'' a''>4 <d'' fis'' a''>4 <d'' fis'' a''>4 |
    <c'' dis'' g''>4 <g' ais' d''>4 <c'' dis'' g''>4 |
    <d'' fis'' a''>4 <d'' fis'' a''>4 <g' ais' d''>4 |
    <c'' e'' g''>4 <g' b' d''>4 <c'' e'' g''>4 |
    <d'' fis'' a''>4 <d'' fis'' a''>4 <g' ais' d''>4 |
    <g' ais' d''>4 <d'' fis'' a''>4 <g' ais' d''>4 |
    <d'' fis'' a''>4 <d'' fis'' a''>4 <g' b' d''>4 |
    <g' ais' d''>4 <d'' fis'' a''>4 <g' ais' d''>4 |
    <d'' fis'' a''>4 <d'' fis'' a''>4 <d'' fis'' a''>4 |
    <g' b' d''>4 <d'' fis'' a''>4 <g' b' d''>4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Piano LH"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 112
    \key g \major
    \time 3/4

    \clef bass
    s1*0\p
    g4 d'4 g'4 |
    d'4 g4 g4 |
    c'4 g'4 e'4 |
    d'4 a'4 fis'4 |
    c'4 g'4 e'4 |
    d'4 g4 g4 |
    c'4 g'4 e'4 |
    d'4 g4 g4 |
    g4 d'4 g'4 |
    d'4 g4 g4 |
    g4 d'4 g'4 |
    d'4 a'4 fis'4 |
    g2. |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

