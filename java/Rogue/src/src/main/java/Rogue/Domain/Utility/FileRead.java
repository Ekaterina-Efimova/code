package Rogue.Domain.Utility;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class FileRead {
  private FileRead() {
  }

  public static void readFromFile(String fileName, char[][] printChar) {
    clearPrintChar(printChar);
    try {
      File file = new File(fileName);
      Scanner scanner = new Scanner(file);

      int row = 0;
      while (scanner.hasNextLine()) {
        String line = scanner.nextLine();
        for (int col = 0; col < printChar[row].length; col++) {
          if (col < line.length()) {
            printChar[row][col] = line.charAt(col);
          } else {
            printChar[row][col] = ' ';
          }
        }
        row++;
      }
      scanner.close();

    } catch (FileNotFoundException e) {
      e.printStackTrace();
    }
  }

  private static void clearPrintChar(char[][] printChar) {
    for (int row = 0; row < printChar.length; row++) {
      for (int col = 0; col < printChar[row].length; col++) {
        printChar[row][col] = ' ';
      }
    }
  }
}