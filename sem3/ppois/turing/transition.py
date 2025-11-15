from dataclasses import dataclass
from turing.direction import Direction

@dataclass(frozen=True)
class Transition:
    write: str
    move: Direction
    next_state: str
    stop: bool = False