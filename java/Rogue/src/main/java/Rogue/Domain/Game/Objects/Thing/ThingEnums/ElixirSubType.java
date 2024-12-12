package Rogue.Domain.Game.Objects.Thing.ThingEnums;

public enum ElixirSubType implements ThingSubType {
  Яд, // 1 Наносит урон соседним монстрам
  ЗельеСилы, // 2 Увеличивает силу 1-3
  ЗальеНаживы, // 3 Показывает скрытые предметы
  ЗельеЛечения, // 4 Лечит рандом на уровень игрока
  ЗельеПредчувствия, // 5 Показывает монстров
  БольшоеЗельеЛечения, // 6 Лечит 8рандом на уровень игрока
  Вода; // 7 Ничего не делает

  @Override
  public int getOrder() {
    return ordinal() + 1;
  }

  public static ElixirSubType parseElixirSubType(char c) {
    int order = c - '0';
    return getByOrder(order);
  }

  private static ElixirSubType getByOrder(int item) {
    for (ElixirSubType subType : values()) {
      if (subType.getOrder() == item) {
        return subType;
      }
    }
    return null;
  }
}