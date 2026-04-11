import itertools
from typing import Tuple
from core.analyzer import TruthTable

def is_post_t0(table: TruthTable) -> bool: return table[0][1] == 0
def is_post_t1(table: TruthTable) -> bool: return table[-1][1] == 1

def is_post_self_dual(table: TruthTable) -> bool:
    length = len(table)
    return all(table[i][1] != table[length - 1 - i][1] for i in range(length // 2))

def is_post_monotonic(table: TruthTable) -> bool:
    """Проверяет монотонность: если набор A <= B, то f(A) <= f(B)."""
    def bitwise_le(t1: Tuple[int, ...], t2: Tuple[int, ...]) -> bool:
        return all(v1 <= v2 for v1, v2 in zip(t1, t2))
        
    pairs = itertools.combinations(table, 2)
    # Ищем контрпримеры
    violations = filter(lambda p: bitwise_le(p[0][0], p[1][0]) and p[0][1] > p[1][1], pairs)
    return not any(violations)

def build_zhegalkin_coeffs(table: TruthTable) -> Tuple[int, ...]:
    """Метод треугольника для коэффициентелей полинома Жегалкина."""
    def next_row(row: Tuple[int, ...]) -> Tuple[int, ...]:
        return tuple(row[i] ^ row[i+1] for i in range(len(row)-1))
        
    def recurse(current: Tuple[int, ...], acc: Tuple[int, ...]) -> Tuple[int, ...]:
        if not current: return acc
        return recurse(next_row(current), acc + (current[0],))
        
    return recurse(tuple(row[1] for row in table), tuple())

def is_post_linear(coeffs: Tuple[int, ...]) -> bool:
    """Функция линейна, если все коэффициенты с весом индекса > 1 равны 0."""
    def weight(n: int) -> int: return bin(n).count('1')
    non_linear_terms = filter(lambda t: weight(t[0]) > 1 and t[1] == 1, enumerate(coeffs))
    return not any(non_linear_terms)

def get_zhegalkin_coeffs(values: Tuple[int, ...]) -> Tuple[int, ...]:
    """Рассчитывает коэффициенты полинома Жегалкина методом треугольника."""
    res = list(values)
    coeffs = [res[0]]
    for i in range(1, len(res)):
        for j in range(len(res) - 1, i - 1, -1):
            res[j] = res[j] ^ res[j-1]
        coeffs.append(res[i])
    return tuple(coeffs)

def format_zhegalkin(coeffs: Tuple[int, ...], vars_tuple: Tuple[str, ...]) -> str:
    """Формирует строковое представление полинома (например, 1 ⊕ a ⊕ ab)."""
    terms = []
    n = len(vars_tuple)
    for i, coeff in enumerate(coeffs):
        if coeff == 1:
            if i == 0:
                terms.append("1")
            else:
                # Определяем переменные по битам индекса
                active_vars = [vars_tuple[j] for j in range(n) if (i >> (n - 1 - j)) & 1]
                terms.append("".join(active_vars))
    return " ⊕ ".join(terms) if terms else "0"