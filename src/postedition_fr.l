%{
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>

#define YY_NO_INPUT

static bool ascii_upper(char c) {
  return c >= 'A' && c <= 'Z';
}

static size_t first_token_len(const char *s) {
  size_t i = 0;
  while (s[i] == ' ' || s[i] == '\t') ++i;
  size_t start = i;
  while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '\r') ++i;
  return i - start;
}

static const char *first_token_start(const char *s) {
  while (*s == ' ' || *s == '\t') ++s;
  return s;
}

static bool token_all_caps(const char *s, size_t n) {
  bool saw_letter = false;
  for (size_t i = 0; i < n; ++i) {
    unsigned char c = static_cast<unsigned char>(s[i]);
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
      saw_letter = true;
      if (!ascii_upper(static_cast<char>(c))) return false;
    }
  }
  return saw_letter;
}

static bool token_initial_cap(const char *s, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    unsigned char c = static_cast<unsigned char>(s[i]);
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
      return ascii_upper(static_cast<char>(c));
    }
  }
  return false;
}

static const char *tail_after_last_blank(const char *s) {
  const char *tail = s;
  for (const char *p = s; *p; ++p) {
    if (*p == ' ' || *p == '\t') tail = p + 1;
  }
  return tail;
}

static void emit_cased_body(const char *source,
                            const std::string &lower,
                            const std::string &title,
                            const std::string &upper) {
  const char *token = first_token_start(source);
  size_t n = first_token_len(source);
  if (token_all_caps(token, n)) {
    std::cout << upper;
  } else if (token_initial_cap(token, n)) {
    std::cout << title;
  } else {
    std::cout << lower;
  }
}

static void emit_initial_text(const char *s) {
  if (std::strncmp(s, "à", 2) == 0) { std::cout << "À" << (s + 2); return; }
  if (std::strncmp(s, "â", 2) == 0) { std::cout << "Â" << (s + 2); return; }
  if (std::strncmp(s, "ä", 2) == 0) { std::cout << "Ä" << (s + 2); return; }
  if (std::strncmp(s, "æ", 2) == 0) { std::cout << "Æ" << (s + 2); return; }
  if (std::strncmp(s, "ç", 2) == 0) { std::cout << "Ç" << (s + 2); return; }
  if (std::strncmp(s, "é", 2) == 0) { std::cout << "É" << (s + 2); return; }
  if (std::strncmp(s, "è", 2) == 0) { std::cout << "È" << (s + 2); return; }
  if (std::strncmp(s, "ê", 2) == 0) { std::cout << "Ê" << (s + 2); return; }
  if (std::strncmp(s, "ë", 2) == 0) { std::cout << "Ë" << (s + 2); return; }
  if (std::strncmp(s, "î", 2) == 0) { std::cout << "Î" << (s + 2); return; }
  if (std::strncmp(s, "ï", 2) == 0) { std::cout << "Ï" << (s + 2); return; }
  if (std::strncmp(s, "ô", 2) == 0) { std::cout << "Ô" << (s + 2); return; }
  if (std::strncmp(s, "ö", 2) == 0) { std::cout << "Ö" << (s + 2); return; }
  if (std::strncmp(s, "œ", 2) == 0) { std::cout << "Œ" << (s + 2); return; }
  if (std::strncmp(s, "ù", 2) == 0) { std::cout << "Ù" << (s + 2); return; }
  if (std::strncmp(s, "û", 2) == 0) { std::cout << "Û" << (s + 2); return; }
  if (std::strncmp(s, "ü", 2) == 0) { std::cout << "Ü" << (s + 2); return; }
  if (std::strncmp(s, "ÿ", 2) == 0) { std::cout << "Ÿ" << (s + 2); return; }
  unsigned char c = static_cast<unsigned char>(s[0]);
  if (c >= 'a' && c <= 'z') {
    std::cout << static_cast<char>(std::toupper(c)) << (s + 1);
  } else {
    std::cout << s;
  }
}

static void emit_initial_replacement_with_tail(const char *source,
                                               const std::string &lower,
                                               const std::string &title,
                                               const std::string &upper) {
  emit_cased_body(source, title, title, upper);
  std::cout << tail_after_last_blank(source);
}

