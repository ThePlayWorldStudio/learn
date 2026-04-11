import itertools
from functools import reduce
from typing import Tuple
from parser.ast_builder import build_ast, get_variables_from_ast, evaluate_ast

TruthTable = Tuple[Tuple[Tuple[int, ...], int], ...]

def generate_truth_table(expression: str) -> Tuple[Tuple[str, ...], TruthTable]:
    """Генерирует таблицу истинности, прогоняя AST через все комбинации."""
    ast_root = build_ast(expression)
    vars_tuple = tuple(sorted(set(get_variables_from_ast(ast_root))))
    combinations = tuple(itertools.product((0, 1), repeat=len(vars_tuple)))
    
    table = tuple(
        (vals, evaluate_ast(ast_root, dict(zip(vars_tuple, vals))))
        for vals in combinations
    )
    return vars_tuple, table

def get_boolean_derivative(table: TruthTable, var_idx: int) -> TruthTable:
    """Вычисляет частную производную, уменьшая размерность таблицы на 1 переменную."""
    new_table = []
    seen = set()
    
    for row in table:
        # Оставляем значения всех переменных, кроме var_idx
        rem_vals = tuple(v for i, v in enumerate(row[0]) if i != var_idx)
        if rem_vals in seen:
            continue
        seen.add(rem_vals)
        
        # Находим индексы строк, где var_idx равен 0 и 1
        val0 = list(row[0])
        val0[var_idx] = 0
        val1 = list(row[0])
        val1[var_idx] = 1
        
        idx0 = int("".join(map(str, val0)), 2)
        idx1 = int("".join(map(str, val1)), 2)
        
        df = table[idx0][1] ^ table[idx1][1]
        new_table.append((rem_vals, df))
        
    return tuple(new_table)

def find_dummy_variables(table: TruthTable, var_count: int) -> Tuple[int, ...]:
    """Переменная фиктивна, если производная по ней равна 0 на всех наборах."""
    def is_dummy(var_idx: int) -> bool:
        derivative = get_boolean_derivative(table, var_idx)
        return all(row[1] == 0 for row in derivative)
        
    return tuple(filter(is_dummy, range(var_count)))

def get_standard_forms(table: TruthTable, vars_tuple: Tuple[str, ...]) -> Tuple[str, str]:
    """Генерирует СДНФ и СКНФ в строковом виде."""
    sdnf_parts, sknf_parts = [], []
    for row in table:
        vals, res = row[0], row[1]
        if res == 1:
            part = " & ".join([f"{var}" if val == 1 else f"!{var}" for var, val in zip(vars_tuple, vals)])
            sdnf_parts.append(f"({part})")
        else:
            part = " | ".join([f"!{var}" if val == 1 else f"{var}" for var, val in zip(vars_tuple, vals)])
            sknf_parts.append(f"({part})")
            
    sdnf = " | ".join(sdnf_parts) if sdnf_parts else "0 (Тождественно ложна)"
    sknf = " & ".join(sknf_parts) if sknf_parts else "1 (Тождественно истинна)"
    return sdnf, sknf

def get_numeric_forms(table: TruthTable) -> Tuple[Tuple[int, ...], Tuple[int, ...]]:
    """Возвращает числовые формы для СДНФ (индексы 1) и СКНФ (индексы 0)."""
    sdnf_nums = tuple(i for i, row in enumerate(table) if row[1] == 1)
    sknf_nums = tuple(i for i, row in enumerate(table) if row[1] == 0)
    return sdnf_nums, sknf_nums

def get_index_form(table: TruthTable) -> int:
    """Вычисляет индексную форму функции (перевод столбца значений в 10-ю СС)."""
    bin_str = "".join(str(row[1]) for row in table)
    return int(bin_str, 2)