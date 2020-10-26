package one;

public class Application {
	public static void main(String arg[]) {
		Simulator simulator = new Simulator();
		simulator.playSound(new Dog());
		simulator.playSound(new Cat());
	}
}
