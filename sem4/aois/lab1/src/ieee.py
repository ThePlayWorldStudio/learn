BIAS = 127

def ieeeToFloat(binaryArray):
    if len(binaryArray) != 32:
        raise ValueError("Массив должен содержать ровно 32 бита")

    sign = binaryArray[0]
    
    # Считаем экспоненту (8 бит)
    expBits = binaryArray[1:9]
    exponent = 0
    for i, bit in enumerate(reversed(expBits)):
        exponent += bit * (2 ** i)
        
    # Считаем мантиссу (23 бита)
    fracBits = binaryArray[9:32]
    fraction = 0
    for i, bit in enumerate(fracBits):
        fraction += bit * (2 ** -(i + 1))
        
    # Обработка чистого нуля (экспонента 0, мантисса 0)
    if exponent == 0 and fraction == 0:
        return -0.0 if sign == 1 else 0.0
        
    # Сборка числа
    value = (1.0 + fraction) * (2 ** (exponent - 127))
    
    return -value if sign == 1 else value

def floatToIeee(value):
    # Хак для проверки "отрицательного нуля" (-0.0) без библиотек
    if value == 0.0:
        isNegativeZero = str(value).startswith('-')
        sign = 1 if isNegativeZero else 0
        return [sign] + [0] * 31
        
    # 1. Знак
    sign = 1 if value < 0 else 0
    absVal = abs(value)
    
    # 2. Поиск экспоненты (нормализация)
    exponent = 0
    if absVal >= 1.0:
        while absVal >= 2.0:
            absVal /= 2.0
            exponent += 1
    else:
        while absVal < 1.0:
            absVal *= 2.0
            exponent -= 1
            
    # 3. Экспонента (смещение 127)
    biasedExp = exponent + 127
    expArray = []
    tempExp = biasedExp
    for _ in range(8):
        expArray.insert(0, tempExp % 2)
        tempExp //= 2
        
    # 4. Мантисса (дробная часть от нормализованного числа)
    fraction = absVal - 1.0
    mantissaArray = []
    
    for _ in range(23):
        fraction *= 2.0
        if fraction >= 1.0:
            mantissaArray.append(1)
            fraction -= 1.0
        else:
            mantissaArray.append(0)
            
    return [sign] + expArray + mantissaArray

def unpackParts(ieeeArray):
    sign = ieeeArray[0]
    # Переводим 8 бит экспоненты в число
    exponent = 0
    for bit in ieeeArray[1:9]:
        exponent = (exponent << 1) | bit
    # Переводим 23 бита мантиссы в число и добавляем скрытую единицу
    fraction = 0
    for bit in ieeeArray[9:32]:
        fraction = (fraction << 1) | bit
    
    # Если экспонента не 0, добавляем скрытую единицу (24-й бит)
    mantissa = (1 << 23) | fraction if exponent > 0 else 0
    return sign, exponent, mantissa

def packParts(sign, exponent, mantissa):
    # Отрезаем скрытую единицу
    fractionValue = mantissa & ((1 << 23) - 1)
    
    # Формируем экспоненту (8 бит)
    expBits = []
    for i in range(7, -1, -1):
        expBits.append((exponent >> i) & 1)
        
    # Формируем мантиссу (23 бита)
    fracBits = []
    for i in range(22, -1, -1):
        fracBits.append((fractionValue >> i) & 1)
        
    return [sign] + expBits + fracBits

def unpackParts(ieeeArray):
    sign = ieeeArray[0]
    # Переводим 8 бит экспоненты в число
    exponent = 0
    for bit in ieeeArray[1:9]:
        exponent = (exponent << 1) | bit
    # Переводим 23 бита мантиссы в число и добавляем скрытую единицу
    fraction = 0
    for bit in ieeeArray[9:32]:
        fraction = (fraction << 1) | bit
    
    # Если экспонента не 0, добавляем скрытую единицу (24-й бит)
    mantissa = (1 << 23) | fraction if exponent > 0 else 0
    return sign, exponent, mantissa

def packParts(sign, exponent, mantissa):
    # Отрезаем скрытую единицу
    fractionValue = mantissa & ((1 << 23) - 1)
    
    # Формируем экспоненту (8 бит)
    expBits = []
    for i in range(7, -1, -1):
        expBits.append((exponent >> i) & 1)
        
    # Формируем мантиссу (23 бита)
    fracBits = []
    for i in range(22, -1, -1):
        fracBits.append((fractionValue >> i) & 1)
        
    return [sign] + expBits + fracBits

def multiplyIeee(arr1, arr2):
    s1, e1, m1 = unpackParts(arr1)
    s2, e2, m2 = unpackParts(arr2)
    
    if m1 == 0 or m2 == 0: return [0] * 32
    
    resSign = s1 ^ s2
    resExp = e1 + e2 - 127
    
    # Умножаем 24-битные мантиссы -> получаем 48-битное число
    resMant = m1 * m2
    
    # Нормализация: результат должен начинаться с 23-го бита (после отсечения)
    if resMant & (1 << 47): # Если есть бит на 47-й позиции
        resMant >>= 24
        resExp += 1
    else:
        resMant >>= 23
        
    return packParts(resSign, resExp, resMant)

def divideIeee(arr1, arr2):
    s1, e1, m1 = unpackParts(arr1)
    s2, e2, m2 = unpackParts(arr2)
    
    if m2 == 0: raise ZeroDivisionError("Division by zero")
    if m1 == 0: return [0] * 32
    
    resSign = s1 ^ s2
    resExp = e1 - e2 + 127
    
    # Сдвигаем m1 влево, чтобы при делении получить точность 23 бита
    resMant = (m1 << 23) // m2
    
    # Если результат деления меньше нормализованного (не хватает бита)
    if not (resMant & (1 << 23)):
        resMant <<= 1
        resExp -= 1
        
    return packParts(resSign, resExp, resMant)

def addIeee(arr1, arr2):
    s1, e1, m1 = unpackParts(arr1)
    s2, e2, m2 = unpackParts(arr2)
    
    if m1 == 0: return arr2
    if m2 == 0: return arr1
    
    # 1. Выравнивание: e1 должен быть >= e2
    if e2 > e1:
        s1, s2, e1, e2, m1, m2 = s2, s1, e2, e1, m2, m1
        
    diff = e1 - e2
    if diff > 24: # Второе число слишком мало
        m2 = 0
    else:
        m2 >>= diff
        
    resExp = e1
    
    # 2. Сложение/Вычитание мантисс
    if s1 == s2:
        resSign = s1
        resMant = m1 + m2
    else:
        if m1 >= m2:
            resSign = s1
            resMant = m1 - m2
        else:
            resSign = s2
            resMant = m2 - m1
            
    if resMant == 0: return [0] * 32
    
    # 3. Нормализация
    if resMant & (1 << 24): # Перенос в 25-й бит
        resMant >>= 1
        resExp += 1
    else:
        # Если при вычитании старший бит ушел влево
        while not (resMant & (1 << 23)) and resExp > 0:
            resMant <<= 1
            resExp -= 1
            
    return packParts(resSign, resExp, resMant)

def subIeee(arr1, arr2):
    arr2Inverted = arr2[:]
    arr2Inverted[0] = 1 - arr2Inverted[0]
    return addIeee(arr1, arr2Inverted)