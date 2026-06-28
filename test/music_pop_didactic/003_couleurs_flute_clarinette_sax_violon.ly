\version "2.26.0"
\paper {
  tagline = ##f
}
\header {
  title = "Pop de chambre"
  composer = "Elvex didactic pop"
}
\score {
<<
  \new Staff {
    \set Staff.instrumentName = "Flute"
    \set Staff.midiInstrument = "flute"
    \clef treble
    \tempo 4 = 96
    \key c \major
    \time 4/4

    s1*0\mf
r1 |
c''8 d''8 e''4 d''8 c''4. |
e''8 f''8 e''4 d''4 c''4 |
g''8 a''8 g''4 e''8 g''4. |
a''8 g''8 a''4 c''4 b''4 |
f''8 e''8 d''4 e''8 c''4. |
g''8 a''8 g''4 e''8 g''4. |
e''8 f''8 e''4 d''4 c''4 |
f''8 e''8 d''4 e''8 c''4. |
g''8 a''8 g''4 e''8 g''4. |
f''4 g''8 a''8 g''2 |
f''4 g''4 a''4 c''4 |
e''2 d''2 |
g''4 a''8 b''8 a''2 |
f''4 e''4 d''4 g''4 |
d''2 c''2 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Clarinette"
    \set Staff.midiInstrument = "clarinet"
    \clef treble
    \tempo 4 = 96
    \key c \major
    \time 4/4

    s1*0\mp
r1 |
r1 |
e'2 f'2 |
r1 |
r1 |
c'2 e'2 |
r1 |
c'1 |
r1 |
e'2 f'2 |
r1 |
a'2 g'2 |
r1 |
e'4 f'4 g'4 f'4 |
f'2 e'2 |
c'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Saxophone"
    \set Staff.midiInstrument = "alto sax"
    \clef treble
    \tempo 4 = 96
    \key c \major
    \time 4/4

    s1*0\mp
r1 |
r1 |
e'2 f'2 |
r1 |
r1 |
c'2 e'2 |
r1 |
c'1 |
r1 |
e'2 f'2 |
r1 |
a'2 g'2 |
r1 |
e'4 f'4 g'4 f'4 |
f'2 e'2 |
c'1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Violon"
    \set Staff.midiInstrument = "violin"
    \clef treble
    \tempo 4 = 96
    \key c \major
    \time 4/4

    s1*0\p
<c' e' g'>1 |
<c' e' g'>1 |
<c' e' g'>1 |
<g' b' d''>1 |
<a' c'' e''>1 |
<f' a' c''>1 |
<g' b' d''>1 |
<c' e' g'>1 |
<f' a' c''>1 |
<g' b' d''>1 |
<c' e' g'>1 |
<a' c'' e''>1 |
<f' a' c''>1 |
<c' e' g'>1 |
<g' b' d''>1 |
<c' e' g'>1 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Violoncelle"
    \set Staff.midiInstrument = "cello"
    \clef bass
    \tempo 4 = 96
    \key c \major
    \time 4/4

    s1*0\mp
c,4 c,4 g,4 c,4 |
c,4 c,4 g,4 c,4 |
c,4 c,4 g,4 c,4 |
g,4 g,4 d,4 g,4 |
a,4 a,4 e,4 a,4 |
f,4 f,4 c,4 f,4 |
g,4 g,4 d,4 g,4 |
c,4 c,4 g,4 c,4 |
f,4 f,4 c,4 f,4 |
g,4 g,4 d,4 g,4 |
c,4 c,4 g,4 c,4 |
a,4 a,4 e,4 a,4 |
f,4 f,4 c,4 f,4 |
c,4 c,4 g,4 c,4 |
g,4 g,4 d,4 g,4 |
c,4 c,4 g,4 c,4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Guitare"
    \set Staff.midiInstrument = "acoustic guitar (nylon)"
    \clef "treble_8"
    \tempo 4 = 96
    \key c \major
    \time 4/4

    s1*0\mp
<c e g>4 <c e g>4 <c e g>4 <c e g>4 |
<c e g>4 <c e g>4 <c e g>4 <c e g>4 |
<c e g>4 <c e g>4 <c e g>4 <c e g>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
<a c' e'>4 <a c' e'>4 <a c' e'>4 <a c' e'>4 |
<f a c'>4 <f a c'>4 <f a c'>4 <f a c'>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
<c e g>4 <c e g>4 <c e g>4 <c e g>4 |
<f a c'>4 <f a c'>4 <f a c'>4 <f a c'>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
<c e g>4 <c e g>4 <c e g>4 <c e g>4 |
<a c' e'>4 <a c' e'>4 <a c' e'>4 <a c' e'>4 |
<f a c'>4 <f a c'>4 <f a c'>4 <f a c'>4 |
<c e g>4 <c e g>4 <c e g>4 <c e g>4 |
<g b d'>4 <g b d'>4 <g b d'>4 <g b d'>4 |
<c e g>4 <c e g>4 <c e g>4 <c e g>4 |
\bar "|."

  }
  \new Staff {
    \set Staff.instrumentName = "Djembe"
    \set Staff.midiInstrument = "woodblock"
    \clef percussion
    \tempo 4 = 96
    \key c \major
    \time 4/4

    s1*0\p
r8 c8 r8 f8 r8 c8 r8 g8 |
r8 c8 r8 f8 r8 c8 r8 g8 |
r8 f8 r8 g8 r8 f8 r8 g8 |
r8 c8 r8 f8 r8 c8 r8 g8 |
r8 c8 r8 f8 r8 c8 r8 g8 |
r8 f8 r8 g8 r8 f8 r8 g8 |
r8 c8 r8 f8 r8 c8 r8 g8 |
r8 f8 r8 g8 r8 f8 r8 g8 |
r8 f8 r8 g8 r8 f8 r8 g8 |
r8 c8 r8 f8 r8 c8 r8 g8 |
r8 f8 r8 g8 r8 f8 r8 g8 |
r8 c8 f8 r8 g8 f8 r8 g8 |
r8 c8 r8 f8 r8 c8 r8 g8 |
r8 f8 r8 g8 r8 f8 r8 g8 |
r8 c8 f8 r8 g8 f8 r8 g8 |
r8 c8 r8 f8 r8 c8 r8 g8 |
\bar "|."

  }
>>
  \layout { }
  \midi { }
}

