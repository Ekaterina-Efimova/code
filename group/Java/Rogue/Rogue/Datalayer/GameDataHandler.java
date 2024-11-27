package Datalayer;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import Domain.Thing.ThingEnums.ThingSubType;

import java.io.FileWriter;
import java.util.Random;
import java.io.FileReader;

public class GameDataHandler {
  private static final String FILE_PATH = "game_data.json";
  private Gson gson;

  public GameDataHandler() {
    gson = new GsonBuilder()
        .registerTypeAdapter(Random.class, new RandomAdapter())
        .registerTypeAdapter(ThingSubType.class, new ThingSubTypeDeserializer())
        .create();
  }

  public void saveGameDataAndStatistics(GameDataAndStatistics dataAndStatistics) {
    try (FileWriter writer = new FileWriter(FILE_PATH)) {
      gson.toJson(dataAndStatistics, writer);
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  public GameDataAndStatistics loadGameDataAndStatistics() {
    try (FileReader reader = new FileReader(FILE_PATH)) {
      return gson.fromJson(reader, GameDataAndStatistics.class);
    } catch (Exception e) {
      e.printStackTrace();
      return null;
    }
  }

  public void updateStatistics(GameDataAndStatistics dataAndStatistics, boolean heroAlive) {
    GameData data = dataAndStatistics.getGameData();
    GameStatistics statistics = dataAndStatistics.getStatistics();
    String name = data.getHero().getName();
    if (name != null)
      statistics.updatePlayerName(name);

    if (!heroAlive) {
      statistics.updateWin(data.isWin());
    }

    statistics.updateExpirence(data.getHero().getExp());
    statistics.updateScore(data.getHero().getGold());
  }
}
