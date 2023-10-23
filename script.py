import sys

num_forms = 32
num_lemmas = 1000
#It will take a while !
#num_forms = 32
#num_lemmas = 100

with open(sys.argv[1], "w") as morphoFile:
    k = 0
    for i in range(1, num_lemmas + 1):
        for j in range(1, num_forms + 1):
            form = f"FORM_{i}_{j}"
            pos = f"POS_{i%2}"
            lemma = f"LEMMA_{i}"
            features = f"attrMorpho:_{i%17},attrInteger:{k},attrString:\"{k}\""
            line = f"{form}\t{pos}\t{lemma}\t[{features}]\n"
            morphoFile.write(line)
            k = k+1

with open(sys.argv[2], "w") as patternFile:
    for i in range(1, num_lemmas + 1):
        lexeme= f"LEXEME_{i}"
        pos = f"POS_{i%2}"
        lemma = f"LEMMA_{i}"
        features = f"attrPattern:_{i%13}"
        line = f"{lexeme}\t{pos}\t{lemma}\t[{features}]\n"
        patternFile.write(line)
