package exercise.exercise.datasource.mapper;

import java.util.stream.IntStream;


import exercise.exercise.domain.model.Game;
import exercise.exercise.datasource.model.GameEntity;


public class GameMapper {
  private GameMapper() {
  }

  public static GameEntity toDatasource(Game game) {
    GameEntity gameEntity = new GameEntity();
    gameEntity.setGameId(game.getGameId());
    IntStream.range(0, 3)
        .forEachOrdered(i -> IntStream.range(0, 3)
            .forEachOrdered(j -> gameEntity.setElement(i, j, game.getBoard().getElement(i, j))));
    gameEntity.setMessage(game.getMessage());
    return gameEntity;
  }

  public static Game toDomain(GameEntity gameEntity) {
    Game game = new Game();
    game.setGameId(gameEntity.getGameId());
    IntStream.range(0, 3)
        .forEachOrdered(i -> IntStream.range(0, 3)
            .forEachOrdered(j -> game.getBoard().setElement(i, j, gameEntity.getElement(i, j))));
    game.setMessage(gameEntity.getMessage());
    return game;
  }
}
