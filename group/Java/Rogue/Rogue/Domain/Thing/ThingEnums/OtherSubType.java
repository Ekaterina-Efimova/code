package Domain.Thing.ThingEnums;

public enum OtherSubType implements ThingSubType {
  None;

  @Override
  public int getOrder() {
    return ordinal() + 1;
  }

  public static OtherSubType getByOrder(int item) {
    for (OtherSubType subType : values()) {
      if (subType.getOrder() == item) {
        return subType;
      }
    }
    return null;
  }
}