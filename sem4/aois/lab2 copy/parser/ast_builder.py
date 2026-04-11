from typing import Tuple, Dict, Any, Callable

# Типы узлов: ('VAR', 'a'), ('NOT', node), ('BINOP', '&', left, right)
AstNode = Tuple[str, Any, ...]

def parse_primary(s: str) -> Tuple[AstNode, str]:
    """Парсит базовые элементы: переменные, отрицания и скобки."""
    s = s.lstrip()
    if not s:
        raise ValueError("Неожиданный конец выражения")
    
    if s.startswith('!'):
        node, rest = parse_primary(s[1:])
        return ('NOT', node), rest
        
    if s.startswith('('):
        node, rest = parse_eq(s[1:])
        rest = rest.lstrip()
        if not rest.startswith(')'):
            raise ValueError(f"Ожидалась ')', найдено: {rest}")
        return node, rest[1:]
        
    if s[0].isalpha():
        return ('VAR', s[0]), s[1:]
        
    raise ValueError(f"Неизвестный символ: {s}")

def parse_binary(parser_lower: Callable, op_str: str, s: str) -> Tuple[AstNode, str]:
    """Функциональный генератор для бинарных операторов."""
    left, s_rest = parser_lower(s)
    
    def recurse(left_node: AstNode, current_s: str) -> Tuple[AstNode, str]:
        current_s = current_s.lstrip()
        if current_s.startswith(op_str):
            right_node, next_s = parser_lower(current_s[len(op_str):])
            new_node = ('BINOP', op_str, left_node, right_node)
            return recurse(new_node, next_s)
        return left_node, current_s
        
    return recurse(left, s_rest)

# Цепочка приоритетов (от высшего к низшему): & -> | -> -> -> ~
def parse_and(s: str) -> Tuple[AstNode, str]: return parse_binary(parse_primary, '&', s)
def parse_or(s: str) -> Tuple[AstNode, str]: return parse_binary(parse_and, '|', s)
def parse_impl(s: str) -> Tuple[AstNode, str]: return parse_binary(parse_or, '->', s)
def parse_eq(s: str) -> Tuple[AstNode, str]: return parse_binary(parse_impl, '~', s)

def build_ast(expression: str) -> AstNode:
    """Точка входа для построения AST."""
    node, rest = parse_eq(expression)
    if rest.strip():
        raise ValueError(f"Неразобранный остаток выражения: {rest}")
    return node

def get_variables_from_ast(node: AstNode) -> Tuple[str, ...]:
    """Рекурсивный обход для поиска всех уникальных переменных."""
    if node[0] == 'VAR':
        return (node[1],)
    if node[0] == 'NOT':
        return get_variables_from_ast(node[1])
    if node[0] == 'BINOP':
        return get_variables_from_ast(node[2]) + get_variables_from_ast(node[3])
    return tuple()

def evaluate_ast(node: AstNode, env: Dict[str, int]) -> int:
    """Рекурсивное вычисление значения дерева."""
    if node[0] == 'VAR':
        return env[node[1]]
    if node[0] == 'NOT':
        return int(not evaluate_ast(node[1], env))
    
    op, left, right = node[1], node[2], node[3]
    val_l = evaluate_ast(left, env)
    val_r = evaluate_ast(right, env)
    
    if op == '&': return val_l & val_r
    if op == '|': return val_l | val_r
    if op == '->': return int(val_l <= val_r)
    if op == '~': return int(val_l == val_r)
    raise ValueError(f"Неизвестный оператор: {op}")

def build_ast_safe(expression: str) -> Tuple[str, Any]:
    """
    Безопасная точка входа. Возвращает кортеж (результат, текст_ошибки).
    """
    try:
        # Предварительная очистка
        clean_expr = expression.replace(' ', '')
        
        # Проверка баланса скобок
        if clean_expr.count('(') != clean_expr.count(')'):
            return None, "Ошибка: Нарушен баланс скобок."

        node, rest = parse_eq(clean_expr)
        
        if rest:
            return None, f"Ошибка: Синтаксическая ошибка рядом с '{rest}'. Возможно, пропущен оператор."
            
        return node, None
    except Exception as e:
        return None, f"Ошибка парсинга: {str(e)}"