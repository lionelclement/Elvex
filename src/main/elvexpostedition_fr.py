#!/usr/bin/env python3
import re
import sys
import unicodedata

LETTER = r"[^\W\d_]"
WORD = rf"{LETTER}+(?:[-’']{LETTER}+)*"

H_ASPIRE = {
    "hache", "haie", "haine", "haïr", "halage", "haleine", "hall", "halle",
    "halte", "hamac", "hambourg", "hameau", "hampe", "hanche", "handicap",
    "hangar", "hanneton", "hanter", "happer", "harangue", "haras", "harceler",
    "hardes", "hardi", "hareng", "haricot", "harnais", "harpe", "hasard",
    "hâte", "hausse", "haut", "hauteur", "havane", "havre", "hennir",
    "héraut", "hérisson", "héros", "hêtre", "heurter", "hibou", "hideux",
    "hiérarchie", "hisser", "hocher", "hockey", "hollande", "hongrie",
    "honte", "hoquet", "hors", "houblon", "houille", "houle", "housse",
    "houx", "huche", "huer", "huit", "hurler", "hutte",
}

VOWELS = set("aeiouyàâäæéèêëîïôöœùûüAEIOUYÀÂÄÆÉÈÊËÎÏÔÖŒÙÛÜ")

ELISION_PREFIX = {
    "le": "l'",
    "la": "l'",
    "de": "d'",
    "que": "qu'",
    "je": "j'",
    "me": "m'",
    "te": "t'",
    "se": "s'",
    "ne": "n'",
}

CONTRACTIONS = {
    ("de", "le"): "du",
    ("de", "les"): "des",
    ("à", "le"): "au",
    ("à", "les"): "aux",
}

POSSESSIVES = {
    "ma": "mon",
    "ta": "ton",
    "sa": "son",
}

PRE_VOWEL_FORMS = {
    "beau": "bel",
    "nouveau": "nouvel",
    "vieux": "vieil",
}

CE_ELISION_FORMS = {
    "est", "était", "étais", "étaient", "été", "être",
}


def strip_accents(s: str) -> str:
    return "".join(
        c for c in unicodedata.normalize("NFD", s)
        if unicodedata.category(c) != "Mn"
    )


def normalize_word(word: str) -> str:
    return word.replace("’", "'").casefold()


def h_aspire_key(word: str) -> str:
    key = normalize_word(word.split("-")[0])
    return strip_accents(key)


def is_h_aspire(word: str) -> bool:
    key = h_aspire_key(word)
    candidates = {key}
    if key.endswith(("s", "x")) and len(key) > 1:
        candidates.add(key[:-1])
    if key.endswith("es") and len(key) > 2:
        candidates.add(key[:-2])
    if key.endswith("e") and len(key) > 1:
        candidates.add(key[:-1])
    aspirated = {strip_accents(w.casefold()) for w in H_ASPIRE}
    return any(c in aspirated for c in candidates)


def begins_with_vowel_or_mute_h(word: str) -> bool:
    if not word:
        return False
    first = word[0]
    if first in VOWELS:
        return True
    if first in "hH":
        return not is_h_aspire(word)
    return False


def style_like(src: str, replacement_lower: str) -> str:
    if src.isupper():
        return replacement_lower.upper()
    if src[:1].isupper():
        return replacement_lower[:1].upper() + replacement_lower[1:]
    return replacement_lower


def style_phrase(src1: str, src2: str, replacement_lower: str) -> str:
    if src1.isupper() and src2.isupper():
        return replacement_lower.upper()
    if src1[:1].isupper():
        return replacement_lower[:1].upper() + replacement_lower[1:]
    return replacement_lower