static void emit_inner_replacement_with_tail(const char *source,
                                             const std::string &lower,
                                             const std::string &title,
                                             const std::string &upper) {
  std::cout << ' ';
  emit_cased_body(source + 1, lower, title, upper);
  std::cout << tail_after_last_blank(source);
}

static void emit_inner_replacement(const char *source,
                                   const std::string &lower,
                                   const std::string &title,
                                   const std::string &upper) {
  std::cout << ' ';
  emit_cased_body(source + 1, lower, title, upper);
}
%}

%option noyywrap
%option 8bit

%s NEXT

A       [aAàÀâÂäÄ]
B       [bB]
C       [cCçÇ]
D       [dD]
E       [eEéÉèÈêÊëË]
F       [fF]
G       [gG]
H       [hH]
I       [iIîÎïÏ]
J       [jJ]
K       [kK]
L       [lL]
M       [mM]
N       [nN]
O       [oOôÔöÖ]
P       [pP]
Q       [qQ]
R       [rR]
S       [sS]
T       [tT]
U       [uUùÙûÛüÜ]
V       [vV]
W       [wW]
X       [xX]
Y       [yYÿŸ]
Z       [zZ]
AE      (æ|Æ)
OE      (œ|Œ)
VOY     ({A}|{E}|{I}|{O}|{U}|{Y}|{AE}|{OE})
ELISION ({VOY}|{H})
SP      [ \t]+

