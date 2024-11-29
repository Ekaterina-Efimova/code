package exercise02;

public class Dog extends Animal implements Omnivore {
  public Dog(String name, int age) {
    super(name, age);
  }

  @Override
  public String toString() {
    return super.toString();
  }

  public String hunt(){
    return "I can hunt for robbers";
  }
}
