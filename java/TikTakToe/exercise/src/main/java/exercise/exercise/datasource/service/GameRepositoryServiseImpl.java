package exercise.exercise.datasource.service;

import java.util.UUID;

import exercise.exercise.datasource.mapper.GameMapper;
import exercise.exercise.datasource.repository.GameStorage;
import exercise.exercise.domain.model.Game;

public class GameRepositoryServiseImpl implements GameRepositoryService {
  GameStorage gameStorage;

  public GameRepositoryServiseImpl(GameStorage gameStorage) {
    this.gameStorage = gameStorage;
  }

  public void saveCurrentGame(Game game) {
    gameStorage.addGame(GameMapper.toDatasource(game));
  }

  public Game findGameById(UUID gameId) {
    return GameMapper.toDomain(gameStorage.getGame(gameId));
  }
}