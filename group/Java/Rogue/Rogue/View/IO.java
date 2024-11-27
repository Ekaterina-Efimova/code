package View;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class IO {
  private static final String ANSI_RESET = "\u001B[0m";
  private static final String ANSI_GREEN = "\u001B[32m";
  private static final String ANSI_RED = "\u001B[31m";
  private static final String ANSI_YELLOW = "\u001B[33m";
  private static final String ANSI_BLUE = "\u001B[34m";

  private IO() {
  }

  public static char getCh() {
    char input = 'q';
    try {
      cmdRawMode();
      input = (char) System.in.read();
      resetCmd();

    } catch (Exception e) {
      Thread.currentThread().interrupt();
      e.printStackTrace();
    }

    return input;
  }

  public static void print(char[][] printChar) {
    StringBuilder sb = new StringBuilder();
    boolean lastColorWhite = true;

    for (int i = 0; i < printChar.length; i++) {
      for (int j = 0; j < printChar[i].length; j++) {
        lastColorWhite = chooseColor(printChar[i][j], sb, lastColorWhite);
      }
      sb.append((i == printChar.length - 1) ? "" : "\n");
    }

    clearScreen();
    System.out.print(sb.toString());
  }

  private static boolean chooseColor(char currentChar, StringBuilder sb, boolean lastColorWhite) {
    if (currentChar == 'Z') { // Зомби
      sb.append(ANSI_GREEN + currentChar);
      lastColorWhite = false;
    } else if (currentChar == 'V') { // Вампир
      sb.append(ANSI_RED + currentChar);
      lastColorWhite = false;
    } else if (currentChar == 'G' || currentChar == 'S') { // Привидение и змея
      sb.append(ANSI_BLUE + currentChar);
      lastColorWhite = false;
    } else if (currentChar == 'O') { // Огр
      sb.append(ANSI_YELLOW + currentChar);
      lastColorWhite = false;
    } else {
      if (!lastColorWhite) {
        sb.append(ANSI_RESET);
      }
      sb.append(currentChar);
      lastColorWhite = true;
    }

    return lastColorWhite;
  }

  private static void clearScreen() {
    System.out.print("\n\033[2J");
  }

  public static void hideCursor() {
    System.out.print("\033[?25l");
  }

  public static void showCursor() {
    System.out.print("\033[?25h");
  }

  private static void cmdRawMode() throws Exception {
    String[] cmd = { "/bin/sh", "-c", "stty raw -echo </dev/tty" };
    Runtime.getRuntime().exec(cmd).waitFor();
  }

  public static void resetCmd() {
    try {
      String[] resetCmd = { "/bin/sh", "-c", "stty sane </dev/tty" };
      Runtime.getRuntime().exec(resetCmd).waitFor();

    } catch (Exception e) {
      Thread.currentThread().interrupt();
      e.printStackTrace();
    }
  }

  public static String getString() {
    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    String input = "";
    try {
      input = reader.readLine();
    } catch (Exception e) {
      Thread.currentThread().interrupt();
      e.printStackTrace();
    }

    return input;
  }
}