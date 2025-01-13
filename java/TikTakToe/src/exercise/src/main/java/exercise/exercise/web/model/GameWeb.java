package exercise.exercise.web.model;

import java.util.UUID;
import org.springframework.stereotype.Component;
import org.springframework.web.context.WebApplicationContext;
import org.springframework.context.annotation.Scope;
import org.springframework.context.annotation.ScopedProxyMode;

@Component
@Scope(value = WebApplicationContext.SCOPE_SESSION, proxyMode = ScopedProxyMode.TARGET_CLASS)
public class GameWeb {
    private UUID gameId;
    private TicTacToeBoardWeb board;
    private boolean gameOver;
    private String move;
    private String error;

    public GameWeb() {
        this.gameId = UUID.randomUUID();
        this.board = new TicTacToeBoardWeb();
        this.gameOver = false;
        this.error = null;
    }

    public void setMove(String move) {
        this.move = move;
        if (move != null) {
            String[] coordinates = move.split(",");
            int row = Integer.parseInt(coordinates[0]);
            int col = Integer.parseInt(coordinates[1]);
            this.board.getBoard()[row][col] = 1;
        }
    }

    public String getError() {
        return error;
    }

    public void setError(String error) {
        this.error = error;
    }

    public String getPlayerMove() {
        return move;
    }

    public UUID getGameId() {
        return gameId;
    }

    public TicTacToeBoardWeb getBoard() {
        return board;
    }

    public void setGameId(UUID gameId) {
        this.gameId = gameId;
    }

    public void setGameOver(boolean gameOver){
        this.gameOver = gameOver;
    }

    public boolean isGameOver() {
        return gameOver;
    }

    public void setBoard(TicTacToeBoardWeb board) {
        this.board = board;
    }
}
