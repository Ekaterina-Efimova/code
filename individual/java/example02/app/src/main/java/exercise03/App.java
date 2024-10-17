package exercise03;

import java.util.List;
import java.util.Locale;

public class App {
  public static void main(String[] args) {
    Locale.setDefault(Locale.US);

    try (Input input = new Input()) {
      int count = input.get_int();

      if (count <= 0) {
        throw new Exception("Incorrect input. Size <= 0");
      }
      App.output(input, count);

    } catch (Exception e) {
      System.err.println(e.getMessage());
    }
  }

  private static void output(Input input, int count) {
    List<Animal> pets = input.get_animals(count);

    pets.stream()
        .map(Animal::increment_age)
        .map(Animal::toString)
        .forEach(System.out::println);
  }
}