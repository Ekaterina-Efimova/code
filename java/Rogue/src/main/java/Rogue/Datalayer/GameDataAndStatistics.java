package Rogue.Datalayer;

import Rogue.Domain.Game.Control.GameData;
import Rogue.Domain.Game.Objects.Character.Hero;

public class GameDataAndStatistics {
  private Hero hero;
  private GameStatistics statistics;

  public void setStatistics(GameStatistics statistics) {
    hero = GameData.getInstance().getHero();
    this.statistics = statistics;
  }

  public GameStatistics getStatistics() {
    return statistics;
  }

  public void setHero(Hero hero) {
    this.hero = hero;
  }

  public Hero getHero() {
    return hero;
  }
}