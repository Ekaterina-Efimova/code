package exercise.exercise.datasource.repository;

import java.util.UUID;
import java.util.concurrent.ConcurrentHashMap;

import exercise.exercise.datasource.model.*;

public class GameStorage {
  private static GameStorage instance;
  private ConcurrentHashMap<UUID, GameEntity> games;

  private GameStorage() {
    this.games = new ConcurrentHashMap<>();
  }

  public static GameStorage getInstance() {
    if (instance == null) {
      instance = new GameStorage();
    }
    return instance;
  }

  public void addGame(GameEntity game) {
    games.put(game.getGameId(), game);
  }

  public GameEntity getGame(UUID gameId) {
    if (!games.containsKey(gameId)) {
      return null;
    }
    return games.get(gameId);
  }
}