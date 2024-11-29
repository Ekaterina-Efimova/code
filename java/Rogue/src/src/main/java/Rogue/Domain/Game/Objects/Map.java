package Rogue.Domain.Game.Objects;

import java.util.Random;

import Rogue.Domain.Character.Control.Hero;

public class Map {
  public static final int MAP_WIDTH = 80;
  public static final int MAP_HEIGHT = 29;

  private char[][] asciiMap;
  private char[][] tempMap;
  private boolean[][] fogOfWar;
  private RoomControl roomControl;
  private int floor;

  public Map(Random rand) {
    asciiMap = new char[MAP_HEIGHT][MAP_WIDTH];
    tempMap = new char[MAP_HEIGHT][MAP_WIDTH];
    fogOfWar = new boolean[MAP_HEIGHT][MAP_WIDTH];
    roomControl = new RoomControl(rand);
    floor = 0;
  }

  public void generateMap(Hero player) {
    clearMap();
    resetFogOfWar();
    roomControl.addFillRoomsOnMap(asciiMap, player);
    copyMap();
    tempMap[player.getPosition().y()][player.getPosition().x()] = '@';
    floor++;
  }

  private void clearMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
      for (int x = 0; x < MAP_WIDTH; x++) {
        asciiMap[y][x] = ' ';
      }
    }
  }

  private void resetFogOfWar() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
      for (int x = 0; x < MAP_WIDTH; x++) {
        fogOfWar[y][x] = true;
      }
    }
  }

  private void copyMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
      System.arraycopy(asciiMap[y], 0, tempMap[y], 0, MAP_WIDTH);
    }
  }

  public char[][] getAsciiMap() {
    return asciiMap;
  }

  public char[][] getTempMap() {
    return tempMap;
  }

  public boolean[][] getFogOfWar() {
    return fogOfWar;
  }

  public Room[] getRooms() {
    return roomControl.getRooms();
  }

  public void setFloor(int floor) {
    this.floor = floor;
  }

  public int getFloor() {
    return floor;
  }
}