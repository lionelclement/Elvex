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
        ];
}    
}