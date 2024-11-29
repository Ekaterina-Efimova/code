package exercise04;

import java.util.Locale;

public class App {
  public static void main(String[] args) {
    Locale.setDefault(Locale.US);
    double startTime = System.currentTimeMillis();

    try (Input input = new Input()) {
      int count = input.get_int();

      if (count <= 0) {
        throw new Exception("Incorrect input. Size <= 0");
      }
      Output out = new Output(input);
      out.output(count, startTime);

    } catch (Exception e) {
      System.err.println(e.getMessage());
    }
  }
}