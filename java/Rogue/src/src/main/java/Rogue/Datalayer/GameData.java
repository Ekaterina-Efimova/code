package Rogue.Datalayer;

import Rogue.Domain.Character.Control.Hero;

public class GameData {
  private int floor;
  private Hero hero;

  public void setGameData(int floor, Hero hero) {
    this.floor = floor;
    this.hero = hero;
  }

  public int getFloor() {
    return floor;
  }

  public Hero getHero() {
    return hero;
  }

  public boolean isWin() {
    return floor == 21;
  }
}