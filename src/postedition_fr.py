import re

def transform_morphology(text):

le, la, de, je, me, te, se, ce, ne, que + 
jusque, lorsque, puisque, quelque, quoique, parce que, quoi que, tel que
si + il
 


    text = re.sub(r'\b([nNdDjJlL])[ea]\s+([hH]?[aAeEiIoOuUyY]|â|Â|à|À|é|É|è|È|ê|Ê|ë|Ë|î|Î|ï|Ï|ö|Ö|ô|Ô|ü|Ü|û|Û)', r"\1'\2", text, flags=re.IGNORECASE)
    text = re.sub(r'\b([mMtTsS])[e]\s+([aAeEiIoOuUyY]|â|Â|à|À|é|É|è|È|ê|Ê|ë|Ë|î|Î|ï|Ï|ö|Ö|ô|Ô|ü|Ü|û|Û)', r"\1'\2", text, flags=re.IGNORECASE)

    return text

# Exemple d'utilisation
input_text = "le haricot"
transformed_text = transform_morphology(input_text)
print(transformed_text)
