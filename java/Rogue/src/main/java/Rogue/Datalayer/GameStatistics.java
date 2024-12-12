package Rogue.Datalayer;

import java.util.Arrays;
import java.util.Comparator;

public class GameStatistics {
  private String lastStatistics;

  public GameStatistics() {
    this.lastStatistics = "";
  }

  public void updateLastStatistics(String newStatistics) {
    if (newStatistics == null || newStatistics.isEmpty()) {
      this.lastStatistics = "";
    } else {
      this.lastStatistics = sorted(newStatistics);
    }
  }

  public String getLastStatistics() {
    return lastStatistics;
  }

  public String sorted(String newStatistics) {
    String[] lines = Arrays.stream(newStatistics.split("\n"))
        .filter(line -> !line.trim().isEmpty())
        .toArray(String[]::new);

    if (lines.length == 0) {
      this.lastStatistics = newStatistics;
      return newStatistics;
    }

    Arrays.sort(lines, Comparator.comparingInt(line -> {
      String[] parts = line.split("сокровища: ");
      if (parts.length < 2) {
        return 0;
      }
      try {
        String numberWithSpaces = parts[1].trim();
        String number = numberWithSpaces.split(",")[0].trim();
        int temp = Integer.parseInt(number);
        return -temp;
      } catch (NumberFormatException e) {
        return 0;
      }
    }));

    this.lastStatistics = String.join("\n", lines);
    return this.lastStatistics;
  }

}