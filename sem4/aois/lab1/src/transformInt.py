from src.consts import WORD_SIZE, ONE
from src.binops import add
from src.binutils import choosenBitInverse

#task 1
def DecToBinP(num: int):
    binp = [0]*WORD_SIZE
    if num<0:
        binp[0] = 1
    temp = abs(num)
    fint = abs(num)
    i = 31
    while temp>0:
        fint = temp//2
        binp[i]=temp%2
        temp=fint
        i-=1
    return binp

def DecToBinRev(num: int):
    binp = DecToBinP(num)
    if binp[0] == 1:
        i = WORD_SIZE-1
        while i > 0:
            choosenBitInverse(i, binp)
            i-=1
    return binp

def DecToDop(num: int):
    binrev = DecToBinRev(num)
    if binrev[0] == 1:
        bindop = add(binrev, ONE)
        return bindop
    else:
        return binrev
    
def fromBinPToDec(bin):
    sign = bin[0]
    magnitudeBits = bin[1:]
    
    value = 0
    for i, bit in enumerate(reversed(magnitudeBits)):
        value += bit * (2 ** i)
        
    return -value if sign == 1 else value

def fromRevBinToDec(bin):
    if bin[0] == 0:
        # Положительное число — считаем как обычно
        return fromBinPToDec(bin)
    
    # Отрицательное число — инвертируем все биты
    invertedBits = [1 - bit for bit in bin]
    
    # Считаем значение инвертированных бит (уже без знака)
    value = 0
    magnitudeBits = invertedBits[1:]
    for i, bit in enumerate(reversed(magnitudeBits)):
        value += bit * (2 ** i)
        
    return -value

def fromDopBinToDec(binaryArray):
    n = len(binaryArray)
    # Вес самого первого (знакового) бита равен -(2^(n-1))
    value = -binaryArray[0] * (2 ** (n - 1))
    
    # Добавляем веса остальных бит
    for i in range(1, n):
        # Позиция бита с конца: (n - 1 - i)
        power = n - 1 - i
        value += binaryArray[i] * (2 ** power)
        
    return value

def fixedToDecimal(sign: int, integerPart: list[int], fractionPart: list[int]) -> float:
    """ Преобразование числа с фиксированной точкой в десятичное """
    # Целая часть
    intValue = 0
    for bit in integerPart:
        intValue = intValue * 2 + bit

    # Дробная часть
    fracValue = 0.0
    power = 0.5
    for bit in fractionPart:
        if bit:
            fracValue += power
        power /= 2

    result = intValue + fracValue
    return -result if sign else result