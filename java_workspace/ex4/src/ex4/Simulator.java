package ex4;

public class Simulator {
	public void playSound(Animal animal) {
		System.out.print(animal.getAnimalName() + ":  ");
		animal.cry();
	}
}