HACHE       {H}{A}{C}{H}{E}{S}?
HAIE        {H}{A}{I}{E}{S}?
HAILLON     {H}{A}{I}{L}{L}{O}{N}{S}?
HAINE       {H}{A}{I}{N}{E}{S}?
HAIR        {H}{A}(ï|Ï|{I}){R}
HALAGE      {H}{A}{L}{A}{G}{E}
HALE        {H}{A}{L}{E}{S}?
HALL        {H}{A}{L}{L}{S}?
HALLE       {H}{A}{L}{L}{E}{S}?
HALTE       {H}{A}{L}{T}{E}{S}?
HAMAC       {H}{A}{M}{A}{C}{S}?
HAMEAU      {H}{A}{M}{E}{A}{U}{X}?
HAMPE       {H}{A}{M}{P}{E}{S}?
HAMSTER     {H}{A}{M}{S}{T}{E}{R}{S}?
HANCHE      {H}{A}{N}{C}{H}{E}{S}?
HANDICAP    {H}{A}{N}{D}{I}{C}{A}{P}{S}?
HANDICAPE   {H}{A}{N}{D}{I}{C}{A}{P}{E}{S}?
HANGAR      {H}{A}{N}{G}{A}{R}{S}?
HANNETON    {H}{A}{N}{N}{E}{T}{O}{N}{S}?
HANSARD     {H}{A}{N}{S}{A}{R}{D}{S}?
HANTISE     {H}{A}{N}{T}{I}{S}{E}{S}?
HARANGUE    {H}{A}{R}{A}{N}{G}{U}{E}{S}?
HARAS       {H}{A}{R}{A}{S}
HARCELER    {H}{A}{R}{C}{E}{L}{E}{R}
HARDI       {H}{A}{R}{D}{I}{E}?{S}?
HARENG      {H}{A}{R}{E}{N}{G}{S}?
HARGNE      {H}{A}{R}{G}{N}{E}{S}?
HARICOT     {H}{A}{R}{I}{C}{O}{T}{S}?
HARNAIS     {H}{A}{R}{N}{A}{I}{S}
HARPE       {H}{A}{R}{P}{E}{S}?
HASARD      {H}{A}{S}{A}{R}{D}{S}?
HATE        {H}{A}({T}|{T}{E}){S}?
HAUBAN      {H}{A}{U}{B}{A}{N}{S}?
HAUSSE      {H}{A}{U}{S}{S}{E}{S}?
HAUT        {H}{A}{U}{T}{E}?{S}?
HAUTEUR     {H}{A}{U}{T}{E}{U}{R}{S}?
HAVANE      {H}{A}{V}{A}{N}{E}{S}?
HAVRE       {H}{A}{V}{R}{E}{S}?
HERISSON    {H}{E}{R}{I}{S}{S}{O}{N}{S}?
HERON       {H}{E}{R}{O}{N}{S}?
HEROS       {H}{E}{R}{O}{S}
HETRE       {H}{E}{T}{R}{E}{S}?
HIBOU       {H}{I}{B}{O}{U}{X}?
HIE         {H}{I}{E}{S}?
HIERARCHIE  {H}{I}{E}{R}{A}{R}{C}{H}{I}{E}{S}?
HIPPIE      {H}{I}{P}{P}{I}{E}{S}?
HOBBY       {H}{O}{B}{B}{Y}{S}?
HOCHET      {H}{O}{C}{H}{E}{T}{S}?
HOCKEY      {H}{O}{C}{K}{E}{Y}
HOLLANDE    {H}{O}{L}{L}{A}{N}{D}{E}
HOLLANDAIS  {H}{O}{L}{L}{A}{N}{D}{A}{I}{S}{E}?{S}?
HOMARD      {H}{O}{M}{A}{R}{D}{S}?
HONTE       {H}{O}{N}{T}{E}{S}?
HOQUET      {H}{O}{Q}{U}{E}{T}{S}?
HORDE       {H}{O}{R}{D}{E}{S}?
HORS        {H}{O}{R}{S}
HOUILLE     {H}{O}{U}{I}{L}{L}{E}{S}?
HOULE       {H}{O}{U}{L}{E}{S}?
HOULETTE    {H}{O}{U}{L}{E}{T}{T}{E}{S}?
HOUPPE      {H}{O}{U}{P}{P}{E}{S}?
HOUSSE      {H}{O}{U}{S}{S}{E}{S}?
HUBLOT      {H}{U}{B}{L}{O}{T}{S}?
HUCHE       {H}{U}{C}{H}{E}{S}?
HUGUENOT    {H}{U}{G}{U}{E}{N}{O}{T}{E}?{S}?
HUIT        {H}{U}{I}{T}
HUITAINE    {H}{U}{I}{T}{A}{I}{N}{E}{S}?
HULOTTE     {H}{U}{L}{O}{T}{T}{E}{S}?
HUNE        {H}{U}{N}{E}{S}?
HURE        {H}{U}{R}{E}{S}?
HURLEMENT   {H}{U}{R}{L}{E}{M}{E}{N}{T}{S}?
HURLER      {H}{U}{R}{L}{E}{R}
HUSSARD     {H}{U}{S}{S}{A}{R}{D}{S}?
HUTTE       {H}{U}{T}{T}{E}{S}?
H_ASPIRE    ({HACHE}|{HAIE}|{HAILLON}|{HAINE}|{HAIR}|{HALAGE}|{HALE}|{HALL}|{HALLE}|{HALTE}|{HAMAC}|{HAMEAU}|{HAMPE}|{HAMSTER}|{HANCHE}|{HANDICAP}|{HANDICAPE}|{HANGAR}|{HANNETON}|{HANSARD}|{HANTISE}|{HARANGUE}|{HARAS}|{HARCELER}|{HARDI}|{HARENG}|{HARGNE}|{HARICOT}|{HARNAIS}|{HARPE}|{HASARD}|{HATE}|{HAUBAN}|{HAUSSE}|{HAUT}|{HAUTEUR}|{HAVANE}|{HAVRE}|{HERISSON}|{HERON}|{HEROS}|{HETRE}|{HIBOU}|{HIE}|{HIERARCHIE}|{HIPPIE}|{HOBBY}|{HOCHET}|{HOCKEY}|{HOLLANDE}|{HOLLANDAIS}|{HOMARD}|{HONTE}|{HOQUET}|{HORDE}|{HORS}|{HOUILLE}|{HOULE}|{HOULETTE}|{HOUPPE}|{HOUSSE}|{HUBLOT}|{HUCHE}|{HUGUENOT}|{HUIT}|{HUITAINE}|{HULOTTE}|{HUNE}|{HURE}|{HURLEMENT}|{HURLER}|{HUSSARD}|{HUTTE})
mesure          mm|cm|m|dm|km|m2|m3|A|[oO]hm|V|VA|gr|[kK]g

%%

