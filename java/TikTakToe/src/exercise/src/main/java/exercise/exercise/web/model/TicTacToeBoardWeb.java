package exercise.exercise.web.model;

public class TicTacToeBoardWeb {
	private int[][] board;

	public TicTacToeBoardWeb() {
		this.board = new int[3][3];
	}

	public void setBoard(int[][] board) {
		for (int i = 0; i < 3; i++) {
			System.arraycopy(board[i], 0, this.board[i], 0, 3);
		}
	}

	public int[][] getBoard() {
		return board;
	}
}