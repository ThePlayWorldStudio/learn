import java.util.*;

public class Turing {
    private final Tape tape;
    private String currentState;
    private final String acceptState;
    private final char blank;
    private final Map<String, Map<Character, Transition>> transitions = new HashMap<>();

    private static class Transition {
        char write;
        char move; // 'L' or 'R'
        String nextState;

        Transition(char write, char move, String nextState) {
            this.write = write;
            this.move = move;
            this.nextState = nextState;
        }
    }

    public TuringMachine(char blank, String initialState, String acceptState) {
        this.tape = new Tape(blank);
        this.blank = blank;
        this.currentState = initialState;
        this.acceptState = acceptState;
    }

    public void loadTape(String input) {
        tape.loadFromString(input);
    }

    public void addRule(String state, char read, char write, char move, String nextState, String nextState) {
        transitions.computeIfAbsent(state, k -> new HashMap<>())
                   .put(read, new Transition(write, move, nextState));
    }

    public boolean step() {
        if (currentState.equals(acceptState)) {
            return false; // уже в принимающем состоянии
        }

        char symbol = tape.read();
        Transition tr = transitions.getOrDefault(currentState, Map.of())
                                   .getOrDefault(symbol, null);
        if (tr == null) {
            return false; // нет правила — останов
        }

        tape.write(tr.write);
        if (tr.move == 'L') tape.moveLeft();
        else if (tr.move == 'R') tape.moveRight();
        currentState = tr.nextState;
        return true;
    }

    public boolean run(boolean log) {
        if (log) {
            System.out.println("Start: " + this);
        }

        int stepCount = 0;
        while (step()) {
            stepCount++;
            if (log) {
                System.out.println("Step " + stepCount + ": " + this);
            }
        }

        if (log) {
            System.out.println("Halted: " + this);
        }
        return currentState.equals(acceptState);
    }

    @Override
    public String toString() {
        return "State: " + currentState + ", Tape: " + tape.toString();
    }

    public Tape getTape() {
        return tape;
    }

    public String getCurrentState() {
        return currentState;
    }
}