<INITIAL>[ \t]+                                      { }
<INITIAL>[lL][eEaA]{SP}{H_ASPIRE}                    { emit_initial_text(yytext); BEGIN(NEXT); }
<INITIAL>[dD][eE]{SP}{H_ASPIRE}                      { emit_initial_text(yytext); BEGIN(NEXT); }
<INITIAL>[jJ][eE]{SP}{H_ASPIRE}                      { emit_initial_text(yytext); BEGIN(NEXT); }
<INITIAL>[nN][eE]{SP}{H_ASPIRE}                      { emit_initial_text(yytext); BEGIN(NEXT); }
<INITIAL>[mMtTsS][eE]{SP}{H_ASPIRE}                  { emit_initial_text(yytext); BEGIN(NEXT); }
<INITIAL>[mMtTsS][aA]{SP}{H_ASPIRE}                  { emit_initial_text(yytext); BEGIN(NEXT); }
<INITIAL>[qQ][uU][eE]{SP}{H_ASPIRE}                  { emit_initial_text(yytext); BEGIN(NEXT); }
<INITIAL>[cC][eE]{SP}{H_ASPIRE}                      { emit_initial_text(yytext); BEGIN(NEXT); }
<INITIAL>[bB][eE][aA][uU]{SP}{H_ASPIRE}              { emit_initial_text(yytext); BEGIN(NEXT); }
<INITIAL>[nN][oO][uU][vV][eE][aA][uU]{SP}{H_ASPIRE}  { emit_initial_text(yytext); BEGIN(NEXT); }
<INITIAL>[vV][iI][eE][uU][xX]{SP}{H_ASPIRE}          { emit_initial_text(yytext); BEGIN(NEXT); }
<INITIAL>[sS][iI]{SP}{H_ASPIRE}                      { emit_initial_text(yytext); BEGIN(NEXT); }
<INITIAL>[dD][eE]{SP}[lL][eEaA]{SP}{ELISION}         { emit_initial_replacement_with_tail(yytext, "de l'", "De l'", "DE L'"); BEGIN(NEXT); }
<INITIAL>"à"{SP}[lL][eEaA]{SP}{ELISION}             { emit_initial_replacement_with_tail(yytext, "à l'", "À l'", "À L'"); BEGIN(NEXT); }
<INITIAL>"À"{SP}[lL][eEaA]{SP}{ELISION}             { emit_initial_replacement_with_tail(yytext, "à l'", "À l'", "À L'"); BEGIN(NEXT); }
<INITIAL>[dD][eE]{SP}[lL][eE][sS]                   { emit_cased_body(yytext, "Des", "Des", "DES"); BEGIN(NEXT); }
<INITIAL>[dD][eE]{SP}[lL][eE]                       { emit_cased_body(yytext, "Du", "Du", "DU"); BEGIN(NEXT); }
<INITIAL>"à"{SP}[lL][eE][sS]                       { std::cout << "Aux"; BEGIN(NEXT); }
<INITIAL>"À"{SP}[lL][eE][sS]                       { std::cout << "Aux"; BEGIN(NEXT); }
<INITIAL>"à"{SP}[lL][eE]                           { std::cout << "Au"; BEGIN(NEXT); }
<INITIAL>"À"{SP}[lL][eE]                           { std::cout << "Au"; BEGIN(NEXT); }
<INITIAL>[nNdDjJlL][eEaA]{SP}{ELISION}              { emit_initial_replacement_with_tail(yytext, "l'", "L'", "L'"); BEGIN(NEXT); }
<INITIAL>[mMtTsS][eE]{SP}{ELISION}                  { emit_initial_replacement_with_tail(yytext, "m'", "M'", "M'"); BEGIN(NEXT); }
<INITIAL>[qQ][uU][eE]{SP}{ELISION}                  { emit_initial_replacement_with_tail(yytext, "qu'", "Qu'", "QU'"); BEGIN(NEXT); }
<INITIAL>[sS][iI]{SP}{I}                            { emit_initial_replacement_with_tail(yytext, "s'", "S'", "S'"); BEGIN(NEXT); }
<INITIAL>[mM][aA]{SP}{ELISION}                      { emit_initial_replacement_with_tail(yytext, "mon ", "Mon ", "MON "); BEGIN(NEXT); }
<INITIAL>[tT][aA]{SP}{ELISION}                      { emit_initial_replacement_with_tail(yytext, "ton ", "Ton ", "TON "); BEGIN(NEXT); }
<INITIAL>[sS][aA]{SP}{ELISION}                      { emit_initial_replacement_with_tail(yytext, "son ", "Son ", "SON "); BEGIN(NEXT); }
<INITIAL>[cC][eE]{SP}{ELISION}                      { emit_initial_replacement_with_tail(yytext, "cet ", "Cet ", "CET "); BEGIN(NEXT); }
<INITIAL>[bB][eE][aA][uU]{SP}{ELISION}              { emit_initial_replacement_with_tail(yytext, "bel ", "Bel ", "BEL "); BEGIN(NEXT); }
<INITIAL>[nN][oO][uU][vV][eE][aA][uU]{SP}{ELISION}  { emit_initial_replacement_with_tail(yytext, "nouvel ", "Nouvel ", "NOUVEL "); BEGIN(NEXT); }
<INITIAL>[vV][iI][eE][uU][xX]{SP}{ELISION}          { emit_initial_replacement_with_tail(yytext, "vieil ", "Vieil ", "VIEIL "); BEGIN(NEXT); }
<INITIAL>"à"                                       { std::cout << "À"; BEGIN(NEXT); }
<INITIAL>"â"                                       { std::cout << "Â"; BEGIN(NEXT); }
<INITIAL>"ä"                                       { std::cout << "Ä"; BEGIN(NEXT); }
<INITIAL>"æ"                                       { std::cout << "Æ"; BEGIN(NEXT); }
<INITIAL>"ç"                                       { std::cout << "Ç"; BEGIN(NEXT); }
<INITIAL>"é"                                       { std::cout << "É"; BEGIN(NEXT); }
<INITIAL>"è"                                       { std::cout << "È"; BEGIN(NEXT); }
<INITIAL>"ê"                                       { std::cout << "Ê"; BEGIN(NEXT); }
<INITIAL>"ë"                                       { std::cout << "Ë"; BEGIN(NEXT); }
<INITIAL>"î"                                       { std::cout << "Î"; BEGIN(NEXT); }
<INITIAL>"ï"                                       { std::cout << "Ï"; BEGIN(NEXT); }
<INITIAL>"ô"                                       { std::cout << "Ô"; BEGIN(NEXT); }
<INITIAL>"ö"                                       { std::cout << "Ö"; BEGIN(NEXT); }
<INITIAL>"œ"                                       { std::cout << "Œ"; BEGIN(NEXT); }
<INITIAL>"ù"                                       { std::cout << "Ù"; BEGIN(NEXT); }
<INITIAL>"û"                                       { std::cout << "Û"; BEGIN(NEXT); }
<INITIAL>"ü"                                       { std::cout << "Ü"; BEGIN(NEXT); }
<INITIAL>"ÿ"                                       { std::cout << "Ÿ"; BEGIN(NEXT); }
<INITIAL>[a-z]                                      { std::cout << static_cast<char>(std::toupper(static_cast<unsigned char>(yytext[0]))); BEGIN(NEXT); }
<INITIAL>.                                          { ECHO; BEGIN(NEXT); }

