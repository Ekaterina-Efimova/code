package exercise04;

import java.util.List;
import java.util.concurrent.CompletableFuture;

public class Output {
  private Input input;

  public Output(Input input) {
    this.input = input;
  }

  public void output(int count, double startTime) {
    List<Animal> pets = input.get_animals(count);

    CompletableFuture<?>[] futures = pets.stream()
        .map(pet -> CompletableFuture.runAsync(() -> walkPet(pet, startTime)))
        .toArray(CompletableFuture[]::new);

    CompletableFuture.allOf(futures).join();
  }

  private void walkPet(Animal pet, double startTime) {
    double startWalkTime = (System.currentTimeMillis() - startTime) / 1000.0;
    double walkTime = pet.goToWalk();
    double endWalkTime = startWalkTime + walkTime;

    System.out.println(pet.toString() + ", start time = " + String.format("%.2f", startWalkTime) + ", end time = "
        + String.format("%.2f", endWalkTime));
  }
}
