package exercise02;

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

    printHerbivores(pets);
    printOmnivores(pets);
  }

  private static void printHerbivores(List<Animal> pets) {
    for (Animal pet : pets)
      if (pet instanceof Herbivore)
        System.out.println(pet.toString());
  }

  private static void printOmnivores(List<Animal> pets) {
    for (Animal pet : pets)
      if (pet instanceof Omnivore)
        System.out.println(pet.toString());
  }
}