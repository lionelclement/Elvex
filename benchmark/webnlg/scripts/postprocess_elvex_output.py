#!/usr/bin/env python3
from __future__ import annotations

import re
import sys

PUNCT_RE = re.compile(r"\s+([.,;:!?])")
SPACE_RE = re.compile(r"[ \t]+")
A_BEFORE_VOWEL_RE = re.compile(r"\ba\s+([aeiouAEIOU])")
ABBREV_DOUBLE_DOT_RE = re.compile(r"\b((?:[A-Za-z]\.){2,})\.")
RUNWAY_SINGLE_QUOTE_RE = re.compile(r"(\b\d{1,2}[A-Z]?/\d{1,2}[A-Z]?\b) \'([^\']+)\'")
DBPEDIA_DISAMBIG_RE = re.compile(r"\s+\((?:band|singer|musician|album|song|record_label|record label|comics?|comic(?:s)? character|character|novel|film|movie|book|publication|restaurant|company)\)", re.I)
MC_NAME_RE = re.compile(r"\bMc ([A-Z])")


def fix_mojibake(text: str) -> str:
    """Repair common UTF-8 decoded-as-Latin-1 mojibake seen in WebNLG names."""
    if "Ã" not in text and "Â" not in text:
        return text
    try:
        repaired = text.encode("latin1").decode("utf-8")
    except UnicodeError:
        return text
    # Keep the repaired form only if it looks strictly cleaner.
    if repaired.count("Ã") + repaired.count("Â") < text.count("Ã") + text.count("Â"):
        return repaired
    return text


def finalize_sentence(text: str) -> str:
    """Final surface cleanup after Elvex generation.

    Policy for this project:
    - lexical entries stay lowercase unless they are proper nouns;
    - capitalization is applied as a final sentence-level operation;
    - Elvex generates the indefinite article as "a"; postproduction changes
      "a" to "an" before vowel-initial forms;
    - spacing before punctuation is removed;
    - final abbreviations such as "U.S." must not become "U.S..".
    """
    text = fix_mojibake(text.strip())
    text = text.replace("_", " ")
    text = SPACE_RE.sub(" ", text)
    text = DBPEDIA_DISAMBIG_RE.sub("", text)
    # v34 cleanup for WebNLG pilot frames.
    text = re.sub(r"\s+'s\b", "'s", text)
    text = re.sub(r"\b([A-Za-z]+)\s*,\s*(\d{4})\b", r"\1 \2", text)
    text = text.replace("(dollars)", "dollars")
    text = re.sub(r"\bFLOOR COUNT NOUN\b", "floor count", text)
    text = re.sub(r"\bTOTAL AREA NOUN\b", "total area", text)
    text = re.sub(r"\bWATER AREA NOUN\b", "water area", text)
    text = re.sub(r"\bPOPULATION DENSITY NOUN\b", "population density", text)
    text = re.sub(r"\bAVERAGE SPEED NOUN\b", "average speed", text)
    text = re.sub(r"\bESCAPE VELOCITY NOUN\b", "escape velocity", text)
    text = re.sub(r"\bORBITAL PERIOD NOUN\b", "orbital period", text)
    text = re.sub(r"\bPERIAPSIS NOUN\b", "periapsis", text)
    text = re.sub(r"\bAPOAPSIS NOUN\b", "apoapsis", text)
    text = re.sub(r"\bMASS NOUN\b", "mass", text)
    text = re.sub(r"\bTEMPERATURE NOUN\b", "temperature", text)
    text = re.sub(r"\bAREA CODE NOUN\b", "area code", text)
    text = re.sub(r"\bFORMER NAME NOUN\b", "former name", text)
    text = re.sub(r"\bLARGEST CITY NOUN\b", "largest city", text)
    # POSS_S_REPAIR_V34


    # Repair dangling unit fragments caused by URI/literal edge cases.
    text = re.sub(r"\bsquare\s+Metre>\b", "square metres", text)
    text = re.sub(r"\bcentimetre>\b", "centimetres", text)
    text = re.sub(r"\bkilogram>\b", "kilograms", text)
    text = re.sub(r"\bminute>\b", "minutes", text)
    text = re.sub(r"\bmetre>\b", "metres", text)
    text = MC_NAME_RE.sub(r"Mc\1", text)
    text = A_BEFORE_VOWEL_RE.sub(r"an \1", text)
    text = re.sub(r"\ba Singing\b", "a singer", text)
    text = re.sub(r"\bthe Singing\b", "the voice", text)
    text = re.sub(r"\bSinging is\b", "A singer is", text)
    text = PUNCT_RE.sub(r"\1", text)
    text = ABBREV_DOUBLE_DOT_RE.sub(r"\1", text)
    text = RUNWAY_SINGLE_QUOTE_RE.sub(r"\1 \2", text)
    if not text:
        return text
    return text[0].upper() + text[1:]


def main() -> int:
    for line in sys.stdin:
        line = line.rstrip("\n")
        if line.strip():
            print(finalize_sentence(line))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
