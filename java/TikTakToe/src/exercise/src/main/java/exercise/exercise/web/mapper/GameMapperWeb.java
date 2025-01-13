package exercise.exercise.web.mapper;

import org.springframework.stereotype.Component;

import exercise.exercise.domain.model.Game;
import exercise.exercise.web.model.GameWeb;

@Component
public class GameMapperWeb {
  private GameMapperWeb() {
  }

  public static GameWeb toWeb(Game game) {
    GameWeb gameWeb = new GameWeb();
    gameWeb.setGameId(game.getGameId());
    gameWeb.getBoard().setBoard(game.getBoard().getBoard());
    gameWeb.setGameOver(game.isGameOver());
    gameWeb.setMove(game.getPlayerMove());
    gameWeb.setError(game.getError());
    return gameWeb;
  }

  public static Game toDomain(GameWeb gameWeb) {
    Game game = new Game();
    game.setGameId(gameWeb.getGameId());
    game.getBoard().setBoard(gameWeb.getBoard().getBoard());
    game.setGameOver(gameWeb.isGameOver());
    game.setMove(gameWeb.getPlayerMove());
    game.setError(gameWeb.getError());
    return game;
  }
}