<NEXT>[ \t]+[lL][eEaA]{SP}{H_ASPIRE}                    { ECHO; }
<NEXT>[ \t]+[dD][eE]{SP}{H_ASPIRE}                      { ECHO; }
<NEXT>[ \t]+[jJ][eE]{SP}{H_ASPIRE}                      { ECHO; }
<NEXT>[ \t]+[nN][eE]{SP}{H_ASPIRE}                      { ECHO; }
<NEXT>[ \t]+[mMtTsS][eE]{SP}{H_ASPIRE}                  { ECHO; }
<NEXT>[ \t]+[mMtTsS][aA]{SP}{H_ASPIRE}                  { ECHO; }
<NEXT>[ \t]+[qQ][uU][eE]{SP}{H_ASPIRE}                  { ECHO; }
<NEXT>[ \t]+[cC][eE]{SP}{H_ASPIRE}                      { ECHO; }
<NEXT>[ \t]+[bB][eE][aA][uU]{SP}{H_ASPIRE}              { ECHO; }
<NEXT>[ \t]+[nN][oO][uU][vV][eE][aA][uU]{SP}{H_ASPIRE}  { ECHO; }
<NEXT>[ \t]+[vV][iI][eE][uU][xX]{SP}{H_ASPIRE}          { ECHO; }
<NEXT>[ \t]+[sS][iI]{SP}{H_ASPIRE}                      { ECHO; }
<NEXT>[ \t]+[dD][eE]{SP}[lL][eEaA]{SP}{ELISION}         { emit_inner_replacement_with_tail(yytext, "de l'", "De l'", "DE L'"); }
<NEXT>[ \t]+"à"{SP}[lL][eEaA]{SP}{ELISION}             { std::cout << " à l'" << tail_after_last_blank(yytext); }
<NEXT>[ \t]+"À"{SP}[lL][eEaA]{SP}{ELISION}             { std::cout << " À l'" << tail_after_last_blank(yytext); }
<NEXT>[ \t]+[dD][eE]{SP}[lL][eE][sS]                   { emit_inner_replacement(yytext, "des", "Des", "DES"); }
<NEXT>[ \t]+[dD][eE]{SP}[lL][eE]                       { emit_inner_replacement(yytext, "du", "Du", "DU"); }
<NEXT>[ \t]+"à"{SP}[lL][eE][sS]                       { std::cout << " aux"; }
<NEXT>[ \t]+"À"{SP}[lL][eE][sS]                       { std::cout << " Aux"; }
<NEXT>[ \t]+"à"{SP}[lL][eE]                           { std::cout << " au"; }
<NEXT>[ \t]+"À"{SP}[lL][eE]                           { std::cout << " Au"; }
<NEXT>[ \t]+[nNdDjJlL][eEaA]{SP}{ELISION}              { emit_inner_replacement_with_tail(yytext, "l'", "L'", "L'"); }
<NEXT>[ \t]+[mMtTsS][eE]{SP}{ELISION}                  { emit_inner_replacement_with_tail(yytext, "m'", "M'", "M'"); }
<NEXT>[ \t]+[qQ][uU][eE]{SP}{ELISION}                  { emit_inner_replacement_with_tail(yytext, "qu'", "Qu'", "QU'"); }
<NEXT>[ \t]+[sS][iI]{SP}{I}                            { emit_inner_replacement_with_tail(yytext, "s'", "S'", "S'"); }
<NEXT>[ \t]+[mM][aA]{SP}{ELISION}                      { emit_inner_replacement_with_tail(yytext, "mon ", "Mon ", "MON "); }
<NEXT>[ \t]+[tT][aA]{SP}{ELISION}                      { emit_inner_replacement_with_tail(yytext, "ton ", "Ton ", "TON "); }
<NEXT>[ \t]+[sS][aA]{SP}{ELISION}                      { emit_inner_replacement_with_tail(yytext, "son ", "Son ", "SON "); }
<NEXT>[ \t]+[cC][eE]{SP}{ELISION}                      { emit_inner_replacement_with_tail(yytext, "cet ", "Cet ", "CET "); }
<NEXT>[ \t]+[bB][eE][aA][uU]{SP}{ELISION}              { emit_inner_replacement_with_tail(yytext, "bel ", "Bel ", "BEL "); }
<NEXT>[ \t]+[nN][oO][uU][vV][eE][aA][uU]{SP}{ELISION}  { emit_inner_replacement_with_tail(yytext, "nouvel ", "Nouvel ", "NOUVEL "); }
<NEXT>[ \t]+[vV][iI][eE][uU][xX]{SP}{ELISION}          { emit_inner_replacement_with_tail(yytext, "vieil ", "Vieil ", "VIEIL "); }
<NEXT>[0-9][ \t]+{mesure}[ \t]+                        { yytext[yyleng-1] = 0; ECHO; }
<NEXT>[-][ \t]+                                         { yytext[yyleng-1] = 0; ECHO; }
<NEXT>[ \t]+[,.;:!?)]                                   { char c = yytext[yyleng-1]; std::cout << c; if (c == '.' || c == '!' || c == '?') BEGIN(INITIAL); }
<NEXT>[ \t]+                                            { std::cout << ' '; }
<NEXT>\n                                                { ECHO; BEGIN(INITIAL); }
<NEXT>.                                                 { ECHO; }

%%

int main() {
  yylex();
  return 0;
}
