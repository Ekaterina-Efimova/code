package exercise.exercise.datasource.repository;

import java.util.UUID;

import org.springframework.stereotype.Repository;

import exercise.exercise.datasource.mapper.GameMapper;
import exercise.exercise.domain.model.Game;

@Repository
public class GameRepository {
    
  private GameStorage gameStorage;
  private UUID currentGameId;
  
  public GameRepository() {
      this.gameStorage = GameStorage.getInstance();
  }
  
  public void saveGame(Game game) {
      gameStorage.addGame(GameMapper.toDatasource(game));
      currentGameId = game.getGameId();
  }
  
  public Game getCurrentGame() {
      return GameMapper.toDomain(gameStorage.getGame(currentGameId));
  }

  public Game findGameById(UUID gameId) {
      return GameMapper.toDomain(gameStorage.getGame(gameId));
  }
}