\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Flute and Piano in Bes Major"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \tempo 4 = 92
    \key bes \major
    \time 4/4

    \clef treble
    s1*0\mf
    bes''8 c'''8 d'''4 f'''8 ees'''8 d'''4 |
    d'''8 ees'''8 d'''4 c'''8 d'''8 f'''4 |
    c'''4 d'''4 e'''4 f'''4 |
    f'''4 d'''4 c'''4 bes''4 |
    f'''8 ees'''8 d'''4 c'''8 d'''8 bes''4 |
    f'''4 d'''4 c'''4 bes''4 |
    ees'''4 f'''4 a'''4 f'''4 |
    f'''8 d'''8 c'''4 bes''2 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Piano"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 92
    \key bes \major
    \time 4/4

    \clef treble
    s1*0\mp
    <bes' d'' f''>2 <f'' a'' c'''>2 |
    <ees'' ges'' bes''>2 <bes' des'' f''>2 |
    <f'' a'' c'''>2 <f'' a'' c'''>2 |
    <bes' des'' f''>2 <f'' a'' c'''>2 |
    <bes' d'' f''>1 |
    <f'' a'' c'''>2 <bes' des'' f''>2 |
    <f'' a'' c'''>2 <f'' a'' c'''>2 |
    <bes' des'' f''>1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Piano LH"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 92
    \key bes \major
    \time 4/4

    \clef bass
    s1*0\p
    bes8 f'8 d'8 f'8 bes8 f'8 d'8 f'8 |
    ees'4 bes'4 g'4 bes'4 |
    f'8 c''8 a'8 c''8 f'8 c''8 a'8 c''8 |
    bes4 f'4 bes'4 f'4 |
    bes8 f'8 d'8 f'8 bes8 f'8 d'8 f'8 |
    f'4 c''4 a'4 c''4 |
    f'2 f'8 f'8 f'4 |
    bes1 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

