#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import re
import sys
import unicodedata

LETTER = r"[^\W\d_]"
WORD = rf"{LETTER}+(?:[-’']{LETTER}+)*"

VOWELS = set(
    "aeiouAEIOU"
    "àÀâÂäÄæÆ"
    "éÉèÈêÊëË"
    "îÎïÏ"
    "ôÔöÖœŒ"
    "ùÙûÛüÜ"
)

H_ASPIRE = {
    "hache", "haie", "haillon", "haine", "haïr", "halage", "haleine",
    "hall", "halle", "halte", "hamac", "hambourg", "hameau", "hampe", "hamster",
    "hanche", "handicap", "hangar", "hanneton", "hanter", "happer",
    "harangue", "haras", "harceler", "hardes", "hardi", "hareng",
    "haricot", "harnais", "harpe", "hasard", "hâte", "hausse",
    "haut", "hauteur", "havane", "havre", "hennir", "héraut",
    "hérisson", "héron", "héros", "hêtre", "heurter", "hibou", "hideux",
    "hiérarchie", "hisser", "hyène", "hockey", "hollande", "homard", "hongre", "hongrie", "honte",
    "hoquet", "hors", "houblon", "houille", "houle", "housse", "houx",
    "huche", "huer", "huit", "hurler", "hutte",
}

CONTRACTIONS = {
    ("de", "le"): "du",
    ("de", "les"): "des",
    ("à", "le"): "au",
    ("à", "les"): "aux",
}

ELISION_PREFIXES = {
    "le": "l'",
    "la": "l'",
    "de": "d'",
    "je": "j'",
    "me": "m'",
    "te": "t'",
    "se": "s'",
    "ce": "c'",
    "ne": "n'",
    "que": "qu'",
    "jusque": "jusqu'",
    "lorsque": "lorsqu'",
    "puisque": "puisqu'",
    "quoique": "quoiqu'",
}

MULTIWORD_ELISIONS = {
    "parce que": "parce qu'",
    "quoi que": "quoi qu'",
    "tel que": "tel qu'",
}

POSSESSIVES = {
    "ma": "mon",
    "ta": "ton",
    "sa": "son",
}

PRE_VOWEL_ADJECTIVES = {
    "beau": "bel",
    "nouveau": "nouvel",
    "vieux": "vieil",
}

CE_TO_CET_EXCEPTIONS = {
    "est", "était", "étais", "étaient", "été", "être",
}


Y_CONSONANT = {
    "yak", "yack", "yacht", "yachtsman", "yachtsmen", "yaourt", "yogourt",
    "yoga", "yogi", "yéti", "yeti", "yuan", "yen",
}


def strip_accents(value: str) -> str:
    return "".join(
        char
        for char in unicodedata.normalize("NFD", value)
        if unicodedata.category(char) != "Mn"
    )


def normalize_word(value: str) -> str:
    return value.replace("’", "'").casefold()


def h_key(word: str) -> str:
    first_part = normalize_word(word.split("-")[0])
    return strip_accents(first_part)


def is_h_aspire(word: str) -> bool:
    key = h_key(word)
    candidates = {key}

    if key.endswith(("s", "x")) and len(key) > 1:
        candidates.add(key[:-1])
    if key.endswith("es") and len(key) > 2:
        candidates.add(key[:-2])
    if key.endswith("e") and len(key) > 1:
        candidates.add(key[:-1])

    h_aspire = {strip_accents(item.casefold()) for item in H_ASPIRE}
    return any(candidate in h_aspire for candidate in candidates)


def is_y_consonant(word: str) -> bool:
    key = strip_accents(normalize_word(word.split("-")[0]))
    candidates = {key}

    if key.endswith(("s", "x")) and len(key) > 1:
        candidates.add(key[:-1])

    return any(candidate in Y_CONSONANT for candidate in candidates)


def starts_with_vowel_or_mute_h(word: str) -> bool:
    if not word:
        return False

    first = word[0]

    if first in "yY":
        return not is_y_consonant(word)

    if first in VOWELS:
        return True

    if first in "hH":
        return not is_h_aspire(word)

    return False


def style_like(source: str, replacement: str) -> str:
    if source.isupper():
        return replacement.upper()
    if source[:1].isupper():
        return replacement[:1].upper() + replacement[1:]
    return replacement


def style_like_phrase(source: str, replacement: str) -> str:
    words = source.split()

    if words and all(word.isupper() for word in words):
        return replacement.upper()

    if source[:1].isupper():
        return replacement[:1].upper() + replacement[1:]

    return replacement


def apply_article_contractions(text: str) -> str:
    first_words = sorted({first for first, _ in CONTRACTIONS}, key=len, reverse=True)
    second_words = sorted({second for _, second in CONTRACTIONS}, key=len, reverse=True)

    first_pattern = "|".join(re.escape(word) for word in first_words)
    second_pattern = "|".join(re.escape(word) for word in second_words)

    pattern = re.compile(
        rf"(?<!{LETTER})({first_pattern})\s+({second_pattern})(?!{LETTER})",
        re.IGNORECASE,
    )

    def replace(match: re.Match) -> str:
        first = match.group(1)
        second = match.group(2)
        contracted = CONTRACTIONS.get((normalize_word(first), normalize_word(second)))

        if contracted is None:
            return match.group(0)

        return style_like_phrase(first + " " + second, contracted)

    return pattern.sub(replace, text)


