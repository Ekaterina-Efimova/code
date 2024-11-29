package exercise04;

import java.util.concurrent.TimeUnit;

public class Dog extends Animal {
  public Dog(String name, int age) {
    super(name, age);
  }

  @Override
  public String toString() {
    return super.toString();
  }

  @Override
  public double goToWalk() {
    double walkTime = calculateWalkTime();

    try {
      TimeUnit.SECONDS.sleep((long) walkTime);
    
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
    }

    return walkTime;
  }

  private double calculateWalkTime() {
    return get_age() * 0.5;
  }
}
