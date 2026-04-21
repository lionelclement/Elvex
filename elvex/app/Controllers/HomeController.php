<?php

require_once __DIR__ . '/../Core/View.php';
require_once __DIR__ . '/../Models/Project.php';
require_once __DIR__ . '/../Lib/Parsedown.php';

class HomeController
{
    public function index(): void
    {
        $selectedProject = null;
        $exampleProjects = $this->exampleProjects();

        if (!is_logged_in()) {
            $projects = $exampleProjects;

            if (isset($_GET['project'])) {
                $requestedId = (string) $_GET['project'];
                foreach ($projects as $project) {
                    if ((string) $project['id'] === $requestedId) {
                        $selectedProject = $project;
                        break;
                    }
                }
            }

            if ($selectedProject === null && !empty($projects)) {
                $selectedProject = $projects[0];
            }

            View::render('home', [
                'projects' => $projects,
                'selectedProject' => $selectedProject
            ]);
            return;
        }

        $userProjects = Project::allByUser((int) current_user()['id']);

        // exemples + projets utilisateur
        $projects = array_merge($exampleProjects, $userProjects);

        if (isset($_GET['project'])) {
            $requestedId = (string) $_GET['project'];

            foreach ($projects as $project) {
                if ((string) $project['id'] === $requestedId) {
                    $selectedProject = $project;
                    break;
                }
            }
        }

        View::render('home', [
            'projects' => $projects,
            'selectedProject' => $selectedProject
        ]);
    }

    public function home(): void
    {
        $file = __DIR__ . '/../../README.md';
        $markdown = is_file($file)
            ? file_get_contents($file)
            : "# Home\n\nREADME.md not found.";

        $parser = new Parsedown();
        $html = $parser->text($markdown);

        View::render('simple_page', [
            'title' => 'Home',
            'html' => $html
        ]);
    }

    public function documentation(): void
    {
        $file = __DIR__ . '/../../DOCUMENTATION.md';
        $markdown = is_file($file)
            ? file_get_contents($file)
            : "# Documentation\n\nDOCUMENTATION.md not found.";

        $parser = new Parsedown();
        $html = $parser->text($markdown);

        View::render('simple_page', [
            'title' => 'Documentation',
            'html' => $html
        ]);
    }

    private function exampleProjects(): array
    {
        return [
            [
                'id' => 'example-1',
                'name' => 'Minimal simple sentence in English',
                'macros' => '',
                'rules' => <<<'EOT'
S → NP VP
{
  [i:$i];
  ↓1 = $i;
  [number:$number, person:$person] ⊂ ⇓1;
  ↓2 = ↑ U [SUBJ:[number:$number, person:$person]];
}

NP → det N
{
  ↓2 = ↑;
  ↓1 = ↑ U ⇓2;
  ⇑ = ⇓1 U ⇓2 U [person:3];
}

N → noun
{
  [mod:NIL];
  ↓1 = ↑;
  ⇑ = ⇓1;
}

VP → verb
{
  ↓1 = ↑;
  ⇑ = ⇓1;
}

EOT,
                'lexicon' => <<<'EOT'
the det	[definite:yes];
dog	noun	[HEAD:DOG, number:singular, person:3];
barks	verb	[HEAD:TO_BARK, SUBJ:[number:singular, person:3]];
EOT,
                'pattern' => '',
                'morpho' => '',
                'post_morpho' => '',
                'input_text' => "S [HEAD:TO_BARK, i:[HEAD:DOG]]",
                'is_example' => true,
            ],
            [
                'id' => 'example-2',
                'name' => 'Particle verb in English',
                'macros' => <<<'EOT'
@s= [number:singular];
@p= [number:plural];
@P1s=	[TENSE:present, MOOD:indicative, SUBJ:[@s, person:1]];
@P2s=	[TENSE:present, MOOD:indicative, SUBJ:[@s, person:2]];
@P3s=	[TENSE:present, MOOD:indicative, SUBJ:[@s, person:3]];
@P3p=	[TENSE:present, MOOD:indicative, SUBJ:[@p, person:3]];
@animate=    [restriction:[animate:yes]];

EOT,
                'rules' => <<<'EOT'
S → NP VP
{
  [i:$i, $rest];
  ↓1 = $i;
  [number:$number, person:$person] ⊂ ⇓1;
  ↓2 = $rest U [SUBJ:[number:$number, person:$person]];
}

NP → det N
{
  ↓2 = ↑;
  ↓1 = ↑ U ⇓2;
  ⇑ = ⇓1 U ⇓2 U [person:3];
}

N → noun
{
  [mod:NIL];
  ↓1 = ↑;
  ⇑ = ⇓1;
}

VP → V NP
{
  [ii:$ii, $rest];
  ↓1 = $rest U [OBJ:$ii];
  ↓2 = $ii;
}


V → verb part
{
  ↓1 = ↑;
  [particle:$particle] ⊂ ⇓1;
  ↓2 = [particle:$particle];
}

VP → verb NP part
{
  [ii:$ii, $rest];
  ↓1 = $rest U [OBJ:$ii, separable_particle:yes];
  ↓2 = $ii;
  [particle:$p] ⊂ ⇓1;
  ↓3 = [particle:$p];
}

EOT,
                'lexicon' => <<<'EOT'
the		det     [definite:yes];
""		det     [definite:no, @p];
up		part    [particle:up];
after	part    [particle:after];
EOT,
                'pattern' => <<<'EOT'
// LEXEME	POS	LEMMA	FEATURES
GIRL	noun	GIRL	[restriction:[animate:yes]]
CHILD	noun	CHILD	[restriction:[animate:yes]]
WORD	noun	WORD	[restriction:[animate:no]]
LOOK_UP	verb	TO_LOOK	[particle:up, separable_particle:yes, OBJ:[]]
LOOK_AFTER	verb	TO_LOOK	[particle:after, separable_particle:no, OBJ:[restriction:[animate:yes]]]
EOT,
                'morpho' => <<<'EOT'
// FORM    POS	LEMMA	FEATURES
girl	noun	GIRL	[@s]
girls	noun	GIRL	[@p]
child	noun	CHILD	[@s]
children	noun	CHILD	[@p]
word	noun	WORD	[@s]
words	noun	WORD	[@p]
look	verb	TO_LOOK	[@P1s]
look	verb	TO_LOOK	[@P2s]
looks	verb	TO_LOOK	[@P3s]
look	verb	TO_LOOK	[@P3p]
EOT,
                'post_morpho' => '',
                'input_text' => <<<'EOT'
//S [HEAD:LOOK_UP, i:[HEAD:GIRL], ii:[HEAD:WORD]]
S [HEAD:LOOK_AFTER, i:[HEAD:GIRL], ii:[HEAD:CHILD]]

EOT, 
               'is_example' => true,
            ],
            [
                'id' => 'example-3',
                'name' => 'Complete example',
                'macros' => <<<'EOT'
// @MACRO= FEATURES;
@s=	[number:singular];
@p=	[number:plural];
@m=	[gender:masc];
@f=	[gender:fem];
@ms= [@m, @s];
@mp= [@m, @p];
@fs= [@f, @s];
@fp= [@f, @p];
@_1=	[person:one];
@_2=	[person:two];
@_12=	[person:one|two];
@_3=	[person:three];
@_1s=	[@_1, @s];
@_2s=	[@_2, @s];
@_12s=	[@_12, @s];
@_3s=	[@_3, @s];
@_1p=	[@_1, @p];
@_2p=	[@_2, @p];
@_3p=	[@_3, @p];
@_3ms=	[@_3, @m, @s];
@_3fs=	[@_3, @f, @s];
@_3mp=	[@_3, @m, @p];
@_3fp=	[@_3, @f, @p];
@indicatif_present=	[MOOD:indicatif, TENSE:present];
@indicatif_imparfait=	[MOOD:indicatif, TENSE:imparfait];
@indicatif_passe_simple=	[MOOD:indicatif, TENSE:passe_simple];
@indicatif_futur_simple=	[MOOD:indicatif, TENSE:futur_simple];
@def=    [definite:yes];
@no_def=    [definite:no];
EOT,
                'rules' => <<<'EOT'
// PHRASE → SYNTACTIC DESCRIPTION
S → NP|cln VP dot
{
  [i:$i];
  ↓1 = $i;
  [number:$number, person:$person, selectional_restriction:$selectional_restriction] ⊂ ⇓1;
  ↓2 = ↑ U [SUBJ:[number:$number, person:$person, selectional_restriction:$selectional_restriction]];
  ↓3 = [];
}

NP → det N
{
  ↓2 = ↑;
  ↓1 = ↑ U ⇓2;
  ⇑ = ⇓1 U ⇓2 U [@_3];
}

N → noun
{
  [mod:NIL];
  ↓1 = ↑;
  ⇑ = ⇓1;
}

VP → verb
{
  ↓1 = ↑;
  ⇑ = ⇓1;
}
EOT,
                'lexicon' => <<<'EOT'
// FORM	POS	FEATURES;
"." dot;

un	det [@ms, @no_def, dem:no, poss:no, part:no];
une	det [@fs, @no_def, dem:no, poss:no, part:no];
des	det [@p, @no_def, qual:no, dem:no, poss:no, part:no];

le	det [@ms, @def, dem:no, poss:no, part:no];
la	det [@fs, @def, dem:no, poss:no, part:no];
les	det [@p, @def, qual:no, dem:no, poss:no, part:no];

mon	det [@ms, @no_def, poss:yes, part:no, dem:no, personPoss:one, numberPoss:sg];
ma	det [@fs, @no_def, poss:yes, part:no, dem:no, personPoss:one, numberPoss:sg];
mes	det [@p, @no_def, poss:yes, part:no, dem:no, personPoss:one, numberPoss:sg];
ton	det [@ms, @no_def, poss:yes, part:no, dem:no, personPoss:two, numberPoss:sg];
ta	det [@fs, @no_def, poss:yes, part:no, dem:no, personPoss:two, numberPoss:sg];
tes	det [@p, @no_def, poss:yes, part:no, dem:no, personPoss:two, numberPoss:sg];
son	det [@ms, @no_def, poss:yes, part:no, dem:no, personPoss:three, numberPoss:sg];
sa	det [@fs, @no_def, poss:yes, part:no, dem:no, personPoss:three, numberPoss:sg];
ses	det [@p, @no_def, poss:yes, part:no, dem:no, personPoss:three, numberPoss:sg];
notre	det [@ms, @no_def, poss:yes, part:no, dem:no, personPoss:one, numberPoss:pl];
nos	det [@p, @no_def, poss:yes, part:no, dem:no, personPoss:one, numberPoss:pl];
votre	det [@ms, @no_def, poss:yes, part:no, dem:no, personPoss:two, numberPoss:pl];
vos	det [@p, @no_def, poss:yes, part:no, dem:no, personPoss:two, numberPoss:pl];
leur	det [@ms, @no_def, poss:yes, part:no, dem:no, personPoss:three, numberPoss:pl];
leurs	det [@p, @no_def, poss:yes, part:no, dem:no, personPoss:three, numberPoss:pl];

ce	det [@ms, @no_def, poss:no, dem:yes, part:no];
ces	det [@p, @no_def, poss:no, dem:yes, part:no];
cette	det [@fs, @no_def, poss:no, dem:yes, part:no];

je	cln [HEAD:_pro, @_1s, clitic:yes];
tu	cln [HEAD:_pro, @_2s, clitic:yes];
il	cln [HEAD:_pro, @_3ms, clitic:yes];
elle	cln [HEAD:_pro, @_3fs, clitic:yes];
nous	cln [HEAD:_pro, @_1p, clitic:yes];
vous	cln [HEAD:_pro, @_2p, clitic:yes];
ils	cln [HEAD:_pro, @_3mp, clitic:yes];
elles	cln [HEAD:_pro, @_3fp, clitic:yes];
EOT,
                'pattern' => <<<'EOT'
// LEXEME	POS	LEMMA	FEATURES
//
// generic lexeme: ANIMAL
// specific lexeme: DOG, CAT, etc.
//
// ==========================
// DOMESTIC ANIMALS
// ==========================
//
ANIMAL	noun	CHIEN	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:aboyer | japper | hurler]]
ANIMAL	noun	CHIOT	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:aboyer | japper]]
CHIEN	noun	CHIEN	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:aboyer | japper | hurler]]
CHIEN	noun	CHIOT	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:aboyer | japper]]
//
ANIMAL	noun	CHAT	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:miauler]]
//
ANIMAL	noun	VACHE	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:meugler]]
ANIMAL	noun	BOEUF	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:meugler]]
ANIMAL	noun	TAUREAU	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:meugler]]
//
ANIMAL	noun	CHEVAL	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:hennir]]
ANIMAL	noun	JUMENT	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:hennir]]
ANIMAL	noun	ETALON	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:hennir]]
ANIMAL	noun	ONGRE	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:hennir]]
ANIMAL	noun	ANE	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:braire]]
//
ANIMAL	noun	MOUTON	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:beler]]
ANIMAL	noun	BREBIS	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:beler]]
ANIMAL	noun	AGNEAU	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:beler]]
ANIMAL	noun	CHEVRE	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:beler]]
//
ANIMAL	noun	POULE	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:caqueter]]
ANIMAL	noun	COQ	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:chanter]]
ANIMAL	noun	OIE	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:cacarder]]
ANIMAL	noun	DINDON	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:glouglouter]]
ANIMAL	noun	CANARD	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:cancaner]]
//
ANIMAL	noun	HAMSTER	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:couiner]]
ANIMAL	noun	LAPIN	[selectional_restriction:[animate:yes, animal:yes, domestic:yes, sound:couiner]]
//
// ==========================
// WILD ANIMALS
// ==========================
//
ANIMAL	noun	CHAUVE_SOURIS	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:piauler | couiner | crier]]
//
ANIMAL	noun	LOUP	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:hurler]]
ANIMAL	noun	COYOTE	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:hurler]]
ANIMAL	noun	CHACAL	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:hurler]]
//
ANIMAL	noun	LION	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:rugir]]
ANIMAL	noun	TIGRE	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:rugir]]
ANIMAL	noun	LEOPARD	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:rugir]]
ANIMAL	noun	JAGUAR	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:rugir]]
ANIMAL	noun	OURS	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:rugir]]
//
ANIMAL	noun	SERPENT	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:siffler]]
//
ANIMAL	noun	CERF	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:bramer]]
//
ANIMAL	noun	CHEVREUIL	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:bramer | raire]]
//
ANIMAL	noun	SANGLIER	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:grogner]]
//
ANIMAL	noun	RENARD	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:glapir]]
//
ANIMAL	noun	HIBOU	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:hululer]]
ANIMAL	noun	CHOUETTE	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:hululer]]
//
ANIMAL	noun	CORBEAU	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:croasser]]
ANIMAL	noun	CORNEILLE	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:croasser]]
//
ANIMAL	noun	GRENOUILLE	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:coasser]]
//
ANIMAL	noun	OISEAU	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:gazouiller]]
ANIMAL	noun	MOINEAU	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:gazouiller]]
ANIMAL	noun	MESANGE	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:gazouiller]]
//
ANIMAL	noun	SOURIS	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:couiner]]
ANIMAL	noun	RAT	[selectional_restriction:[animate:yes, animal:yes, wild:yes, sound:couiner]]
//
//
CRIER	verb	ABOYER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:aboyer]]]
ABOYER	verb	ABOYER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:aboyer]]]
//
CRIER	verb	CRIER	[SUBJ:[selectional_restriction:[animate:yes, sound:crier]]]
CRIER	verb	SIFFLER	[SUBJ:[selectional_restriction:[animate:yes, sound:siffler]]]
CRIER	verb	GROGNER	[SUBJ:[selectional_restriction:[animate:yes, sound:grogner]]]
//
CRIER	verb	MEUGLER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:meugler]]]
CRIER	verb	JAPPER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:japper]]]
CRIER	verb	MIAULER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:miauler]]]
CRIER	verb	HENNIR	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:hennir]]]
CRIER	verb	BELER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:beler]]]
CRIER	verb	CAQUETER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:caqueter]]]
CRIER	verb	CHANTER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:chanter]]]
CRIER	verb	CACARDER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:cacarder]]]
CRIER	verb	GLOUGLOUTER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:glouglouter]]]
CRIER	verb	CANCANER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:cancaner]]]
CRIER	verb	COUINER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:couiner]]]
CRIER	verb	BRAIRE	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:braire]]]
CRIER	verb	HURLER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:hurler]]]
CRIER	verb	PIAULER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:piauler]]]
CRIER	verb	RUGIR	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:rugir]]]
CRIER	verb	BRAMER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:bramer]]]
CRIER	verb	RAIRE	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:raire]]]
CRIER	verb	GLAPIR	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:glapir]]]
CRIER	verb	HULULER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:hululer]]]
CRIER	verb	CROASSER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:croasser]]]
CRIER	verb	COASSER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:coasser]]]
CRIER	verb	GAZOUILLER	[SUBJ:[selectional_restriction:[animate:yes, animal:yes, sound:gazouiller]]]
//
EOT,
                'morpho' => <<<'EOT'
