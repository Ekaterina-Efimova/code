package exercise.exercise.datasource.service;

import java.util.UUID;

import exercise.exercise.datasource.mapper.GameMapper;
import exercise.exercise.datasource.repository.GameStorage;
import exercise.exercise.domain.model.Game;

public class GameRepositoryServiceImpl implements GameRepositoryService {
  GameStorage gameStorage;

  public GameRepositoryServiceImpl(GameStorage gameStorage) {
    this.gameStorage = gameStorage;
  }

  public Game saveCurrentGame(Game game) {
    gameStorage.addGame(GameMapper.toDatasource(game));
    return game;
  }

  public Game findGameById(UUID gameId) {
    return GameMapper.toDomain(gameStorage.getGame(gameId));
  }
}