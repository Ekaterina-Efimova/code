package exercise02;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Input implements AutoCloseable {
  private Scanner input;

  public Input() {
    input = new Scanner(System.in);
  }

  private String get_string() {
    return input.nextLine();
  }

  public int get_int() {
    do {
      String s = input.nextLine();

      try {
        return Integer.parseInt(s);

      } catch (NumberFormatException e) {
        System.err.println("Couldn't parse a number. Please, try again");
        e = null;
      }

    } while (true);
  }

  private Animal get_animal(String pet_type, String name, int age) {
    Animal animal;

    if (pet_type.equals("dog")) {
      animal = new Dog(name, age);
    } else if (pet_type.equals("hamster")) {
      animal = new Hamster(name, age);
    } else if (pet_type.equals("guinea")) {
      animal = new GuineaPig(name, age);
    } else {
      animal = new Cat(name, age);
    }

    return animal;
  }

  public void close() {
    input.close();
  }

  public List<Animal> get_animals(int count) {
    List<Animal> pets = new ArrayList<>();

    for (int i = 0; i < count; i++) {
      try {
        String pet_type = get_string();

        if (!pet_type.equals("dog") && !pet_type.equals("cat") && !pet_type.equals("hamster")
            && !pet_type.equals("guinea")) {
          throw new Exception("Incorrect input. Unsupported pet type");
        }

        String name = get_string();
        int age = get_int();
        if (age <= 0) {
          throw new Exception("Incorrect input. Age <= 0");
        }

        pets.add(get_animal(pet_type, name, age));

      } catch (Exception e) {
        System.err.println(e.getMessage());
        e = null;
      }
    }

    close();
    return pets;
  }
}