def apply_si_il(text: str) -> str:
    pattern = re.compile(
        rf"(?<!{LETTER})(si)\s+(il|ils)(?!{LETTER})",
        re.IGNORECASE,
    )

    def replace(match: re.Match) -> str:
        si = match.group(1)
        pronoun = match.group(2)
        return style_like(si, "s'") + pronoun

    return pattern.sub(replace, text)


def apply_multiword_elisions(text: str) -> str:
    phrases = sorted(MULTIWORD_ELISIONS, key=len, reverse=True)
    pattern = re.compile(
        rf"(?<!{LETTER})({'|'.join(re.escape(phrase) for phrase in phrases)})\s+({WORD})",
        re.IGNORECASE,
    )

    def replace(match: re.Match) -> str:
        phrase = match.group(1)
        next_word = match.group(2)

        if not starts_with_vowel_or_mute_h(next_word):
            return match.group(0)

        replacement = MULTIWORD_ELISIONS[normalize_word(phrase)]
        return style_like_phrase(phrase, replacement) + next_word

    return pattern.sub(replace, text)


def apply_ce_special_cases(text: str) -> str:
    pattern = re.compile(
        rf"(?<!{LETTER})(ce)\s+({WORD})",
        re.IGNORECASE,
    )

    def replace(match: re.Match) -> str:
        ce = match.group(1)
        next_word = match.group(2)

        if not starts_with_vowel_or_mute_h(next_word):
            return match.group(0)

        if normalize_word(next_word) in CE_TO_CET_EXCEPTIONS:
            return style_like(ce, "c'") + next_word

        return style_like(ce, "cet") + " " + next_word

    return pattern.sub(replace, text)


def apply_possessives(text: str) -> str:
    words = sorted(POSSESSIVES, key=len, reverse=True)
    pattern = re.compile(
        rf"(?<!{LETTER})({'|'.join(re.escape(word) for word in words)})\s+({WORD})",
        re.IGNORECASE,
    )

    def replace(match: re.Match) -> str:
        determiner = match.group(1)
        next_word = match.group(2)

        if not starts_with_vowel_or_mute_h(next_word):
            return match.group(0)

        replacement = POSSESSIVES[normalize_word(determiner)]
        return style_like(determiner, replacement) + " " + next_word

    return pattern.sub(replace, text)


def apply_pre_vowel_adjectives(text: str) -> str:
    words = sorted(PRE_VOWEL_ADJECTIVES, key=len, reverse=True)
    pattern = re.compile(
        rf"(?<!{LETTER})({'|'.join(re.escape(word) for word in words)})\s+({WORD})",
        re.IGNORECASE,
    )

    def replace(match: re.Match) -> str:
        adjective = match.group(1)
        next_word = match.group(2)

        if not starts_with_vowel_or_mute_h(next_word):
            return match.group(0)

        replacement = PRE_VOWEL_ADJECTIVES[normalize_word(adjective)]
        return style_like(adjective, replacement) + " " + next_word

    return pattern.sub(replace, text)


def apply_simple_elisions(text: str) -> str:
    words = sorted(ELISION_PREFIXES, key=len, reverse=True)
    pattern = re.compile(
        rf"(?<!{LETTER})({'|'.join(re.escape(word) for word in words)})\s+({WORD})",
        re.IGNORECASE,
    )

    def replace(match: re.Match) -> str:
        prefix = match.group(1)
        next_word = match.group(2)

        if not starts_with_vowel_or_mute_h(next_word):
            return match.group(0)

        replacement = ELISION_PREFIXES[normalize_word(prefix)]
        return style_like(prefix, replacement) + next_word

    return pattern.sub(replace, text)


def fix_spacing_and_punctuation(text: str) -> str:
    text = text.replace("’", "'")
    text = re.sub(r"[ \t]+([.,])", r"\1", text)
    text = re.sub(r"[ \t]+([!?;:])", r"\1", text)
    text = re.sub(r"[ \t]{2,}", " ", text)
    text = re.sub(r"[ \t]+\n", "\n", text)
    return text


def capitalize_sentences(text: str) -> str:
    pattern = re.compile(rf"(^|[.!?]\s+|\n\s*)({LETTER})", re.MULTILINE)

    def replace(match: re.Match) -> str:
        return match.group(1) + match.group(2).upper()

    return pattern.sub(replace, text)


def transform_morphology(text: str) -> str:
    text = apply_article_contractions(text)
    text = apply_si_il(text)
    text = apply_multiword_elisions(text)
    text = apply_ce_special_cases(text)
    text = apply_possessives(text)
    text = apply_pre_vowel_adjectives(text)
    text = apply_simple_elisions(text)
    text = fix_spacing_and_punctuation(text)
    text = capitalize_sentences(text)
    return text


def main() -> int:
    sys.stdout.write(transform_morphology(sys.stdin.read()))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
