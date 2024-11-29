package Rogue.Domain.Thing.ThingEnums;

public enum OtherSubType implements ThingSubType {
  None;

  @Override
  public int getOrder() {
    return ordinal() + 1;
  }
}