// FORM    POS	LEMMA	FEATURES
//
souris	noun	SOURIS	[@f]
//
chat	noun	CHAT	[@ms]
chatte	noun	CHAT	[@fs]
chats	noun	CHAT	[@mp]
chattes	noun	CHAT	[@fp]
//
chien	noun	CHIEN	[@ms]
chienne	noun	CHIEN	[@fs]
chiens	noun	CHIEN	[@mp]
chiennes	noun	CHIEN	[@fp]
//
chiot	noun	CHIOT	[@ms]
chiots	noun	CHIOT	[@mp]
//
poule	noun	POULE	[@fs]
poules	noun	POULE	[@fp]
coq	noun	COQ	[@ms]
coqs	noun	COQ	[@mp]
oie	noun	OIE	[@fs]
oies	noun	OIE	[@fp]
dindon	noun	DINDON	[@ms]
dindons	noun	DINDON	[@mp]
poulet	noun	POULET	[@ms]
poulets	noun	POULET	[@mp]
//
renard	noun	RENARD	[@ms]
renarde	noun	RENARD	[@fs]
renards	noun	RENARD	[@mp]
renardes	noun	RENARD	[@fp]
renardeau	noun	RENARD	[@ms]
renardeaux	noun	RENARD	[@mp]
//
vache	noun	VACHE	[@fs]
vaches	noun	VACHE	[@fp]
boeuf	noun	BOEUF	[@ms]
boeufs	noun	BOEUF	[@mp]
taureau	noun	TAUREAU	[@ms]
taureaux	noun	TAUREAU	[@mp]
//
cheval	noun	CHEVAL	[@ms]
chevaux	noun	CHEVAL	[@mp]
jument	noun	JUMENT	[@fs]
juments	noun	JUMENT	[@fp]
étalon	noun	ETALON	[@ms]
étalons	noun	ETALON	[@mp]
ongre	noun	ONGRE	[@ms]
ongres	noun	ONGRE	[@mp]
//
mouton	noun	MOUTON	[@ms]
moutons	noun	MOUTON	[@mp]
brebis	noun	BREBIS	[@f]
agneau	noun	AGNEAU	[@ms]
agneaux	noun	AGNEAU	[@mp]
chèvre	noun	CHEVRE	[@fs]
chèvres	noun	CHEVRE	[@fp]
//
canard	noun	CANARD	[@ms]
canards	noun	CANARD	[@mp]
cane	noun	CANARD	[@fs]
canes	noun	CANARD	[@fp]
//
oiseau	noun	OISEAU	[@ms]
oiseaux	noun	OISEAU	[@mp]
moineau	noun	MOINEAU	[@ms]
moineaux	noun	MOINEAU	[@mp]
mesange	noun	MESANGE	[@fs]
mesanges	noun	MESANGE	[@fp]
mésange	noun	MESANGE	[@fs]
mésanges	noun	MESANGE	[@fp]
//
lion	noun	LION	[@ms]
lions	noun	LION	[@mp]
lionne	noun	LION	[@fs]
lionnes	noun	LION	[@fp]
tigre	noun	TIGRE	[@ms]
tigres	noun	TIGRE	[@mp]
tigresse	noun	TIGRE	[@fs]
tigresses	noun	TIGRE	[@fp]
léopard	noun	LEOPARD	[@ms]
léopards	noun	LEOPARD	[@mp]
jaguar	noun	JAGUAR	[@ms]
jaguars	noun	JAGUAR	[@mp]
ours	noun	OURS	[@m]
ourse	noun	OURS	[@fs]
ourses	noun	OURS	[@fp]
//
loup	noun	LOUP	[@ms]
loups	noun	LOUP	[@mp]
louve	noun	LOUP	[@fs]
louves	noun	LOUP	[@fp]
//
serpent	noun	SERPENT	[@ms]
serpents	noun	SERPENT	[@mp]
//
rat	noun	RAT	[@ms]
rats	noun	RAT	[@mp]
rate	noun	RAT	[@fs]
rates	noun	RAT	[@fp]
//
hamster	noun	HAMSTER	[@ms]
hamsters	noun	HAMSTER	[@mp]
//
coyote	noun	COYOTE	[@ms]
coyotes	noun	COYOTE	[@mp]
//
chacal	noun	CHACAL	[@ms]
chacals	noun	CHACAL	[@mp]
//
cerf	noun	CERF	[@ms]
cerfs	noun	CERF	[@mp]
biche	noun	CERF	[@fs]
biches	noun	CERF	[@fp]
faon	noun	CERF	[@ms]
faons	noun	CERF	[@mp]
//
chevreuil	noun	CHEVREUIL	[@ms]
chevreuils	noun	CHEVREUIL	[@mp]
chevrette	noun	CHEVREUIL	[@fs]
chevrettes	noun	CHEVREUIL	[@fp]
faon	noun	CHEVREUIL	[@ms]
faons	noun	CHEVREUIL	[@mp]
//
sanglier	noun	SANGLIER	[@ms]
sangliers	noun	SANGLIER	[@mp]
laie	noun	SANGLIER	[@fs]
laies	noun	SANGLIER	[@fp]
marcassin	noun	SANGLIER	[@ms]
marcassins	noun	SANGLIER	[@mp]
//
hibou	noun	HIBOU	[@ms]
hiboux	noun	HIBOU	[@mp]
//
chouette	noun	CHOUETTE	[@fs]
chouettes	noun	CHOUETTE	[@fp]
//
corbeau	noun	CORBEAU	[@ms]
corbeaux	noun	CORBEAU	[@mp]
//
corneille	noun	CORNEILLE	[@fs]
corneilles	noun	CORNEILLE	[@fp]
//
grenouille	noun	GRENOUILLE	[@fs]
grenouilles	noun	GRENOUILLE	[@fp]
//
lapin	noun	LAPIN	[@ms]
lapins	noun	LAPIN	[@mp]
//
âne	noun	ANE	[@ms]
ânes	noun	ANE	[@mp]
//
chauve-souris	noun	CHAUVE_SOURIS	[@fs]
chauves-souris	noun	CHAUVE_SOURIS	[@fp]
//
// ***********************************************************
//  Verbs by lemma
// ***********************************************************/
//
// COUINER
//
couine	verb	COUINER	[SUBJ:[@_1s], @indicatif_present]
couines	verb	COUINER	[SUBJ:[@_2s], @indicatif_present]
couine	verb	COUINER	[SUBJ:[@_3s], @indicatif_present]
couinons	verb	COUINER	[SUBJ:[@_1p], @indicatif_present]
couinez	verb	COUINER	[SUBJ:[@_2p], @indicatif_present]
couinent	verb	COUINER	[SUBJ:[@_3p], @indicatif_present]
//
couinais	verb	COUINER	[SUBJ:[@_1s], @indicatif_imparfait]
couinais	verb	COUINER	[SUBJ:[@_2s], @indicatif_imparfait]
couinait	verb	COUINER	[SUBJ:[@_3s], @indicatif_imparfait]
couinions	verb	COUINER	[SUBJ:[@_1p], @indicatif_imparfait]
couiniez	verb	COUINER	[SUBJ:[@_2p], @indicatif_imparfait]
couinaient	verb	COUINER	[SUBJ:[@_3p], @indicatif_imparfait]
//
couinai	verb	COUINER	[SUBJ:[@_1s], @indicatif_passe_simple]
couinas	verb	COUINER	[SUBJ:[@_2s], @indicatif_passe_simple]
couina	verb	COUINER	[SUBJ:[@_3s], @indicatif_passe_simple]
couinâmes	verb	COUINER	[SUBJ:[@_1p], @indicatif_passe_simple]
couinâtes	verb	COUINER	[SUBJ:[@_2p], @indicatif_passe_simple]
couinèrent	verb	COUINER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
couinerai	verb	COUINER	[SUBJ:[@_1s], @indicatif_futur_simple]
couineras	verb	COUINER	[SUBJ:[@_2s], @indicatif_futur_simple]
couinera	verb	COUINER	[SUBJ:[@_3s], @indicatif_futur_simple]
couinerons	verb	COUINER	[SUBJ:[@_1p], @indicatif_futur_simple]
couinerez	verb	COUINER	[SUBJ:[@_2p], @indicatif_futur_simple]
couineront	verb	COUINER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// MIAULER
//
miaule	verb	MIAULER	[SUBJ:[@_1s], @indicatif_present]
miaules	verb	MIAULER	[SUBJ:[@_2s], @indicatif_present]
miaule	verb	MIAULER	[SUBJ:[@_3s], @indicatif_present]
miaulons	verb	MIAULER	[SUBJ:[@_1p], @indicatif_present]
miaulez	verb	MIAULER	[SUBJ:[@_2p], @indicatif_present]
miaulent	verb	MIAULER	[SUBJ:[@_3p], @indicatif_present]
//
miaulais	verb	MIAULER	[SUBJ:[@_1s], @indicatif_imparfait]
miaulais	verb	MIAULER	[SUBJ:[@_2s], @indicatif_imparfait]
miaulait	verb	MIAULER	[SUBJ:[@_3s], @indicatif_imparfait]
miaulions	verb	MIAULER	[SUBJ:[@_1p], @indicatif_imparfait]
miauliez	verb	MIAULER	[SUBJ:[@_2p], @indicatif_imparfait]
miaulaient	verb	MIAULER	[SUBJ:[@_3p], @indicatif_imparfait]
//
miaulai	verb	MIAULER	[SUBJ:[@_1s], @indicatif_passe_simple]
miaulas	verb	MIAULER	[SUBJ:[@_2s], @indicatif_passe_simple]
miaula	verb	MIAULER	[SUBJ:[@_3s], @indicatif_passe_simple]
miaulâmes	verb	MIAULER	[SUBJ:[@_1p], @indicatif_passe_simple]
miaulâtes	verb	MIAULER	[SUBJ:[@_2p], @indicatif_passe_simple]
miaulèrent	verb	MIAULER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
miaulerai	verb	MIAULER	[SUBJ:[@_1s], @indicatif_futur_simple]
miauleras	verb	MIAULER	[SUBJ:[@_2s], @indicatif_futur_simple]
miaulera	verb	MIAULER	[SUBJ:[@_3s], @indicatif_futur_simple]
miaulerons	verb	MIAULER	[SUBJ:[@_1p], @indicatif_futur_simple]
miaulerez	verb	MIAULER	[SUBJ:[@_2p], @indicatif_futur_simple]
miauleront	verb	MIAULER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// ABOYER
//
aboie	verb	ABOYER	[SUBJ:[@_1s], @indicatif_present]
aboies	verb	ABOYER	[SUBJ:[@_2s], @indicatif_present]
aboie	verb	ABOYER	[SUBJ:[@_3s], @indicatif_present]
aboyons	verb	ABOYER	[SUBJ:[@_1p], @indicatif_present]
aboyez	verb	ABOYER	[SUBJ:[@_2p], @indicatif_present]
aboient	verb	ABOYER	[SUBJ:[@_3p], @indicatif_present]
//
aboyais	verb	ABOYER	[SUBJ:[@_1s], @indicatif_imparfait]
aboyais	verb	ABOYER	[SUBJ:[@_2s], @indicatif_imparfait]
aboyait	verb	ABOYER	[SUBJ:[@_3s], @indicatif_imparfait]
aboyions	verb	ABOYER	[SUBJ:[@_1p], @indicatif_imparfait]
aboyiez	verb	ABOYER	[SUBJ:[@_2p], @indicatif_imparfait]
aboyaient	verb	ABOYER	[SUBJ:[@_3p], @indicatif_imparfait]
//
aboyai	verb	ABOYER	[SUBJ:[@_1s], @indicatif_passe_simple]
aboyas	verb	ABOYER	[SUBJ:[@_2s], @indicatif_passe_simple]
aboya	verb	ABOYER	[SUBJ:[@_3s], @indicatif_passe_simple]
aboyâmes	verb	ABOYER	[SUBJ:[@_1p], @indicatif_passe_simple]
aboyâtes	verb	ABOYER	[SUBJ:[@_2p], @indicatif_passe_simple]
aboyèrent	verb	ABOYER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
aboierai	verb	ABOYER	[SUBJ:[@_1s], @indicatif_futur_simple]
aboieras	verb	ABOYER	[SUBJ:[@_2s], @indicatif_futur_simple]
aboiera	verb	ABOYER	[SUBJ:[@_3s], @indicatif_futur_simple]
aboierons	verb	ABOYER	[SUBJ:[@_1p], @indicatif_futur_simple]
aboierez	verb	ABOYER	[SUBJ:[@_2p], @indicatif_futur_simple]
aboieront	verb	ABOYER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// JAPPER
//
jappe	verb	JAPPER	[SUBJ:[@_1s], @indicatif_present]
jappes	verb	JAPPER	[SUBJ:[@_2s], @indicatif_present]
jappe	verb	JAPPER	[SUBJ:[@_3s], @indicatif_present]
jappons	verb	JAPPER	[SUBJ:[@_1p], @indicatif_present]
jappez	verb	JAPPER	[SUBJ:[@_2p], @indicatif_present]
jappent	verb	JAPPER	[SUBJ:[@_3p], @indicatif_present]
//
jappais	verb	JAPPER	[SUBJ:[@_1s], @indicatif_imparfait]
jappais	verb	JAPPER	[SUBJ:[@_2s], @indicatif_imparfait]
jappait	verb	JAPPER	[SUBJ:[@_3s], @indicatif_imparfait]
jappions	verb	JAPPER	[SUBJ:[@_1p], @indicatif_imparfait]
jappiez	verb	JAPPER	[SUBJ:[@_2p], @indicatif_imparfait]
jappaient	verb	JAPPER	[SUBJ:[@_3p], @indicatif_imparfait]
//
jappai	verb	JAPPER	[SUBJ:[@_1s], @indicatif_passe_simple]
jappas	verb	JAPPER	[SUBJ:[@_2s], @indicatif_passe_simple]
jappa	verb	JAPPER	[SUBJ:[@_3s], @indicatif_passe_simple]
jappâmes	verb	JAPPER	[SUBJ:[@_1p], @indicatif_passe_simple]
jappâtes	verb	JAPPER	[SUBJ:[@_2p], @indicatif_passe_simple]
jappèrent	verb	JAPPER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
japperai	verb	JAPPER	[SUBJ:[@_1s], @indicatif_futur_simple]
japperas	verb	JAPPER	[SUBJ:[@_2s], @indicatif_futur_simple]
jappera	verb	JAPPER	[SUBJ:[@_3s], @indicatif_futur_simple]
japperons	verb	JAPPER	[SUBJ:[@_1p], @indicatif_futur_simple]
japperez	verb	JAPPER	[SUBJ:[@_2p], @indicatif_futur_simple]
japperont	verb	JAPPER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// HURLER
//
hurle	verb	HURLER	[SUBJ:[@_1s], @indicatif_present]
hurles	verb	HURLER	[SUBJ:[@_2s], @indicatif_present]
hurle	verb	HURLER	[SUBJ:[@_3s], @indicatif_present]
hurlons	verb	HURLER	[SUBJ:[@_1p], @indicatif_present]
hurlez	verb	HURLER	[SUBJ:[@_2p], @indicatif_present]
hurlent	verb	HURLER	[SUBJ:[@_3p], @indicatif_present]
//
hurlais	verb	HURLER	[SUBJ:[@_1s], @indicatif_imparfait]
hurlais	verb	HURLER	[SUBJ:[@_2s], @indicatif_imparfait]
hurlait	verb	HURLER	[SUBJ:[@_3s], @indicatif_imparfait]
hurlions	verb	HURLER	[SUBJ:[@_1p], @indicatif_imparfait]
hurliez	verb	HURLER	[SUBJ:[@_2p], @indicatif_imparfait]
hurlaient	verb	HURLER	[SUBJ:[@_3p], @indicatif_imparfait]
//
hurlai	verb	HURLER	[SUBJ:[@_1s], @indicatif_passe_simple]
hurlas	verb	HURLER	[SUBJ:[@_2s], @indicatif_passe_simple]
hurla	verb	HURLER	[SUBJ:[@_3s], @indicatif_passe_simple]
hurlâmes	verb	HURLER	[SUBJ:[@_1p], @indicatif_passe_simple]
hurlâtes	verb	HURLER	[SUBJ:[@_2p], @indicatif_passe_simple]
hurlèrent	verb	HURLER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
hurlerai	verb	HURLER	[SUBJ:[@_1s], @indicatif_futur_simple]
hurleras	verb	HURLER	[SUBJ:[@_2s], @indicatif_futur_simple]
hurlera	verb	HURLER	[SUBJ:[@_3s], @indicatif_futur_simple]
hurlerons	verb	HURLER	[SUBJ:[@_1p], @indicatif_futur_simple]
hurlerez	verb	HURLER	[SUBJ:[@_2p], @indicatif_futur_simple]
hurleront	verb	HURLER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// PIAULER
//
piaule	verb	PIAULER	[SUBJ:[@_1s], @indicatif_present]
piaules	verb	PIAULER	[SUBJ:[@_2s], @indicatif_present]
piaule	verb	PIAULER	[SUBJ:[@_3s], @indicatif_present]
piaulons	verb	PIAULER	[SUBJ:[@_1p], @indicatif_present]
piaulez	verb	PIAULER	[SUBJ:[@_2p], @indicatif_present]
piaulent	verb	PIAULER	[SUBJ:[@_3p], @indicatif_present]
//
piaulais	verb	PIAULER	[SUBJ:[@_1s], @indicatif_imparfait]
piaulais	verb	PIAULER	[SUBJ:[@_2s], @indicatif_imparfait]
piaulait	verb	PIAULER	[SUBJ:[@_3s], @indicatif_imparfait]
piaulions	verb	PIAULER	[SUBJ:[@_1p], @indicatif_imparfait]
piauliez	verb	PIAULER	[SUBJ:[@_2p], @indicatif_imparfait]
piaulaient	verb	PIAULER	[SUBJ:[@_3p], @indicatif_imparfait]
//
piaulai	verb	PIAULER	[SUBJ:[@_1s], @indicatif_passe_simple]
piaulas	verb	PIAULER	[SUBJ:[@_2s], @indicatif_passe_simple]
piaula	verb	PIAULER	[SUBJ:[@_3s], @indicatif_passe_simple]
piaulâmes	verb	PIAULER	[SUBJ:[@_1p], @indicatif_passe_simple]
piaulâtes	verb	PIAULER	[SUBJ:[@_2p], @indicatif_passe_simple]
piaulèrent	verb	PIAULER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
piaulerai	verb	PIAULER	[SUBJ:[@_1s], @indicatif_futur_simple]
piauleras	verb	PIAULER	[SUBJ:[@_2s], @indicatif_futur_simple]
piaulera	verb	PIAULER	[SUBJ:[@_3s], @indicatif_futur_simple]
piaulerons	verb	PIAULER	[SUBJ:[@_1p], @indicatif_futur_simple]
piaulerez	verb	PIAULER	[SUBJ:[@_2p], @indicatif_futur_simple]
piauleront	verb	PIAULER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// RUGIR
//
rugis	verb	RUGIR	[SUBJ:[@_1s], @indicatif_present]
rugis	verb	RUGIR	[SUBJ:[@_2s], @indicatif_present]
rugit	verb	RUGIR	[SUBJ:[@_3s], @indicatif_present]
rugissons	verb	RUGIR	[SUBJ:[@_1p], @indicatif_present]
rugissez	verb	RUGIR	[SUBJ:[@_2p], @indicatif_present]
rugissent	verb	RUGIR	[SUBJ:[@_3p], @indicatif_present]
//
rugissais	verb	RUGIR	[SUBJ:[@_1s], @indicatif_imparfait]
rugissais	verb	RUGIR	[SUBJ:[@_2s], @indicatif_imparfait]
rugissait	verb	RUGIR	[SUBJ:[@_3s], @indicatif_imparfait]
rugissions	verb	RUGIR	[SUBJ:[@_1p], @indicatif_imparfait]
rugissiez	verb	RUGIR	[SUBJ:[@_2p], @indicatif_imparfait]
rugissaient	verb	RUGIR	[SUBJ:[@_3p], @indicatif_imparfait]
//
rugis	verb	RUGIR	[SUBJ:[@_1s], @indicatif_passe_simple]
rugis	verb	RUGIR	[SUBJ:[@_2s], @indicatif_passe_simple]
rugit	verb	RUGIR	[SUBJ:[@_3s], @indicatif_passe_simple]
rugîmes	verb	RUGIR	[SUBJ:[@_1p], @indicatif_passe_simple]
rugîtes	verb	RUGIR	[SUBJ:[@_2p], @indicatif_passe_simple]
rugirent	verb	RUGIR	[SUBJ:[@_3p], @indicatif_passe_simple]
//
rugirai	verb	RUGIR	[SUBJ:[@_1s], @indicatif_futur_simple]
rugiras	verb	RUGIR	[SUBJ:[@_2s], @indicatif_futur_simple]
rugira	verb	RUGIR	[SUBJ:[@_3s], @indicatif_futur_simple]
rugirons	verb	RUGIR	[SUBJ:[@_1p], @indicatif_futur_simple]
rugirez	verb	RUGIR	[SUBJ:[@_2p], @indicatif_futur_simple]
rugiront	verb	RUGIR	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// HENNIR
//
hennis	verb	HENNIR	[SUBJ:[@_1s], @indicatif_present]
hennis	verb	HENNIR	[SUBJ:[@_2s], @indicatif_present]
hennit	verb	HENNIR	[SUBJ:[@_3s], @indicatif_present]
hennissons	verb	HENNIR	[SUBJ:[@_1p], @indicatif_present]
hennissez	verb	HENNIR	[SUBJ:[@_2p], @indicatif_present]
hennissent	verb	HENNIR	[SUBJ:[@_3p], @indicatif_present]
//
hennissais	verb	HENNIR	[SUBJ:[@_1s], @indicatif_imparfait]
hennissais	verb	HENNIR	[SUBJ:[@_2s], @indicatif_imparfait]
hennissait	verb	HENNIR	[SUBJ:[@_3s], @indicatif_imparfait]
hennissions	verb	HENNIR	[SUBJ:[@_1p], @indicatif_imparfait]
hennissiez	verb	HENNIR	[SUBJ:[@_2p], @indicatif_imparfait]
hennissaient	verb	HENNIR	[SUBJ:[@_3p], @indicatif_imparfait]
//
hennis	verb	HENNIR	[SUBJ:[@_1s], @indicatif_passe_simple]
hennis	verb	HENNIR	[SUBJ:[@_2s], @indicatif_passe_simple]
hennit	verb	HENNIR	[SUBJ:[@_3s], @indicatif_passe_simple]
hennîmes	verb	HENNIR	[SUBJ:[@_1p], @indicatif_passe_simple]
hennîtes	verb	HENNIR	[SUBJ:[@_2p], @indicatif_passe_simple]
hennirent	verb	HENNIR	[SUBJ:[@_3p], @indicatif_passe_simple]
//
hennirai	verb	HENNIR	[SUBJ:[@_1s], @indicatif_futur_simple]
henniras	verb	HENNIR	[SUBJ:[@_2s], @indicatif_futur_simple]
hennira	verb	HENNIR	[SUBJ:[@_3s], @indicatif_futur_simple]
hennirons	verb	HENNIR	[SUBJ:[@_1p], @indicatif_futur_simple]
hennirez	verb	HENNIR	[SUBJ:[@_2p], @indicatif_futur_simple]
henniront	verb	HENNIR	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// BELER
//
bêle	verb	BELER	[SUBJ:[@_1s], @indicatif_present]
bêles	verb	BELER	[SUBJ:[@_2s], @indicatif_present]
bêle	verb	BELER	[SUBJ:[@_3s], @indicatif_present]
bêlons	verb	BELER	[SUBJ:[@_1p], @indicatif_present]
bêlez	verb	BELER	[SUBJ:[@_2p], @indicatif_present]
bêlent	verb	BELER	[SUBJ:[@_3p], @indicatif_present]
//
bêlais	verb	BELER	[SUBJ:[@_1s], @indicatif_imparfait]
bêlais	verb	BELER	[SUBJ:[@_2s], @indicatif_imparfait]
bêlait	verb	BELER	[SUBJ:[@_3s], @indicatif_imparfait]
bêlions	verb	BELER	[SUBJ:[@_1p], @indicatif_imparfait]
bêliez	verb	BELER	[SUBJ:[@_2p], @indicatif_imparfait]
bêlaient	verb	BELER	[SUBJ:[@_3p], @indicatif_imparfait]
//
bêlai	verb	BELER	[SUBJ:[@_1s], @indicatif_passe_simple]
bêlas	verb	BELER	[SUBJ:[@_2s], @indicatif_passe_simple]
bêla	verb	BELER	[SUBJ:[@_3s], @indicatif_passe_simple]
bêlâmes	verb	BELER	[SUBJ:[@_1p], @indicatif_passe_simple]
bêlâtes	verb	BELER	[SUBJ:[@_2p], @indicatif_passe_simple]
bêlèrent	verb	BELER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
bêlerai	verb	BELER	[SUBJ:[@_1s], @indicatif_futur_simple]
bêleras	verb	BELER	[SUBJ:[@_2s], @indicatif_futur_simple]
bêlera	verb	BELER	[SUBJ:[@_3s], @indicatif_futur_simple]
bêlerons	verb	BELER	[SUBJ:[@_1p], @indicatif_futur_simple]
bêlerez	verb	BELER	[SUBJ:[@_2p], @indicatif_futur_simple]
bêleront	verb	BELER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// CAQUETER
//
caquette	verb	CAQUETER	[SUBJ:[@_1s], @indicatif_present]
caquettes	verb	CAQUETER	[SUBJ:[@_2s], @indicatif_present]
caquette	verb	CAQUETER	[SUBJ:[@_3s], @indicatif_present]
caquetons	verb	CAQUETER	[SUBJ:[@_1p], @indicatif_present]
caquetez	verb	CAQUETER	[SUBJ:[@_2p], @indicatif_present]
caquettent	verb	CAQUETER	[SUBJ:[@_3p], @indicatif_present]
//
caquetais	verb	CAQUETER	[SUBJ:[@_1s], @indicatif_imparfait]
caquetais	verb	CAQUETER	[SUBJ:[@_2s], @indicatif_imparfait]
caquetait	verb	CAQUETER	[SUBJ:[@_3s], @indicatif_imparfait]
caquetions	verb	CAQUETER	[SUBJ:[@_1p], @indicatif_imparfait]
caquetiez	verb	CAQUETER	[SUBJ:[@_2p], @indicatif_imparfait]
caquetaient	verb	CAQUETER	[SUBJ:[@_3p], @indicatif_imparfait]
//
caquetai	verb	CAQUETER	[SUBJ:[@_1s], @indicatif_passe_simple]
caquetas	verb	CAQUETER	[SUBJ:[@_2s], @indicatif_passe_simple]
caqueta	verb	CAQUETER	[SUBJ:[@_3s], @indicatif_passe_simple]
caquetâmes	verb	CAQUETER	[SUBJ:[@_1p], @indicatif_passe_simple]
caquetâtes	verb	CAQUETER	[SUBJ:[@_2p], @indicatif_passe_simple]
caquetèrent	verb	CAQUETER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
caquèterai	verb	CAQUETER	[SUBJ:[@_1s], @indicatif_futur_simple]
caquèteras	verb	CAQUETER	[SUBJ:[@_2s], @indicatif_futur_simple]
caquètera	verb	CAQUETER	[SUBJ:[@_3s], @indicatif_futur_simple]
caquèterons	verb	CAQUETER	[SUBJ:[@_1p], @indicatif_futur_simple]
caquèterez	verb	CAQUETER	[SUBJ:[@_2p], @indicatif_futur_simple]
caquèteront	verb	CAQUETER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// CANCANER
//
cancane	verb	CANCANER	[SUBJ:[@_1s], @indicatif_present]
cancanes	verb	CANCANER	[SUBJ:[@_2s], @indicatif_present]
cancane	verb	CANCANER	[SUBJ:[@_3s], @indicatif_present]
cancanons	verb	CANCANER	[SUBJ:[@_1p], @indicatif_present]
cancanez	verb	CANCANER	[SUBJ:[@_2p], @indicatif_present]
cancanent	verb	CANCANER	[SUBJ:[@_3p], @indicatif_present]
//
cancanais	verb	CANCANER	[SUBJ:[@_1s], @indicatif_imparfait]
cancanais	verb	CANCANER	[SUBJ:[@_2s], @indicatif_imparfait]
cancanait	verb	CANCANER	[SUBJ:[@_3s], @indicatif_imparfait]
cancanions	verb	CANCANER	[SUBJ:[@_1p], @indicatif_imparfait]
cancaniez	verb	CANCANER	[SUBJ:[@_2p], @indicatif_imparfait]
cancanaient	verb	CANCANER	[SUBJ:[@_3p], @indicatif_imparfait]
//
cancanai	verb	CANCANER	[SUBJ:[@_1s], @indicatif_passe_simple]
cancanas	verb	CANCANER	[SUBJ:[@_2s], @indicatif_passe_simple]
cancana	verb	CANCANER	[SUBJ:[@_3s], @indicatif_passe_simple]
cancanâmes	verb	CANCANER	[SUBJ:[@_1p], @indicatif_passe_simple]
cancanâtes	verb	CANCANER	[SUBJ:[@_2p], @indicatif_passe_simple]
cancanèrent	verb	CANCANER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
cancanerai	verb	CANCANER	[SUBJ:[@_1s], @indicatif_futur_simple]
cancaneras	verb	CANCANER	[SUBJ:[@_2s], @indicatif_futur_simple]
cancanera	verb	CANCANER	[SUBJ:[@_3s], @indicatif_futur_simple]
cancanerons	verb	CANCANER	[SUBJ:[@_1p], @indicatif_futur_simple]
cancanerez	verb	CANCANER	[SUBJ:[@_2p], @indicatif_futur_simple]
cancaneront	verb	CANCANER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// GAZOUILLER
//
gazouille	verb	GAZOUILLER	[SUBJ:[@_1s], @indicatif_present]
gazouilles	verb	GAZOUILLER	[SUBJ:[@_2s], @indicatif_present]
gazouille	verb	GAZOUILLER	[SUBJ:[@_3s], @indicatif_present]
gazouillons	verb	GAZOUILLER	[SUBJ:[@_1p], @indicatif_present]
gazouillez	verb	GAZOUILLER	[SUBJ:[@_2p], @indicatif_present]
gazouillent	verb	GAZOUILLER	[SUBJ:[@_3p], @indicatif_present]
//
gazouillais	verb	GAZOUILLER	[SUBJ:[@_1s], @indicatif_imparfait]
gazouillais	verb	GAZOUILLER	[SUBJ:[@_2s], @indicatif_imparfait]
gazouillait	verb	GAZOUILLER	[SUBJ:[@_3s], @indicatif_imparfait]
gazouillions	verb	GAZOUILLER	[SUBJ:[@_1p], @indicatif_imparfait]
gazouilliez	verb	GAZOUILLER	[SUBJ:[@_2p], @indicatif_imparfait]
gazouillaient	verb	GAZOUILLER	[SUBJ:[@_3p], @indicatif_imparfait]
//
gazouillai	verb	GAZOUILLER	[SUBJ:[@_1s], @indicatif_passe_simple]
gazouillas	verb	GAZOUILLER	[SUBJ:[@_2s], @indicatif_passe_simple]
gazouilla	verb	GAZOUILLER	[SUBJ:[@_3s], @indicatif_passe_simple]
gazouillâmes	verb	GAZOUILLER	[SUBJ:[@_1p], @indicatif_passe_simple]
gazouillâtes	verb	GAZOUILLER	[SUBJ:[@_2p], @indicatif_passe_simple]
gazouillèrent	verb	GAZOUILLER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
gazouillerai	verb	GAZOUILLER	[SUBJ:[@_1s], @indicatif_futur_simple]
gazouilleras	verb	GAZOUILLER	[SUBJ:[@_2s], @indicatif_futur_simple]
gazouillera	verb	GAZOUILLER	[SUBJ:[@_3s], @indicatif_futur_simple]
gazouillerons	verb	GAZOUILLER	[SUBJ:[@_1p], @indicatif_futur_simple]
gazouillerez	verb	GAZOUILLER	[SUBJ:[@_2p], @indicatif_futur_simple]
gazouilleront	verb	GAZOUILLER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// SIFFLER
//
siffle	verb	SIFFLER	[SUBJ:[@_1s], @indicatif_present]
siffles	verb	SIFFLER	[SUBJ:[@_2s], @indicatif_present]
siffle	verb	SIFFLER	[SUBJ:[@_3s], @indicatif_present]
sifflons	verb	SIFFLER	[SUBJ:[@_1p], @indicatif_present]
sifflez	verb	SIFFLER	[SUBJ:[@_2p], @indicatif_present]
sifflent	verb	SIFFLER	[SUBJ:[@_3p], @indicatif_present]
//
sifflais	verb	SIFFLER	[SUBJ:[@_1s], @indicatif_imparfait]
sifflais	verb	SIFFLER	[SUBJ:[@_2s], @indicatif_imparfait]
sifflait	verb	SIFFLER	[SUBJ:[@_3s], @indicatif_imparfait]
sifflions	verb	SIFFLER	[SUBJ:[@_1p], @indicatif_imparfait]
siffliez	verb	SIFFLER	[SUBJ:[@_2p], @indicatif_imparfait]
sifflaient	verb	SIFFLER	[SUBJ:[@_3p], @indicatif_imparfait]
//
sifflai	verb	SIFFLER	[SUBJ:[@_1s], @indicatif_passe_simple]
sifflas	verb	SIFFLER	[SUBJ:[@_2s], @indicatif_passe_simple]
siffla	verb	SIFFLER	[SUBJ:[@_3s], @indicatif_passe_simple]
sifflâmes	verb	SIFFLER	[SUBJ:[@_1p], @indicatif_passe_simple]
sifflâtes	verb	SIFFLER	[SUBJ:[@_2p], @indicatif_passe_simple]
sifflèrent	verb	SIFFLER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
sifflerai	verb	SIFFLER	[SUBJ:[@_1s], @indicatif_futur_simple]
siffleras	verb	SIFFLER	[SUBJ:[@_2s], @indicatif_futur_simple]
sifflera	verb	SIFFLER	[SUBJ:[@_3s], @indicatif_futur_simple]
sifflerons	verb	SIFFLER	[SUBJ:[@_1p], @indicatif_futur_simple]
sifflerez	verb	SIFFLER	[SUBJ:[@_2p], @indicatif_futur_simple]
siffleront	verb	SIFFLER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// BRAMER
//
brame	verb	BRAMER	[SUBJ:[@_1s], @indicatif_present]
brames	verb	BRAMER	[SUBJ:[@_2s], @indicatif_present]
brame	verb	BRAMER	[SUBJ:[@_3s], @indicatif_present]
bramons	verb	BRAMER	[SUBJ:[@_1p], @indicatif_present]
bramez	verb	BRAMER	[SUBJ:[@_2p], @indicatif_present]
brament	verb	BRAMER	[SUBJ:[@_3p], @indicatif_present]
//
bramais	verb	BRAMER	[SUBJ:[@_1s], @indicatif_imparfait]
bramais	verb	BRAMER	[SUBJ:[@_2s], @indicatif_imparfait]
bramait	verb	BRAMER	[SUBJ:[@_3s], @indicatif_imparfait]
bramions	verb	BRAMER	[SUBJ:[@_1p], @indicatif_imparfait]
bramiez	verb	BRAMER	[SUBJ:[@_2p], @indicatif_imparfait]
bramaient	verb	BRAMER	[SUBJ:[@_3p], @indicatif_imparfait]
//
bramai	verb	BRAMER	[SUBJ:[@_1s], @indicatif_passe_simple]
bramas	verb	BRAMER	[SUBJ:[@_2s], @indicatif_passe_simple]
brama	verb	BRAMER	[SUBJ:[@_3s], @indicatif_passe_simple]
bramâmes	verb	BRAMER	[SUBJ:[@_1p], @indicatif_passe_simple]
bramâtes	verb	BRAMER	[SUBJ:[@_2p], @indicatif_passe_simple]
bramèrent	verb	BRAMER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
bramerai	verb	BRAMER	[SUBJ:[@_1s], @indicatif_futur_simple]
brameras	verb	BRAMER	[SUBJ:[@_2s], @indicatif_futur_simple]
bramera	verb	BRAMER	[SUBJ:[@_3s], @indicatif_futur_simple]
bramerons	verb	BRAMER	[SUBJ:[@_1p], @indicatif_futur_simple]
bramerez	verb	BRAMER	[SUBJ:[@_2p], @indicatif_futur_simple]
brameront	verb	BRAMER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// GROGNER
//
grogne	verb	GROGNER	[SUBJ:[@_1s], @indicatif_present]
grognes	verb	GROGNER	[SUBJ:[@_2s], @indicatif_present]
grogne	verb	GROGNER	[SUBJ:[@_3s], @indicatif_present]
grognons	verb	GROGNER	[SUBJ:[@_1p], @indicatif_present]
grognez	verb	GROGNER	[SUBJ:[@_2p], @indicatif_present]
grognent	verb	GROGNER	[SUBJ:[@_3p], @indicatif_present]
//
grognais	verb	GROGNER	[SUBJ:[@_1s], @indicatif_imparfait]
grognais	verb	GROGNER	[SUBJ:[@_2s], @indicatif_imparfait]
grognait	verb	GROGNER	[SUBJ:[@_3s], @indicatif_imparfait]
grognions	verb	GROGNER	[SUBJ:[@_1p], @indicatif_imparfait]
grogniez	verb	GROGNER	[SUBJ:[@_2p], @indicatif_imparfait]
grognaient	verb	GROGNER	[SUBJ:[@_3p], @indicatif_imparfait]
//
grognai	verb	GROGNER	[SUBJ:[@_1s], @indicatif_passe_simple]
grognas	verb	GROGNER	[SUBJ:[@_2s], @indicatif_passe_simple]
grogna	verb	GROGNER	[SUBJ:[@_3s], @indicatif_passe_simple]
grognâmes	verb	GROGNER	[SUBJ:[@_1p], @indicatif_passe_simple]
grognâtes	verb	GROGNER	[SUBJ:[@_2p], @indicatif_passe_simple]
grognèrent	verb	GROGNER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
grognerai	verb	GROGNER	[SUBJ:[@_1s], @indicatif_futur_simple]
grogneras	verb	GROGNER	[SUBJ:[@_2s], @indicatif_futur_simple]
grognera	verb	GROGNER	[SUBJ:[@_3s], @indicatif_futur_simple]
grognerons	verb	GROGNER	[SUBJ:[@_1p], @indicatif_futur_simple]
grognerez	verb	GROGNER	[SUBJ:[@_2p], @indicatif_futur_simple]
grogneront	verb	GROGNER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// GLAPIR
//
glapis	verb	GLAPIR	[SUBJ:[@_1s], @indicatif_present]
glapis	verb	GLAPIR	[SUBJ:[@_2s], @indicatif_present]
glapit	verb	GLAPIR	[SUBJ:[@_3s], @indicatif_present]
glapissons	verb	GLAPIR	[SUBJ:[@_1p], @indicatif_present]
glapissez	verb	GLAPIR	[SUBJ:[@_2p], @indicatif_present]
glapissent	verb	GLAPIR	[SUBJ:[@_3p], @indicatif_present]
//
glapissais	verb	GLAPIR	[SUBJ:[@_1s], @indicatif_imparfait]
glapissais	verb	GLAPIR	[SUBJ:[@_2s], @indicatif_imparfait]
glapissait	verb	GLAPIR	[SUBJ:[@_3s], @indicatif_imparfait]
glapissions	verb	GLAPIR	[SUBJ:[@_1p], @indicatif_imparfait]
glapissiez	verb	GLAPIR	[SUBJ:[@_2p], @indicatif_imparfait]
glapissaient	verb	GLAPIR	[SUBJ:[@_3p], @indicatif_imparfait]
//
glapis	verb	GLAPIR	[SUBJ:[@_1s], @indicatif_passe_simple]
glapis	verb	GLAPIR	[SUBJ:[@_2s], @indicatif_passe_simple]
glapit	verb	GLAPIR	[SUBJ:[@_3s], @indicatif_passe_simple]
glapîmes	verb	GLAPIR	[SUBJ:[@_1p], @indicatif_passe_simple]
glapîtes	verb	GLAPIR	[SUBJ:[@_2p], @indicatif_passe_simple]
glapirent	verb	GLAPIR	[SUBJ:[@_3p], @indicatif_passe_simple]
//
glapirai	verb	GLAPIR	[SUBJ:[@_1s], @indicatif_futur_simple]
glapiras	verb	GLAPIR	[SUBJ:[@_2s], @indicatif_futur_simple]
glapira	verb	GLAPIR	[SUBJ:[@_3s], @indicatif_futur_simple]
glapirons	verb	GLAPIR	[SUBJ:[@_1p], @indicatif_futur_simple]
glapirez	verb	GLAPIR	[SUBJ:[@_2p], @indicatif_futur_simple]
glapiront	verb	GLAPIR	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// CRIER
//
crie	verb	CRIER	[SUBJ:[@_1s], @indicatif_present]
cries	verb	CRIER	[SUBJ:[@_2s], @indicatif_present]
crie	verb	CRIER	[SUBJ:[@_3s], @indicatif_present]
crions	verb	CRIER	[SUBJ:[@_1p], @indicatif_present]
criez	verb	CRIER	[SUBJ:[@_2p], @indicatif_present]
crient	verb	CRIER	[SUBJ:[@_3p], @indicatif_present]
//
criais	verb	CRIER	[SUBJ:[@_1s], @indicatif_imparfait]
criais	verb	CRIER	[SUBJ:[@_2s], @indicatif_imparfait]
criait	verb	CRIER	[SUBJ:[@_3s], @indicatif_imparfait]
criions	verb	CRIER	[SUBJ:[@_1p], @indicatif_imparfait]
criiez	verb	CRIER	[SUBJ:[@_2p], @indicatif_imparfait]
criaient	verb	CRIER	[SUBJ:[@_3p], @indicatif_imparfait]
//
criai	verb	CRIER	[SUBJ:[@_1s], @indicatif_passe_simple]
crias	verb	CRIER	[SUBJ:[@_2s], @indicatif_passe_simple]
cria	verb	CRIER	[SUBJ:[@_3s], @indicatif_passe_simple]
criâmes	verb	CRIER	[SUBJ:[@_1p], @indicatif_passe_simple]
criâtes	verb	CRIER	[SUBJ:[@_2p], @indicatif_passe_simple]
crièrent	verb	CRIER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
crierai	verb	CRIER	[SUBJ:[@_1s], @indicatif_futur_simple]
crieras	verb	CRIER	[SUBJ:[@_2s], @indicatif_futur_simple]
criera	verb	CRIER	[SUBJ:[@_3s], @indicatif_futur_simple]
crierons	verb	CRIER	[SUBJ:[@_1p], @indicatif_futur_simple]
crierez	verb	CRIER	[SUBJ:[@_2p], @indicatif_futur_simple]
crieront	verb	CRIER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// HULULER
//
hulule	verb	HULULER	[SUBJ:[@_1s], @indicatif_present]
hulules	verb	HULULER	[SUBJ:[@_2s], @indicatif_present]
hulule	verb	HULULER	[SUBJ:[@_3s], @indicatif_present]
hululons	verb	HULULER	[SUBJ:[@_1p], @indicatif_present]
hululez	verb	HULULER	[SUBJ:[@_2p], @indicatif_present]
hululent	verb	HULULER	[SUBJ:[@_3p], @indicatif_present]
//
hululais	verb	HULULER	[SUBJ:[@_1s], @indicatif_imparfait]
hululais	verb	HULULER	[SUBJ:[@_2s], @indicatif_imparfait]
hululait	verb	HULULER	[SUBJ:[@_3s], @indicatif_imparfait]
hululions	verb	HULULER	[SUBJ:[@_1p], @indicatif_imparfait]
hululiez	verb	HULULER	[SUBJ:[@_2p], @indicatif_imparfait]
hululaient	verb	HULULER	[SUBJ:[@_3p], @indicatif_imparfait]
//
hululai	verb	HULULER	[SUBJ:[@_1s], @indicatif_passe_simple]
hululas	verb	HULULER	[SUBJ:[@_2s], @indicatif_passe_simple]
hulula	verb	HULULER	[SUBJ:[@_3s], @indicatif_passe_simple]
hululâmes	verb	HULULER	[SUBJ:[@_1p], @indicatif_passe_simple]
hululâtes	verb	HULULER	[SUBJ:[@_2p], @indicatif_passe_simple]
hululèrent	verb	HULULER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
hululerai	verb	HULULER	[SUBJ:[@_1s], @indicatif_futur_simple]
hululeras	verb	HULULER	[SUBJ:[@_2s], @indicatif_futur_simple]
hululera	verb	HULULER	[SUBJ:[@_3s], @indicatif_futur_simple]
hululerons	verb	HULULER	[SUBJ:[@_1p], @indicatif_futur_simple]
hululerez	verb	HULULER	[SUBJ:[@_2p], @indicatif_futur_simple]
hululeront	verb	HULULER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// CROASSER
//
croasse	verb	CROASSER	[SUBJ:[@_1s], @indicatif_present]
croasses	verb	CROASSER	[SUBJ:[@_2s], @indicatif_present]
croasse	verb	CROASSER	[SUBJ:[@_3s], @indicatif_present]
croassons	verb	CROASSER	[SUBJ:[@_1p], @indicatif_present]
croassez	verb	CROASSER	[SUBJ:[@_2p], @indicatif_present]
croassent	verb	CROASSER	[SUBJ:[@_3p], @indicatif_present]
//
croassais	verb	CROASSER	[SUBJ:[@_1s], @indicatif_imparfait]
croassais	verb	CROASSER	[SUBJ:[@_2s], @indicatif_imparfait]
croassait	verb	CROASSER	[SUBJ:[@_3s], @indicatif_imparfait]
croassions	verb	CROASSER	[SUBJ:[@_1p], @indicatif_imparfait]
croassiez	verb	CROASSER	[SUBJ:[@_2p], @indicatif_imparfait]
croassaient	verb	CROASSER	[SUBJ:[@_3p], @indicatif_imparfait]
//
croassai	verb	CROASSER	[SUBJ:[@_1s], @indicatif_passe_simple]
croassas	verb	CROASSER	[SUBJ:[@_2s], @indicatif_passe_simple]
croassa	verb	CROASSER	[SUBJ:[@_3s], @indicatif_passe_simple]
croassâmes	verb	CROASSER	[SUBJ:[@_1p], @indicatif_passe_simple]
croassâtes	verb	CROASSER	[SUBJ:[@_2p], @indicatif_passe_simple]
croassèrent	verb	CROASSER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
croasserai	verb	CROASSER	[SUBJ:[@_1s], @indicatif_futur_simple]
croasseras	verb	CROASSER	[SUBJ:[@_2s], @indicatif_futur_simple]
croassera	verb	CROASSER	[SUBJ:[@_3s], @indicatif_futur_simple]
croasserons	verb	CROASSER	[SUBJ:[@_1p], @indicatif_futur_simple]
croasserez	verb	CROASSER	[SUBJ:[@_2p], @indicatif_futur_simple]
croasseront	verb	CROASSER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// COASSER
//
coasse	verb	COASSER	[SUBJ:[@_1s], @indicatif_present]
coasses	verb	COASSER	[SUBJ:[@_2s], @indicatif_present]
coasse	verb	COASSER	[SUBJ:[@_3s], @indicatif_present]
coassons	verb	COASSER	[SUBJ:[@_1p], @indicatif_present]
coassez	verb	COASSER	[SUBJ:[@_2p], @indicatif_present]
coassent	verb	COASSER	[SUBJ:[@_3p], @indicatif_present]
//
coassais	verb	COASSER	[SUBJ:[@_1s], @indicatif_imparfait]
coassais	verb	COASSER	[SUBJ:[@_2s], @indicatif_imparfait]
coassait	verb	COASSER	[SUBJ:[@_3s], @indicatif_imparfait]
coassions	verb	COASSER	[SUBJ:[@_1p], @indicatif_imparfait]
coassiez	verb	COASSER	[SUBJ:[@_2p], @indicatif_imparfait]
coassaient	verb	COASSER	[SUBJ:[@_3p], @indicatif_imparfait]
//
coassai	verb	COASSER	[SUBJ:[@_1s], @indicatif_passe_simple]
coassas	verb	COASSER	[SUBJ:[@_2s], @indicatif_passe_simple]
coassa	verb	COASSER	[SUBJ:[@_3s], @indicatif_passe_simple]
coassâmes	verb	COASSER	[SUBJ:[@_1p], @indicatif_passe_simple]
coassâtes	verb	COASSER	[SUBJ:[@_2p], @indicatif_passe_simple]
coassèrent	verb	COASSER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
coasserai	verb	COASSER	[SUBJ:[@_1s], @indicatif_futur_simple]
coasseras	verb	COASSER	[SUBJ:[@_2s], @indicatif_futur_simple]
coassera	verb	COASSER	[SUBJ:[@_3s], @indicatif_futur_simple]
coasserons	verb	COASSER	[SUBJ:[@_1p], @indicatif_futur_simple]
coasserez	verb	COASSER	[SUBJ:[@_2p], @indicatif_futur_simple]
coasseront	verb	COASSER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// BRAIRE
//
brais	verb	BRAIRE	[SUBJ:[@_1s], @indicatif_present]
brais	verb	BRAIRE	[SUBJ:[@_2s], @indicatif_present]
brait	verb	BRAIRE	[SUBJ:[@_3s], @indicatif_present]
brayons	verb	BRAIRE	[SUBJ:[@_1p], @indicatif_present]
brayez	verb	BRAIRE	[SUBJ:[@_2p], @indicatif_present]
braient	verb	BRAIRE	[SUBJ:[@_3p], @indicatif_present]
//
brayais	verb	BRAIRE	[SUBJ:[@_1s], @indicatif_imparfait]
brayais	verb	BRAIRE	[SUBJ:[@_2s], @indicatif_imparfait]
brayait	verb	BRAIRE	[SUBJ:[@_3s], @indicatif_imparfait]
brayions	verb	BRAIRE	[SUBJ:[@_1p], @indicatif_imparfait]
brayiez	verb	BRAIRE	[SUBJ:[@_2p], @indicatif_imparfait]
brayaient	verb	BRAIRE	[SUBJ:[@_3p], @indicatif_imparfait]
//
brais	verb	BRAIRE	[SUBJ:[@_1s], @indicatif_passe_simple]
brais	verb	BRAIRE	[SUBJ:[@_2s], @indicatif_passe_simple]
brait	verb	BRAIRE	[SUBJ:[@_3s], @indicatif_passe_simple]
braîmes	verb	BRAIRE	[SUBJ:[@_1p], @indicatif_passe_simple]
braîtes	verb	BRAIRE	[SUBJ:[@_2p], @indicatif_passe_simple]
brairent	verb	BRAIRE	[SUBJ:[@_3p], @indicatif_passe_simple]
//
brairai	verb	BRAIRE	[SUBJ:[@_1s], @indicatif_futur_simple]
brairas	verb	BRAIRE	[SUBJ:[@_2s], @indicatif_futur_simple]
braira	verb	BRAIRE	[SUBJ:[@_3s], @indicatif_futur_simple]
brairons	verb	BRAIRE	[SUBJ:[@_1p], @indicatif_futur_simple]
brairez	verb	BRAIRE	[SUBJ:[@_2p], @indicatif_futur_simple]
brairont	verb	BRAIRE	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// RAIRE
//
rais	verb	RAIRE	[SUBJ:[@_1s], @indicatif_present]
rais	verb	RAIRE	[SUBJ:[@_2s], @indicatif_present]
rait	verb	RAIRE	[SUBJ:[@_3s], @indicatif_present]
rayons	verb	RAIRE	[SUBJ:[@_1p], @indicatif_present]
rayez	verb	RAIRE	[SUBJ:[@_2p], @indicatif_present]
raient	verb	RAIRE	[SUBJ:[@_3p], @indicatif_present]
//
rayais	verb	RAIRE	[SUBJ:[@_1s], @indicatif_imparfait]
rayais	verb	RAIRE	[SUBJ:[@_2s], @indicatif_imparfait]
rayait	verb	RAIRE	[SUBJ:[@_3s], @indicatif_imparfait]
rayions	verb	RAIRE	[SUBJ:[@_1p], @indicatif_imparfait]
rayiez	verb	RAIRE	[SUBJ:[@_2p], @indicatif_imparfait]
rayaient	verb	RAIRE	[SUBJ:[@_3p], @indicatif_imparfait]
//
rais	verb	RAIRE	[SUBJ:[@_1s], @indicatif_passe_simple]
rais	verb	RAIRE	[SUBJ:[@_2s], @indicatif_passe_simple]
rait	verb	RAIRE	[SUBJ:[@_3s], @indicatif_passe_simple]
raîmes	verb	RAIRE	[SUBJ:[@_1p], @indicatif_passe_simple]
raîtes	verb	RAIRE	[SUBJ:[@_2p], @indicatif_passe_simple]
rairent	verb	RAIRE	[SUBJ:[@_3p], @indicatif_passe_simple]
//
rairai	verb	RAIRE	[SUBJ:[@_1s], @indicatif_futur_simple]
rairas	verb	RAIRE	[SUBJ:[@_2s], @indicatif_futur_simple]
raira	verb	RAIRE	[SUBJ:[@_3s], @indicatif_futur_simple]
rairons	verb	RAIRE	[SUBJ:[@_1p], @indicatif_futur_simple]
rairez	verb	RAIRE	[SUBJ:[@_2p], @indicatif_futur_simple]
rairont	verb	RAIRE	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// CHANTER
//
chante	verb	CHANTER	[SUBJ:[@_1s], @indicatif_present]
chantes	verb	CHANTER	[SUBJ:[@_2s], @indicatif_present]
chante	verb	CHANTER	[SUBJ:[@_3s], @indicatif_present]
chantons	verb	CHANTER	[SUBJ:[@_1p], @indicatif_present]
chantez	verb	CHANTER	[SUBJ:[@_2p], @indicatif_present]
chantent	verb	CHANTER	[SUBJ:[@_3p], @indicatif_present]
//
chantais	verb	CHANTER	[SUBJ:[@_1s], @indicatif_imparfait]
chantais	verb	CHANTER	[SUBJ:[@_2s], @indicatif_imparfait]
chantait	verb	CHANTER	[SUBJ:[@_3s], @indicatif_imparfait]
chantions	verb	CHANTER	[SUBJ:[@_1p], @indicatif_imparfait]
chantiez	verb	CHANTER	[SUBJ:[@_2p], @indicatif_imparfait]
chantaient	verb	CHANTER	[SUBJ:[@_3p], @indicatif_imparfait]
//
chantai	verb	CHANTER	[SUBJ:[@_1s], @indicatif_passe_simple]
chantas	verb	CHANTER	[SUBJ:[@_2s], @indicatif_passe_simple]
chanta	verb	CHANTER	[SUBJ:[@_3s], @indicatif_passe_simple]
chantâmes	verb	CHANTER	[SUBJ:[@_1p], @indicatif_passe_simple]
chantâtes	verb	CHANTER	[SUBJ:[@_2p], @indicatif_passe_simple]
chantèrent	verb	CHANTER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
chanterai	verb	CHANTER	[SUBJ:[@_1s], @indicatif_futur_simple]
chanteras	verb	CHANTER	[SUBJ:[@_2s], @indicatif_futur_simple]
chantera	verb	CHANTER	[SUBJ:[@_3s], @indicatif_futur_simple]
chanterons	verb	CHANTER	[SUBJ:[@_1p], @indicatif_futur_simple]
chanterez	verb	CHANTER	[SUBJ:[@_2p], @indicatif_futur_simple]
chanteront	verb	CHANTER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// CACARDER
//
cacarde	verb	CACARDER	[SUBJ:[@_1s], @indicatif_present]
cacardes	verb	CACARDER	[SUBJ:[@_2s], @indicatif_present]
cacarde	verb	CACARDER	[SUBJ:[@_3s], @indicatif_present]
cacardons	verb	CACARDER	[SUBJ:[@_1p], @indicatif_present]
cacardez	verb	CACARDER	[SUBJ:[@_2p], @indicatif_present]
cacardent	verb	CACARDER	[SUBJ:[@_3p], @indicatif_present]
//
cacardais	verb	CACARDER	[SUBJ:[@_1s], @indicatif_imparfait]
cacardais	verb	CACARDER	[SUBJ:[@_2s], @indicatif_imparfait]
cacardait	verb	CACARDER	[SUBJ:[@_3s], @indicatif_imparfait]
cacardions	verb	CACARDER	[SUBJ:[@_1p], @indicatif_imparfait]
cacardiez	verb	CACARDER	[SUBJ:[@_2p], @indicatif_imparfait]
cacardaient	verb	CACARDER	[SUBJ:[@_3p], @indicatif_imparfait]
//
cacardai	verb	CACARDER	[SUBJ:[@_1s], @indicatif_passe_simple]
cacardas	verb	CACARDER	[SUBJ:[@_2s], @indicatif_passe_simple]
cacarda	verb	CACARDER	[SUBJ:[@_3s], @indicatif_passe_simple]
cacardâmes	verb	CACARDER	[SUBJ:[@_1p], @indicatif_passe_simple]
cacardâtes	verb	CACARDER	[SUBJ:[@_2p], @indicatif_passe_simple]
cacardèrent	verb	CACARDER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
cacarderai	verb	CACARDER	[SUBJ:[@_1s], @indicatif_futur_simple]
cacarderas	verb	CACARDER	[SUBJ:[@_2s], @indicatif_futur_simple]
cacardera	verb	CACARDER	[SUBJ:[@_3s], @indicatif_futur_simple]
cacarderons	verb	CACARDER	[SUBJ:[@_1p], @indicatif_futur_simple]
cacarderez	verb	CACARDER	[SUBJ:[@_2p], @indicatif_futur_simple]
cacarderont	verb	CACARDER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// GLOUGLOUTER
//
glougloute	verb	GLOUGLOUTER	[SUBJ:[@_1s], @indicatif_present]
glougloutes	verb	GLOUGLOUTER	[SUBJ:[@_2s], @indicatif_present]
glougloute	verb	GLOUGLOUTER	[SUBJ:[@_3s], @indicatif_present]
glougloutons	verb	GLOUGLOUTER	[SUBJ:[@_1p], @indicatif_present]
glougloutez	verb	GLOUGLOUTER	[SUBJ:[@_2p], @indicatif_present]
glougloutent	verb	GLOUGLOUTER	[SUBJ:[@_3p], @indicatif_present]
//
glougloutais	verb	GLOUGLOUTER	[SUBJ:[@_1s], @indicatif_imparfait]
glougloutais	verb	GLOUGLOUTER	[SUBJ:[@_2s], @indicatif_imparfait]
glougloutait	verb	GLOUGLOUTER	[SUBJ:[@_3s], @indicatif_imparfait]
glougloutions	verb	GLOUGLOUTER	[SUBJ:[@_1p], @indicatif_imparfait]
glougloutiez	verb	GLOUGLOUTER	[SUBJ:[@_2p], @indicatif_imparfait]
glougloutaient	verb	GLOUGLOUTER	[SUBJ:[@_3p], @indicatif_imparfait]
//
glougloutai	verb	GLOUGLOUTER	[SUBJ:[@_1s], @indicatif_passe_simple]
glougloutas	verb	GLOUGLOUTER	[SUBJ:[@_2s], @indicatif_passe_simple]
glouglouta	verb	GLOUGLOUTER	[SUBJ:[@_3s], @indicatif_passe_simple]
glougloutâmes	verb	GLOUGLOUTER	[SUBJ:[@_1p], @indicatif_passe_simple]
glougloutâtes	verb	GLOUGLOUTER	[SUBJ:[@_2p], @indicatif_passe_simple]
glougloutèrent	verb	GLOUGLOUTER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
glouglouterai	verb	GLOUGLOUTER	[SUBJ:[@_1s], @indicatif_futur_simple]
glouglouteras	verb	GLOUGLOUTER	[SUBJ:[@_2s], @indicatif_futur_simple]
glougloutera	verb	GLOUGLOUTER	[SUBJ:[@_3s], @indicatif_futur_simple]
glouglouterons	verb	GLOUGLOUTER	[SUBJ:[@_1p], @indicatif_futur_simple]
glouglouterez	verb	GLOUGLOUTER	[SUBJ:[@_2p], @indicatif_futur_simple]
glouglouteront	verb	GLOUGLOUTER	[SUBJ:[@_3p], @indicatif_futur_simple]
//
//
// MEUGLER
//
meugle	verb	MEUGLER	[SUBJ:[@_1s], @indicatif_present]
meugles	verb	MEUGLER	[SUBJ:[@_2s], @indicatif_present]
meugle	verb	MEUGLER	[SUBJ:[@_3s], @indicatif_present]
meuglons	verb	MEUGLER	[SUBJ:[@_1p], @indicatif_present]
meuglez	verb	MEUGLER	[SUBJ:[@_2p], @indicatif_present]
meuglent	verb	MEUGLER	[SUBJ:[@_3p], @indicatif_present]
//
meuglais	verb	MEUGLER	[SUBJ:[@_1s], @indicatif_imparfait]
meuglais	verb	MEUGLER	[SUBJ:[@_2s], @indicatif_imparfait]
meuglait	verb	MEUGLER	[SUBJ:[@_3s], @indicatif_imparfait]
meuglions	verb	MEUGLER	[SUBJ:[@_1p], @indicatif_imparfait]
meugliez	verb	MEUGLER	[SUBJ:[@_2p], @indicatif_imparfait]
meuglaient	verb	MEUGLER	[SUBJ:[@_3p], @indicatif_imparfait]
//
meuglai	verb	MEUGLER	[SUBJ:[@_1s], @indicatif_passe_simple]
meuglas	verb	MEUGLER	[SUBJ:[@_2s], @indicatif_passe_simple]
meugla	verb	MEUGLER	[SUBJ:[@_3s], @indicatif_passe_simple]
meuglâmes	verb	MEUGLER	[SUBJ:[@_1p], @indicatif_passe_simple]
meuglâtes	verb	MEUGLER	[SUBJ:[@_2p], @indicatif_passe_simple]
meuglèrent	verb	MEUGLER	[SUBJ:[@_3p], @indicatif_passe_simple]
//
meuglerai	verb	MEUGLER	[SUBJ:[@_1s], @indicatif_futur_simple]
meugleras	verb	MEUGLER	[SUBJ:[@_2s], @indicatif_futur_simple]
meuglera	verb	MEUGLER	[SUBJ:[@_3s], @indicatif_futur_simple]
meuglerons	verb	MEUGLER	[SUBJ:[@_1p], @indicatif_futur_simple]
meuglerez	verb	MEUGLER	[SUBJ:[@_2p], @indicatif_futur_simple]
meugleront	verb	MEUGLER	[SUBJ:[@_3p], @indicatif_futur_simple]
// end
EOT,
                'post_morpho' => <<<'EOT'
// FORM BEFORE => FORM AFTER
(^| )de le => \1du
(^| )de les => \1des
(^| )à le => \1au
(^| )à les => \1aux
(^| )le (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1l'\2
(^| )la (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1l'\2
(^| )de (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1d'\2
(^| )je (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1j'\2
(^| )me (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1m'\2
(^| )ma (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1mon \2
(^| )ta (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1ton \2
(^| )sa (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1son \2
(^| )te (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1t'\2
(^| )se (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1s'\2
(^| )ne (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1n'\2
(^| )que (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1qu'\2
(^| )ce (a|â|e|é|è|ê|i|î|o|ô|u|û) => \1cet \2
(^| )si il => \1s'il
(^| )si ils => \1s'ils
^(.) => upper(\1)
\ \. => .
EOT,
                'input_text' => <<<'EOT'
// SYMBOL	FEATURES
S [HEAD:CRIER, i:[HEAD:ANIMAL, @s, @def], TENSE:present]
EOT, 
               'is_example' => true,
            ],
        ];
}    
}