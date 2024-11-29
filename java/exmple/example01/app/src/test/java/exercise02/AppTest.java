package exercise02;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class AppTest {

  @Test
  public void testApp() {
    String input = "6\ndog\nSnowball\n12\nguinea\nPiggy\n5\ncat\nSnowball\n9\nhamster\nWave\n" +
        "2\ndog\nSnowball\n12";

    InputStream fakeInput = new ByteArrayInputStream(input.getBytes());
    System.setIn(fakeInput);

    ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
    System.setOut(new PrintStream(outputStream));

    App.main(null);

    String expectedOutput = "GuineaPig name = Piggy, age = 5. I can chill for 12 hours\n" +
        "Hamster name = Wave, age = 2. I can chill for 8 hours\n" +
        "Dog name = Snowball, age = 12. I can hunt for robbers\n" +
        "Cat name = Snowball, age = 9. I can hunt for mice\n" +
        "Dog name = Snowball, age = 12. I can hunt for robbers\n";

    assertEquals(expectedOutput, outputStream.toString());

    System.setIn(System.in);
    System.setOut(System.out);
  }

  @Test
  public void testAnimalAgeValidation() {
    String input = "1\ncat\nKitty\n-10\n";
    InputStream fakeInput = new ByteArrayInputStream(input.getBytes());
    System.setIn(fakeInput);

    ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
    ByteArrayOutputStream errorStream = new ByteArrayOutputStream(); // Добавляем объявление errorStream
    System.setOut(new PrintStream(outputStream));
    System.setErr(new PrintStream(errorStream));

    App.main(null);

    String expectedErrorOutput = "Incorrect input. Age <= 0\n";
    assertEquals(expectedErrorOutput, errorStream.toString());

    System.setIn(System.in);
    System.setOut(System.out); 
  }

  @Test
  public void testUnsupportedPetType() {
    String input = "1\nturtle\nTurtly\n5\n";
    InputStream fakeInput = new ByteArrayInputStream(input.getBytes());
    System.setIn(fakeInput);

    ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
    ByteArrayOutputStream errorStream = new ByteArrayOutputStream();
    System.setOut(new PrintStream(outputStream));
    System.setErr(new PrintStream(errorStream));

    App.main(null);

    String expectedErrorOutput = "Incorrect input. Unsupported pet type\n";
    assertEquals(expectedErrorOutput, errorStream.toString());

    System.setIn(System.in);
    System.setOut(System.out);
    System.setErr(System.err);
  }
}
