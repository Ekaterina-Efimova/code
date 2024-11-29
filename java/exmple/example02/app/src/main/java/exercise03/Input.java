package exercise03;

import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.Optional;

public class Input implements AutoCloseable {
  private Scanner input;

  public Input() {
    input = new Scanner(System.in);
  }

  private String get_string() {
    return input.nextLine();
  }

  public int get_int() {
    String s = input.nextLine();

    try {
      return Integer.parseInt(s);

    } catch (NumberFormatException e) {
      System.err.println("Couldn't parse a number. Please, try again");
      e = null;
      return get_int();
    }
  }

  private Animal get_animal(String pet_type, String name, int age) {
    Animal animal;

    if (pet_type.equals("dog")) {
      animal = new Dog(name, age);
    } else {
      animal = new Cat(name, age);
    }

    return animal;
  }

  private Optional<Animal> get_pet() {
    Optional<Animal> result = Optional.empty();

    try {
      String pet_type = get_string();
      if (!pet_type.equals("dog") && !pet_type.equals("cat")) {
        throw new Exception("Incorrect input. Unsupported pet type");
      }

      String name = get_string();
      int age = get_int();
      if (age <= 0) {
        throw new Exception("Incorrect input. Age <= 0");
      }

      result = Optional.of(get_animal(pet_type, name, age));
    } catch (Exception e) {
      System.err.println(e.getMessage());
    }

    return result;
  }

  public List<Animal> get_animals(int count) {
    List<Animal> pets = IntStream.range(0, count)
        .mapToObj(i -> get_pet())
        .filter(Optional::isPresent)
        .map(Optional::get)
        .collect(Collectors.toList());

    close();
    return pets;
  }

  public void close() {
    input.close();
  }
}
