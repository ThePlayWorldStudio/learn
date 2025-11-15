# rules.py
from typing import Dict
from turing.transition import Transition

class TransitionRules:
    """Таблица переходов: (state, symbol) → Transition"""
    
    def __init__(self):
        self._rules: Dict[str, Dict[str, Transition]] = {}
        self._current_state: str = ""

    def add(self, state: str, read: str, transition: Transition) -> None:
        if state not in self._rules:
            self._rules[state] = {}
        self._rules[state][read] = transition
        if not self._current_state:
            self._current_state = state

    def get(self, state: str, symbol: str) -> Transition:
        if state not in self._rules:
            raise KeyError(f"Состояние '{state}' не определено")
        if symbol not in self._rules[state]:
            raise KeyError(f"Нет перехода для '{state}' и символа '{symbol}'")
        return self._rules[state][symbol]

    def set_current_state(self, state: str) -> None:
        # РАЗРЕШАЕМ halt без проверки
        self._current_state = state

    @property
    def current_state(self) -> str:
        return self._current_state

    @property
    def states(self):
        return list(self._rules.keys())

    def clear(self):
        self._rules.clear()
        self._current_state = ""