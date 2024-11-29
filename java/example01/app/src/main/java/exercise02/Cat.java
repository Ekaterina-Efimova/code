package exercise02;

public class Cat extends Animal implements Omnivore  {
  public Cat(String name, int age) {
    super(name, age);
  }

  @Override
  public String toString() {
    return super.toString();
  }

  public String hunt(){
    return "I can hunt for mice";
  }
}
