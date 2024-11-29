package exercise05;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

class AppTest {
   @Test
  public void testApp() {
    String input = "3\ndog\nSnowball\n12\ndog\nSnowball2\n8\ndog\nSnowball3\n10";

    InputStream fakeInput = new ByteArrayInputStream(input.getBytes());
    System.setIn(fakeInput);

    ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
    System.setOut(new PrintStream(outputStream));

    App.main(null);

    String expectedOutput = "Dog name = Snowball, age = 12\n" +
        "Dog name = Snowball2, age = 8\n" +
        "Dog name = Snowball3, age = 10\n";

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
    ByteArrayOutputStream errorStream = new ByteArrayOutputStream(); 
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
