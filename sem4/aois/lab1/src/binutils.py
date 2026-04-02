from src.consts import WORD_SIZE, ONE

def choosenBitInverse(ind: int, bin):
    if bin[ind] == 0:
        bin[ind] = 1
    elif bin[ind] == 1:
        bin[ind] = 0

def inverse(bin):
    out = bin.copy()
    choosenBitInverse(0, out)
    return out

def inverseRevBin(bin):
    out = bin.copy()
    i = WORD_SIZE-1
    while i > 0:
        choosenBitInverse(i, out)
        i -= 1
    return out

def bitInverse(bit: int):
     match bit:
         case 0:
               bit = 1
         case 1:
               bit = 0