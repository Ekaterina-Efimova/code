package Rogue.Datalayer;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import Rogue.Domain.Game.Objects.Thing.ThingEnums.ThingSubType;

import java.io.FileWriter;
import java.util.Random;
import java.io.FileReader;
import java.util.logging.Level;
import java.util.logging.Logger;

public final class GameDataHandler {
  private static GameDataHandler instance;
  private static final String FILE_PATH = "game_data.json";
  private final Gson gson;

  private GameDataHandler() {
    gson = new GsonBuilder()
        .registerTypeAdapter(Random.class, new RandomAdapter())
        .registerTypeAdapter(ThingSubType.class, new ThingSubTypeDeserializer())
        .create();
  }

  public static GameDataHandler getGameDataHandler() {
    if (instance == null) {
      instance = new GameDataHandler();
    }
    return instance;
  }

  public void saveGameDataAndStatistics(GameDataAndStatistics dataAndStatistics) {
    try (FileWriter writer = new FileWriter(FILE_PATH)) {
      gson.toJson(dataAndStatistics, writer);
    } catch (Exception e) {
      Logger.getLogger(GameDataHandler.class.getName()).log(Level.SEVERE, "An error occurred", e);
    }
  }

  public GameDataAndStatistics loadGameDataAndStatistics() {
    try (FileReader reader = new FileReader(FILE_PATH)) {
      return gson.fromJson(reader, GameDataAndStatistics.class);
    } catch (Exception e) {
      Logger.getLogger(GameDataHandler.class.getName()).log(Level.SEVERE, "An error occurred", e);
      return null;
    }
  }
}