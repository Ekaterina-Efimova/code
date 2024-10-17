package exercise02;

public class Hamster extends Animal implements Herbivore {
  public Hamster(String name, int age) {
    super(name, age);
  }

  @Override
  public String toString() {
    return super.toString();
  }

  public String chill() {
    return "I can chill for 8 hours";
  }
}