def apply_contractions(text: str) -> str:
    first = "|".join(re.escape(k[0]) for k in sorted(set(CONTRACTIONS)))
    second = "|".join(re.escape(k[1]) for k in sorted({k[1] for k in CONTRACTIONS}))
    rx = re.compile(rf"(?<!{LETTER})({first})\s+({second})(?!{LETTER})", re.IGNORECASE)

    def repl(match: re.Match) -> str:
        a, b = match.group(1), match.group(2)
        out = CONTRACTIONS.get((a.casefold(), b.casefold()))
        if out is None:
            return match.group(0)
        return style_phrase(a, b, out)

    return rx.sub(repl, text)


def apply_si_elision(text: str) -> str:
    rx = re.compile(rf"(?<!{LETTER})(si)\s+(il|ils)(?!{LETTER})", re.IGNORECASE)

    def repl(match: re.Match) -> str:
        si, pron = match.group(1), match.group(2)
        return style_like(si, "s'") + pron

    return rx.sub(repl, text)


def apply_ce(text: str) -> str:
    rx = re.compile(rf"(?<!{LETTER})(ce)\s+({WORD})", re.IGNORECASE)

    def repl(match: re.Match) -> str:
        ce, word = match.group(1), match.group(2)
        if not begins_with_vowel_or_mute_h(word):
            return match.group(0)
        if normalize_word(word) in CE_ELISION_FORMS:
            return style_like(ce, "c'") + word
        return style_like(ce, "cet") + " " + word

    return rx.sub(repl, text)


def apply_possessives(text: str) -> str:
    words = "|".join(POSSESSIVES)
    rx = re.compile(rf"(?<!{LETTER})({words})\s+({WORD})", re.IGNORECASE)

    def repl(match: re.Match) -> str:
        src, word = match.group(1), match.group(2)
        if not begins_with_vowel_or_mute_h(word):
            return match.group(0)
        return style_like(src, POSSESSIVES[src.casefold()]) + " " + word

    return rx.sub(repl, text)


def apply_pre_vowel_forms(text: str) -> str:
    words = "|".join(PRE_VOWEL_FORMS)
    rx = re.compile(rf"(?<!{LETTER})({words})\s+({WORD})", re.IGNORECASE)

    def repl(match: re.Match) -> str:
        src, word = match.group(1), match.group(2)
        if not begins_with_vowel_or_mute_h(word):
            return match.group(0)
        return style_like(src, PRE_VOWEL_FORMS[src.casefold()]) + " " + word

    return rx.sub(repl, text)


def apply_elisions(text: str) -> str:
    words = "|".join(ELISION_PREFIX)
    rx = re.compile(rf"(?<!{LETTER})({words})\s+({WORD})", re.IGNORECASE)

    def repl(match: re.Match) -> str:
        src, word = match.group(1), match.group(2)
        if not begins_with_vowel_or_mute_h(word):
            return match.group(0)
        return style_like(src, ELISION_PREFIX[src.casefold()]) + word

    return rx.sub(repl, text)


def fix_punctuation(text: str) -> str:
    text = re.sub(r"[ \t]+([.,])", r"\1", text)
    text = re.sub(r"[ \t]+([!?;:])", r"\1", text)
    text = re.sub(r"([«])\s+", r"\1", text)
    text = re.sub(r"\s+([»])", r"\1", text)
    text = re.sub(r"[ \t]{2,}", " ", text)
    return text


def capitalize_sentences(text: str) -> str:
    rx = re.compile(rf"(^|[.!?]\s+|\n\s*)({LETTER})", re.MULTILINE)

    def repl(match: re.Match) -> str:
        return match.group(1) + match.group(2).upper()

    return rx.sub(repl, text)


def postedition_fr(text: str) -> str:
    text = apply_contractions(text)
    text = apply_si_elision(text)
    text = apply_ce(text)
    text = apply_possessives(text)
    text = apply_pre_vowel_forms(text)
    text = apply_elisions(text)
    text = fix_punctuation(text)
    text = capitalize_sentences(text)
    return text


def main() -> int:
    sys.stdout.write(postedition_fr(sys.stdin.read()))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
