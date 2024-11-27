package Domain.Thing.Things;

import Domain.Thing.ThingEnums.*;
import Domain.Utility.Position;

public class Thing {
  private ThingType thingType;
  private ThingSubType thingSubType;
  private Position position;
  private char thingName;

  public Thing(ThingType thingType, ThingSubType thingSubType) {
    this.thingType = thingType;
    this.thingSubType = thingSubType;
    this.position = new Position(0, 0);
    getName(false);
  }

  public void getName(boolean identifly) {
    if (identifly) {
      if (thingType == ThingType.Оружие) {
        thingName = 'w';
      } else if (thingType == ThingType.Зелье) {
        thingName = 'e';
      } else if (thingType == ThingType.Свиток) {
        thingName = 's';
      } else if (thingType == ThingType.Еда) {
        thingName = 'f';
      }
    } else {
      thingName = 't';
    }
  }

  public ThingSubType getThingSubType() {
    return thingSubType;
  }

  public ThingType getThingType() {
    return thingType;
  }

  public Position getPosition() {
    return position;
  }

  public char getThingName() {
    return thingName;
  }

  public void setThingType(ThingType thingType) {
    this.thingType = thingType;
  }

  public void setThingSubType(ThingSubType thingSubType) {
    this.thingSubType = thingSubType;
  }

  public void setPosition(Position position) {
    this.position = position;
  }

  public void setPosition(int x, int y) {
    this.position.setPosition(x, y);
  }
}
