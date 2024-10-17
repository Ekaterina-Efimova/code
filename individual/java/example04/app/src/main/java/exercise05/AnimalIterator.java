package exercise05;

import java.util.List;
import java.util.NoSuchElementException;

public class AnimalIterator implements BaseIterator<Animal> {
  private List<Animal> animals;
  private int index;

  public AnimalIterator(List<Animal> animals) {
    this.animals = animals;
    this.index = 0;
  }

  @Override
  public Animal next() {
    if (hasNext()) {
      return animals.get(index++);

    } else {
      throw new NoSuchElementException("No more elements in the iterator");
    }
  }

  @Override
  public boolean hasNext() {
    return index < animals.size();
  }

  @Override
  public void reset() {
    index = 0;
  }
}
