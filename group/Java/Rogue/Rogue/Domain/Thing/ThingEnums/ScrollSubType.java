package Domain.Thing.ThingEnums;

public enum ScrollSubType implements ThingSubType {
  Катра, // Показывает карту, предметы скрыты
  СвитокСна, // Заставляет монстра спать 4 - 8 ходов
  СвитокОпознования, // Показывает тип предмета
  СвитокТелепортации, // Телепортирует игрока в случайное место
  СвитокСозданияМонстра, // Создает монстра
  ИспорченныйСвиток, // Ничего не делает
  СвитокСвета; // Освещает комнату

  @Override
  public int getOrder() {
    return ordinal() + 1;
  }

  public static ScrollSubType parseScrollSubType(char c) {
    int item = c - '0';

    return getByOrder(item);
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