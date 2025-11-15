# tape.py
from __future__ import annotations
from typing import List
from turing.direction import Direction

EMPTY_SYMBOL = '_'
NO_WRITE = '*'

class Tape:
    """Лента машины Тьюринга с динамическим расширением"""
    
    def __init__(self, input_word: str = ""):
        self._cells: List[str] = [EMPTY_SYMBOL]
        self._head: int = 0
        if input_word:
            self.load_word(input_word)

    def read(self) -> str:
        return self._cells[self._head]

    def write(self, symbol: str) -> None:
        if symbol != NO_WRITE:
            self._cells[self._head] = symbol

    def move(self, direction: Direction) -> None:
        if direction == Direction.RIGHT:
            self._head += 1
            if self._head >= len(self._cells):
                self._cells.append(EMPTY_SYMBOL)
        elif direction == Direction.LEFT:
            self._head -= 1
            if self._head < 0:
                self._cells.insert(0, EMPTY_SYMBOL)
                self._head = 0

    def load_word(self, word: str) -> None:
        self._cells = [EMPTY_SYMBOL] + list(word) + [EMPTY_SYMBOL]
        self._head = 1

    def clear(self) -> None:
        self._cells = [EMPTY_SYMBOL]
        self._head = 0

    @property
    def content(self) -> str:
        return ''.join(self._cells).strip(EMPTY_SYMBOL)

    @property
    def head_position(self) -> int:
        return self._head - 1

    def __str__(self) -> str:
        s = ''.join(self._cells)
        marker = ' ' * self._head + 'v'
        return f"{s}\n{marker}"