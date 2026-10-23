\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Minuet for Piano in F Major"
  composer = "Elvex"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Piano"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 112
    \key f \major
    \time 3/4

    \clef treble
    s1*0\mp
    <f' aes' c''>2 <c'' e'' g''>4 |
    <c'' e'' g''>2 <f' aes' c''>4 |
    <bes' d'' f''>8 <g' bes' d''>8 <bes' d'' f''>4 <c'' e'' g''>4 |
    <c'' e'' g''>4 <c'' e'' g''>2 |
    <bes' d'' f''>4 <f' a' c''>8 <bes' d'' f''>8 <f' a' c''>4 |
    <c'' e'' g''>2 <f' a' c''>4 |
    <f' a' c''>2 <c'' e'' g''>4 |
    <c'' e'' g''>2 <f' aes' c''>4 |
    <c'' e'' g''>4 <c'' e'' g''>2 |
    <f' aes' c''>2 <f' aes' c''>4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Piano LH"
    \set Staff.midiInstrument = "acoustic grand"
    \tempo 4 = 112
    \key f \major
    \time 3/4

    \clef bass
    s1*0\p
    f2 c'4 |
    c'2 f4 |
    bes8 f'8 d'4 c'4 |
    c'4 g'2 |
    bes4 f'8 bes8 f'4 |
    c'2 f4 |
    f2 c'4 |
    c'2 f4 |
    c'4 g'2 |
    f2. |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

