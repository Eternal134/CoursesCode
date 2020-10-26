package ex4;

public class Application {
	public static void main(String arg[]) {
		Simulator simulator = new Simulator();
		simulator.playSound(new Cat());
		simulator.playSound(new Dog());
	}
}
