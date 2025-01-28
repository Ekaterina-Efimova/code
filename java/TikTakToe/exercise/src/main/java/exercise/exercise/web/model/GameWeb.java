package exercise.exercise.web.model;

import java.util.UUID;
import lombok.Getter;
import lombok.Setter;
import org.springframework.stereotype.Component;


@Component
@Getter
public class GameWeb {
    @Setter
    private UUID gameId;
    @Setter
    private int[][] board;
    @Setter
    private String move;
    @Setter
    private String message;

    public GameWeb() {
        this.gameId = UUID.randomUUID();
        this.board = new int[3][3];
        this.message = null;
    }

    public int getElement(int row, int col) {
        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length) {
            throw new IndexOutOfBoundsException();
        }
        return board[row][col];
    }

    public void setElement(int row, int col, int value) {
        if (row < 0 || row >= board.length || col < 0 || col >= board[0].length) {
            throw new IndexOutOfBoundsException();
        }
        board[row][col] = value;
    }
}
