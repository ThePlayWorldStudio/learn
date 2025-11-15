# machine.py
from typing import Tuple
from turing.tape import Tape, EMPTY_SYMBOL, NO_WRITE
from turing.rules import TransitionRules
from turing.transition import Transition
from turing.direction import Direction

MAX_STEPS = 10000

class TuringMachine:
    """Машина Тьюринга: связывает ленту и правила"""
    
    def __init__(self, alphabet: str = ""):
        self.tape = Tape()
        self.rules = TransitionRules()
        self._alphabet = ""
        self._step_count = 0
        self._halted = False

        if alphabet:
            self.set_alphabet(alphabet)

    def set_alphabet(self, alphabet: str) -> None:
        if NO_WRITE in alphabet or EMPTY_SYMBOL in alphabet:
            raise ValueError(f"Алфавит не может содержать '{NO_WRITE}' или '{EMPTY_SYMBOL}'")
        if not alphabet:
            raise ValueError("Алфавит пуст")
        self._alphabet = ''.join(dict.fromkeys(alphabet))

    def load_word(self, word: str) -> None:
        for c in word:
            if c not in self._alphabet:
                raise ValueError(f"Символ '{c}' не в алфавите")
        self.tape.load_word(word)

    def add_rule(self, state: str, read: str, write: str, move: Direction, next_state: str, stop: bool = False) -> None:
        self.rules.add(state, read, Transition(write, move, next_state, stop))

    def set_start_state(self, state: str) -> None:
        self.rules.set_current_state(state)

    def reset(self) -> None:
        self._step_count = 0
        self._halted = False

    def step(self) -> Tuple[str, bool]:
        if self._halted or self._step_count >= MAX_STEPS:
            raise RuntimeError("Лимит шагов")

        symbol = self.tape.read()
        state = self.rules.current_state

        # Если текущее состояние — halt, сразу стоп
        if state == "halt":
            self._halted = True
            result = self.tape.content
            tape_str = str(self.tape)
            return (f"[halt] СТОП\n{tape_str}\n"
                    f"Результат: {result} | Шаги: {self._step_count}"), False

        trans = self.rules.get(state, symbol)
        self._step_count += 1

        tape_before = str(self.tape)
        self.tape.write(trans.write)
        self.tape.move(trans.move)
        self.rules.set_current_state(trans.next_state)
        tape_after = str(self.tape)

        dir_map = {Direction.LEFT: "влево", Direction.RIGHT: "вправо", Direction.NONE: "на месте"}
        msg = f"[{state}] <{symbol}> → <{trans.write}> (→ {dir_map[trans.move]}) → {trans.next_state}"

        if trans.stop:
            self._halted = True
            result = self.tape.content
            return (f"{msg}\n{tape_before}\n→ СТОП\n{tape_after}\n"
                    f"Результат: {result} | Шаги: {self._step_count}"), False

        return f"{msg}\n{tape_before}\n→\n{tape_after}", True

    def run(self) -> str:
        """Запуск до остановки. Возвращает финальное содержимое ленты."""
        self.reset()
        while True:
            msg, continue_run = self.step()
            if not continue_run:
                return self.tape.content
            if self._step_count >= MAX_STEPS:
                raise RuntimeError(f"Превышен лимит шагов: {MAX_STEPS}")

    @property
    def tape_content(self) -> str:
        return self.tape.content

    @property
    def current_state(self) -> str:
        return self.rules.current_state

    @property
    def steps(self) -> int:
        return self._step_count

    def __str__(self) -> str:
        return f"{self.tape}\nСостояние: {self.current_state} | Шаг: {self._step_count}"