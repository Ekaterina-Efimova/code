package exercise.exercise.datasource.service;

import java.util.UUID;

import exercise.exercise.domain.model.Game;

public interface GameRepositoryService {
  Game saveCurrentGame(Game game);

  Game findGameById(UUID gameId);
}
