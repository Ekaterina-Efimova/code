package exercise04;
public abstract class Animal {
  private String name;
  private int age;

  protected Animal(String name, int age){
    this.name = name;
    this.age = age;
  }

  public String get_name(){
    return name;
  }
  
  public int get_age(){
    return age;
  }

  @Override
  public String toString() {
    return String.format("%s name = %s, age = %d", getClass().getSimpleName(), name, age);
  }

  public abstract double goToWalk();
}
