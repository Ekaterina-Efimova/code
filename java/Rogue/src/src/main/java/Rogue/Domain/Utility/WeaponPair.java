package Rogue.Domain.Utility;

import Rogue.Domain.Thing.ThingEnums.WeaponSubType;

public class WeaponPair {
  private WeaponSubType key;
  private Integer value;

  public WeaponPair(WeaponSubType key, Integer value) {
    this.key = key;
    this.value = value;
  }

  public WeaponSubType getKey() {
    return key;
  }

  public Integer getValue() {
    return value;
  }
}