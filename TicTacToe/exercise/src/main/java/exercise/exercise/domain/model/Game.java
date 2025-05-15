package exercise.exercise.domain.model;

import java.util.UUID;
import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class Game {
    private UUID gameId;
    private TicTacToeBoard board;
    private String move;
    private String message;

    public Game() {
        this.gameId = UUID.randomUUID();
        this.board = new TicTacToeBoard();
        this.message = null;
    }

    public Game(UUID gameId, TicTacToeBoard board,  String move) {
        this.gameId = gameId;
        this.board = board;
        this.move = move;
    }

    public void setMove(String move) {
        this.move = move;
        if (move != null) {
            String[] coordinates = move.split(",");
            this.board.setElement(Integer.parseInt(coordinates[0]), Integer.parseInt(coordinates[1]), 1);
        }
    }
}
