def encodeDigit5421(digit):
    """Превращает цифру в список из 4 бит (5421 BCD)"""
    bits = [0, 0, 0, 0]
    if digit >= 5:
        bits[0] = 1
        remainder = digit - 5
    else:
        bits[0] = 0
        remainder = digit
    
    # Остаток (0-4) кодируем весами 4-2-1
    if remainder >= 4: bits[1] = 1; remainder -= 4
    if remainder >= 2: bits[2] = 1; remainder -= 2
    if remainder >= 1: bits[3] = 1
    return bits

def decodeDigit5421(bits):
    """Превращает список из 4 бит обратно в десятичную цифру"""
    weights = [5, 4, 2, 1]
    digit = 0
    for i in range(4):
        if bits[i] == 1:
            digit += weights[i]
    return digit

def numberToBcdArray(number):
    """Превращает число в список списков (массив нибблов)"""
    return [encodeDigit5421(int(d)) for d in str(number)]

def addBcd5421(bcdArray1, bcdArray2):
    num1 = int("".join(str(decodeDigit5421(b)) for b in bcdArray1))
    num2 = int("".join(str(decodeDigit5421(b)) for b in bcdArray2))
    
    total = num1 + num2
    
    return numberToBcdArray(total)