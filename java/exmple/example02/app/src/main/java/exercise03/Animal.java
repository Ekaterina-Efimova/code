package exercise03;

public abstract class Animal {
  private String name;
  private int age;

  protected Animal(String name, int age) {
    this.name = name;
    this.age = age;
  }

  public String get_name() {
    return name;
  }

  public int get_age() {
    return age;
  }

  public Animal increment_age() {
    Animal pet = this;
    if (age > 10) {
      pet = (pet instanceof Dog) ? new Dog(name, ++age) : new Cat(name, ++age);
    }
    return pet;
  }

  @Override
  public String toString() {
    return String.format("%s name = %s, age = %d", getClass().getSimpleName(), name, age);
  }
}
