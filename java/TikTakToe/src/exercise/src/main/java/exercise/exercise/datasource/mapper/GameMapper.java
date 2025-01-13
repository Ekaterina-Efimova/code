package exercise.exercise.datasource.mapper;

import org.springframework.stereotype.Component;

import exercise.exercise.domain.model.Game;
import exercise.exercise.datasource.model.GameEntity;

@Component
public class GameMapper {
  private GameMapper() {
  }

  public static GameEntity toDatasource(Game game) {
    GameEntity gameEntity = new GameEntity();
    gameEntity.setGameId(game.getGameId());
    gameEntity.getBoard().setBoard(game.getBoard().getBoard());
    gameEntity.setGameOver(game.isGameOver());
    gameEntity.setMove(game.getPlayerMove());
    gameEntity.setError(game.getError());
    return gameEntity;
  }

  public static Game toDomain(GameEntity gameEntity) {
    Game game = new Game();
    game.setGameId(gameEntity.getGameId());
    game.getBoard().setBoard(gameEntity.getBoard().getBoard());
    game.setGameOver(gameEntity.isGameOver());
    game.setMove(gameEntity.getPlayerMove());
    game.setError(gameEntity.getError());
    return game;
  }
}
