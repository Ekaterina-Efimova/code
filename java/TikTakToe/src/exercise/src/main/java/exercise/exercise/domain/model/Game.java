package exercise.exercise.domain.model;

import java.util.UUID;

public class Game {
    private UUID gameId;
    private TicTacToeBoard board;
    private String move;
    private boolean gameOver;
    private String error;

    public Game() {
        this.gameId = UUID.randomUUID();
        this.board = new TicTacToeBoard();
        this.gameOver = false;
        this.error = null;
    }

    public Game(UUID gameId, TicTacToeBoard board, boolean gameOver, String move) {
        this.gameId = gameId;
        this.board = board;
        this.gameOver = gameOver;
        this.move = move;
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

    public void setGameId(UUID gameId) {
        this.gameId = gameId;
    }

    public TicTacToeBoard getBoard() {
        return board;
    }

    public void setBoard(TicTacToeBoard board) {
        this.board = board;
    }

    public void setGameOver(boolean gameOver) {
        this.gameOver = gameOver;
    }

    public boolean isGameOver() {
        return gameOver;
    }
}
