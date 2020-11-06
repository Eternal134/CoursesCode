import java.util.InputMismatchException;
import java.util.*;

public class cal_grade {
	public static void main(String args[]) {
		String str = "数学87分，物理76分，英语96分";
		java.util.Scanner scanner = new Scanner(str);
		scanner.useDelimiter("[^0-9]+");
		int sum = 0;
		while(scanner.hasNext()) {
			try {
				int grade = scanner.nextInt();
				sum += grade;
			}
			catch (InputMismatchException exp) {
				String t = scanner.next();
			}
		}
		System.out.printf("总分：%d\n平均分：%.2f", sum, sum / 3.);
	}
}