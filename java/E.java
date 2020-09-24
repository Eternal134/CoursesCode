import java.util.*;
public class E {
    public static void main (String args[]) {
        int i, j, count = 0;
        for(i = 2; i < 100; i ++) {
            for(j = 2; j <= Math.sqrt(i); j ++) {
                if(i % j == 0) {
                    break;
                }
            }
            if(j > Math.sqrt(i)) {
                System.out.print(i + "\t");
                count ++;
                if(count % 5 == 0) {
                    System.out.print("\n");
                }
            }
        }
    }
}