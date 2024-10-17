package exercise02;

public class GuineaPig extends Animal implements Herbivore  {
  public GuineaPig (String name, int age) {
    super(name, age);
  }

  @Override
  public String toString() {
    return super.toString();
  }

  public String chill(){
    return "I can chill for 12 hours";
  }
}