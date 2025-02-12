package temp;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class App {

  public static void main(String[] args) {
    long startTime = System.currentTimeMillis();


    List<long[]> data = input();
    List<Set<Integer>> groups = new ArrayList<>();
    findGroups(data, groups);
    groups.sort((set1, set2) -> Integer.compare(set2.size(), set1.size()));
    output(getUniqueRows(groups, data));

    long endTime = System.currentTimeMillis();
    double duration = (endTime - startTime) / 1000.0;
    System.out.println("Время выполнения: " + duration + " секунд");
  }

  private static List<long[]> input() {
    List<long[]> data = new ArrayList<>();

    try (BufferedReader br = new BufferedReader(new FileReader("lng.txt"))) {
      String line;

      while ((line = br.readLine()) != null) {
        List<Long> numbers = new ArrayList<>();
        String[] parts = line.split(";");
        for (String part : parts) {
          part = part.replace("\"", "").trim();
          if (part.matches("\\d{1,11}")) {
            numbers.add(Long.parseLong(part));
          } else {
            numbers.add(0L);
          }
        }

        if (!numbers.isEmpty()) {
          data.add(numbers.stream().mapToLong(Long::longValue).toArray());
        }
      }

    } catch (IOException e) {
      e.printStackTrace();
    }

    return data;
  }

  private static void findGroups(List<long[]> data, List<Set<Integer>> groups) {
    Map<Long, List<Integer>> valueToRows = new HashMap<>();
    int numRows = data.size();

    for (int i = 0; i < numRows; i++)
      for (long value : data.get(i))
        if (value != 0)
          valueToRows.computeIfAbsent(value, k -> new ArrayList<>()).add(i);

    boolean[] visited = new boolean[numRows];

    for (int i = 0; i < numRows; i++) {
      if (!visited[i]) {
        List<Integer> group = new ArrayList<>();
        dfs(i, visited, group, valueToRows, data);

        if (group.size() > 1) {
          choiceGroups(data, group.stream().mapToInt(Integer::intValue).toArray(), groups);
        }
      }
    }
  }

  private static void dfs(int row, boolean[] visited, List<Integer> group, Map<Long, List<Integer>> valueToRows,
      List<long[]> data) {
    visited[row] = true;
    group.add(row);

    for (long value : data.get(row)) {
      if (value != 0) {
        List<Integer> connectedRows = valueToRows.get(value);
        if (connectedRows != null) {
          for (int connectedRow : connectedRows) {
            if (!visited[connectedRow]) {
              dfs(connectedRow, visited, group, valueToRows, data);
            }
          }
        }
      }
    }
  }

  private static void choiceGroups(List<long[]> data, int[] group, List<Set<Integer>> groups) {
    List<Set<Integer>> groupMap = findCommonNumbers(data, group);

    for (int i = 0; i < groupMap.size(); i++) {
      if (groupMap.get(i).size() > 1) {
        int lastSize;

        do {
          lastSize = groupMap.get(i).size();
          findCommonString(groupMap, i);

        } while (groupMap.get(i).size() > lastSize);
        groups.add(groupMap.get(i));
      }
    }
  }

  private static List<Set<Integer>> findCommonNumbers(List<long[]> data, int[] group) {
    Map<String, Set<Integer>> numberPositionToRows = new HashMap<>();
    List<Set<Integer>> groupMap = new ArrayList<>();

    for (int rowIndex = 0; rowIndex < group.length; rowIndex++) {
      long[] row = data.get(group[rowIndex]);
      for (int pos = 0; pos < row.length; pos++) {
        if (row[pos] != 0) {
          String key = row[pos] + "_" + pos;
          numberPositionToRows.computeIfAbsent(key, k -> new HashSet<>()).add(group[rowIndex]);
        }
      }
    }

    for (Set<Integer> rowSet : numberPositionToRows.values()) {
      if (rowSet.size() > 1) {
        groupMap.add(rowSet);
      }
    }
    return groupMap;
  }

  private static void findCommonString(List<Set<Integer>> groupMap, int i) {
    for (int j = 0; j < groupMap.size(); j++)
      if (i != j)
        for (Integer num : groupMap.get(j))
          if (groupMap.get(i).contains(num)) {
            groupMap.get(i).addAll(groupMap.get(j));
            groupMap.remove(j);
            j--;
            break;
          }
  }

  private static List<Set<String>> getUniqueRows(List<Set<Integer>> groups, List<long[]> result) {
    List<Set<String>> uniqueRowsList = new ArrayList<>();

    for (Set<Integer> group : groups) {
      Set<String> uniqueRows = new HashSet<>();
      for (Integer index : group) {
        String rowString = Arrays.toString(result.get(index));
        uniqueRows.add(rowString);
      }
      if (uniqueRows.size() > 1)
        uniqueRowsList.add(uniqueRows);
    }

    return uniqueRowsList;
  }

  private static void output(List<Set<String>> uniqueRowsList) {
    try (BufferedWriter bw = new BufferedWriter(new FileWriter("result.txt"))) {
      bw.write("Количество групп с более чем одним элементом: " + uniqueRowsList.size());
      bw.newLine();

      for (int i = 0; i < uniqueRowsList.size(); i++) {
        Set<String> uniqueRows = uniqueRowsList.get(i);
        bw.write("Группа " + (i + 1));
        bw.newLine();
        for (String uniqueRow : uniqueRows) {
          bw.write(uniqueRow);
          bw.newLine();
        }
      }
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}