package exercise.exercise.domain.service;

import java.util.UUID;

import exercise.exercise.domain.model.Game;

public interface GameRepositoryService {
  void saveCurrentGame(Game game);

  Game getCurrentGame();

  Game findGameById(UUID gameId);
}
