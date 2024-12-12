package Rogue.Domain.Game.Objects.Thing.ThingEnums;

public enum ScrollSubType implements ThingSubType {
  Карта, // Показывает карту, предметы скрыты
  СвитокСна, // Заставляет монстров рядом спать 4 - 8 ходов
  СвитокОпознования, // Показывает тип всех предметов на этаже
  СвитокТелепортации, // Телепортирует игрока в случайное место
  СвитокСозданияМонстра, // Создает монстра
  ИспорченныйСвиток, // Ничего не делает
  СвитокСвета; // Освещает комнату

  @Override
  public int getOrder() {
    return ordinal() + 1;
  }

  public static ScrollSubType parseScrollSubType(char c) {
    int order = c - '0';
    return getByOrder(order);
  }

  private static ScrollSubType getByOrder(int item) {
    for (ScrollSubType subType : values()) {
      if (subType.getOrder() == item) {
        return subType;
      }
    }
    return null;
  }
}