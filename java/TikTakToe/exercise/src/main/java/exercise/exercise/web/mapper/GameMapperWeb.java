package exercise.exercise.web.mapper;

import java.util.stream.IntStream;

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
    IntStream.range(0, 3)
        .forEachOrdered(i -> IntStream.range(0, 3)
            .forEachOrdered(j -> gameWeb.setElement(i, j, game.getBoard().getElement(i, j))));
    gameWeb.setMessage(game.getMessage());
    return gameWeb;
  }

  public static Game toDomain(GameWeb gameWeb) {
    Game game = new Game();
    game.setGameId(gameWeb.getGameId());
    IntStream.range(0, 3)
        .forEachOrdered(i -> IntStream.range(0, 3)
            .forEachOrdered(j -> game.getBoard().setElement(i, j, gameWeb.getElement(i, j))));
    game.setMessage(gameWeb.getMessage());
    return game;
  }
}
