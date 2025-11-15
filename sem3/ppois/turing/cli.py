# turing_interpreter.py
import sys
from pathlib import Path
from turing.turing import TuringMachine   # у тебя файл так и называется, оставляем как есть
from turing.direction import Direction

def parse_file(filepath: str) -> dict:
    path = Path(filepath)
    if not path.exists():
        raise FileNotFoundError(f"Файл не найден: {filepath}")

    data = {
        'alphabet': '',
        'word': '',
        'start_state': 'q0',
        'rules': []
    }

    with open(path, 'r', encoding='utf-8') as f:
        lines = [line.strip() for line in f if line.strip() and not line.startswith('#')]

    data['alphabet'] = lines[0]
    data['word'] = lines[1]

    for line in lines[2:]:
        parts = line.split()
        if len(parts) < 5:
            raise ValueError(f"Неверный формат правила: {line}")
        
        state, read, write, move_str, next_state = parts[:5]
        stop = len(parts) > 5 and parts[5] == '1'

        try:
            move = Direction(move_str)
        except ValueError:
            raise ValueError(f"Неверное направление: {move_str}")

        data['rules'].append((state, read, write, move, next_state, stop))

    return data

def main():
    if len(sys.argv) < 2:
        print("Использование: python turing_interpreter.py <путь_к_файлу> [-log]")
        sys.exit(1)

    filepath = sys.argv[1]
    log_mode = '-log' in sys.argv

    try:
        config = parse_file(filepath)
    except Exception as e:
        print(f"Ошибка парсинга файла: {e}")
        sys.exit(1)

    tm = TuringMachine(alphabet=config['alphabet'])
    tm.load_word(config['word'])

    # ПРАВИЛЬНЫЙ ПОРЯДОК
    tm.set_start_state(config['start_state'])
    for state, read, write, move, next_state, stop in config['rules']:
        tm.add_rule(state, read, write, move, next_state, stop)

    print(f"Машина загружена из: {filepath}")
    print(f"Алфавит: {config['alphabet']}")
    print(f"Слово: {config['word']}")
    print(f"Начальное состояние: {config['start_state']}")
    print(f"Правил: {len(config['rules'])}")
    print("-" * 50)

    # ЕДИНЫЙ ЗАПУСК
    tm.reset()
    step = 0
    log_messages = []

    while True:
        try:
            msg, continue_run = tm.step()
            step += 1
            log_messages.append(f"Шаг {step}:\n{msg}\n{'-'*50}")
            if not continue_run:   # машина остановилась
                break
        except Exception as e:
            print(f"Ошибка: {e}")
            sys.exit(1)

    final_result = tm.tape.content

    if log_mode:
        print("=== ПОШАГОВЫЙ ЛОГ ===")
        for log_msg in log_messages:
            print(log_msg)
        print(f"Финальное состояние: {final_result}")
        print(f"Шагов: {tm.steps}")
    else:
        print(f"Результат: {final_result}")
        print(f"Шагов: {tm.steps}")

if __name__ == "__main__":
    main()
