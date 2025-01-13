package exercise.exercise.domain.service;

import java.util.UUID;

import exercise.exercise.datasource.repository.GameRepository;
import exercise.exercise.domain.model.Game;

public class GameRepositoryServiseImpl implements GameRepositoryService {
  private GameRepository gameRepository;

  public GameRepositoryServiseImpl(GameRepository gameRepository) {
    this.gameRepository = gameRepository;
  }

  public void saveCurrentGame(Game game) {
    gameRepository.saveGame(game);
  }

  public Game getCurrentGame() {
    return gameRepository.getCurrentGame();
  }

  public Game findGameById(UUID gameId) {
    return gameRepository.findGameById(gameId);
  }
}