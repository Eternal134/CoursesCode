package ex4;

public class Dog implements Animal{
	public void cry() {
		System.out.println("汪汪汪");
	}
	
	public String getAnimalName() {
		return "Dog";
	}
}
