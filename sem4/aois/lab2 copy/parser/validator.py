# validator.py
import re

ALLOWED_VARS = {'a', 'b', 'c', 'd', 'e'}
ALLOWED_OPS = {'&', '|', '!', '-', '>', '~', '(', ')'}

def validate_input(expression: str) -> str:
    # Убираем все пробелы сразу, они нам не нужны
    expr = expression.replace(" ", "")
    
    if not expr:
        raise ValueError("Строка пуста. Введите логическое выражение.")

    if "()" in expr:
        raise ValueError("Обнаружены пустые скобки.")

    # Проверка на недопустимые символы
    chars = set(expr)
    invalid = chars - ALLOWED_VARS - ALLOWED_OPS - {str(i) for i in range(10)}
    if invalid:
        raise ValueError(f"Использованы запрещенные символы: {invalid}")

    vars_found = set(re.findall(r'[a-e]', expr))
    if len(vars_found) > 5:
        raise ValueError(f"Слишком много переменных ({len(vars_found)}). Максимум — 5 (a, b, c, d, e).")
    
    # Проверка на дурака: если пользователь ввел минус, но не стрелку
    if '-' in expr and '->' not in expr:
         raise ValueError("Символ '-' можно использовать только в составе импликации '->'.")
         
    return expr