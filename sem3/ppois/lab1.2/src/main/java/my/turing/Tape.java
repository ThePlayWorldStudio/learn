import java.util.HashMap;
import java.util.Map;

public class Tape {
    private final Map<Integer, Character> cells = new HashMap<>();
    private int head = 0;
    private final char blank;

    public Tape(char blank) {
        this.blank = blank;
    }

    public char read() {
        return cells.getOrDefault(head, blank);
    }

    public void write(char symbol) {
        if (symbol == blank) {
            cells.remove(head);
        } else {
            cells.put(head, symbol);
        }
    }

    public void moveLeft() {
        head--;
    }

    public void moveRight() {
        head++;
    }

    public void loadFromString(String input) {
        cells.clear();
        head = 0;
        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
            if (c != blank) {
                cells.put(i, c);
            }
        }
    }

    @Override
    public String toString() {
        if (cells.isEmpty()) return "_" + blank + "_";

        int min = cells.keySet().stream().min(Integer::compare).orElse(0);
        int max = cells.keySet().stream().max(Integer::compare).orElse(0);

        StringBuilder sb = new StringBuilder();
        for (int i = min - 1; i <= max + 1; i++) {
            if (i == head) sb.append('[');
            char c = cells.getOrDefault(i, blank);
            sb.append(c == blank ? '_' : c);
            if (i == head) sb.append(']');
        }
        return sb.toString();
    }
}
