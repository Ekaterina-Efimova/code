package Domain.Game.Objects;

import java.util.Random;

import Domain.Utility.Position;

public class Room {
  public static final int SECTOR_WIDTH = Map.MAP_WIDTH / 3; // перенести в room?
  public static final int SECTOR_HEIGHT = Map.MAP_HEIGHT / 3;

  private int x1;
  private int x2;
  private int y1;
  private int y2;
  private boolean startRoom;
  private boolean exitRoom;

  public Room(int xRoom, int yRoom) {
    Random rand = new Random();
    int x = rand.nextInt(SECTOR_WIDTH - 4) + 4;
    int y = rand.nextInt(SECTOR_HEIGHT - 4) + 4;
    x1 = xRoom * (SECTOR_WIDTH + 1) + (SECTOR_WIDTH - x) / 2;
    y1 = yRoom * (SECTOR_HEIGHT + 1) + (SECTOR_HEIGHT - y) / 2;
    x2 = x1 + x;
    y2 = y1 + y;

    startRoom = false;
    exitRoom = false;
  }

  public int x1() {
    return x1;
  }

  public int x2() {
    return x2;
  }

  public int y1() {
    return y1;
  }

  public int y2() {
    return y2;
  }

  public boolean isStartRoom() {
    return startRoom;
  }

  public boolean isExitRoom() {
    return exitRoom;
  }

  public void setStartRoom() {
    this.startRoom = true;
  }

  public void setExitRoom() {
    this.exitRoom = true;
  }

  private Room checkRoom(int x, int y) {
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2) ? this : null;
  }

  public static Room findRoom(Room[] rooms, Position pos) {
    Room room = null;
    for (Room roomToFind : rooms) {
      if (roomToFind.checkRoom(pos.x(), pos.y()) != null) {
        room = roomToFind;
        break;
      }
    }

    return room;
  }
}
