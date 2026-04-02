from src.consts import WORD_SIZE, ONE, FRACDIGITS
from src.binutils import inverse, inverseRevBin

#task3
def minus(bin1, bin2):
    bin2i = inverse(bin2.copy())
    bin2i = inverseRevBin(bin2i)
    bin2i = add(bin2i, ONE)
    sum = add(bin1, bin2i)
    return sum

# task 2
def add(bin1, bin2):
    sum = [0]*WORD_SIZE
    car = 0
    for i in range(31, -1, -1):
        s = bin1[i] + bin2[i] + car
        sum[i] = s % 2
        car = s // 2
    return sum

# task 4
def multiply(bin1, bin2):
    sign = bin1[0] ^ bin2[0]
    
    m1 = bin1[1:]
    m2 = bin2[1:]

    temp = [0] * (len(m1) + len(m2))
    
    for i in range(len(m2) - 1, -1, -1):
        if m2[i] == 1:
            carry = 0
            for j in range(len(m1) - 1, -1, -1):
                idx = i + j + 1
                s = temp[idx] + m1[j] + carry
                temp[idx] = s % 2
                carry = s // 2
            temp[i] += carry


    cutbin = temp[-(WORD_SIZE - 1):]
    
    return [sign] + cutbin

def divide(bin1, bin2) -> tuple[int, list[int], list[int]]:
    """
    Деление двух чисел в прямом коде с фиксированной точкой
    a / b
    """
    if all(x == 0 for x in bin2):
        raise ValueError("Деление на ноль")

    # 1. Знак результата = XOR знаковых битов
    sign = bin1[0] ^ bin2[0]

    # 2. Модули чисел (без знакового бита)
    absA = bin1[1:]
    absB = bin2[1:]

    # 3. Перевод в целые для удобства
    numA = int(''.join(map(str, absA)), 2)
    numB = int(''.join(map(str, absB)), 2)

    if numA == 0:
        return sign, [0] * WORD_SIZE, [0] * WORD_SIZE

    # Целая часть
    integerPartValue = numA // numB

    # Остаток для дробной части
    remainder = numA % numB

    # Дробная часть (WORD_SIZE бит после точки)
    fractionBits = []
    for _ in range(WORD_SIZE):
        remainder *= 2
        bit = 1 if remainder >= numB else 0
        fractionBits.append(bit)
        if bit:
            remainder -= numB

    # Ограничиваем целую часть до WORD_SIZE бит
    integerBin = bin(integerPartValue)[2:]
    integerBin = integerBin.zfill(WORD_SIZE)[-WORD_SIZE:]
    integerPart = [int(bit) for bit in integerBin]

    fractionPart = fractionBits[:WORD_SIZE]

    return sign, integerPart, fractionPart
