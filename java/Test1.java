public class Test1 {
    public static void main(String args[]) {
        String s1 = "a";
        String s2 = "80";
        System.out.printf(s1 + s2);
        Double d1 = new Double(s1);
        Double d2 = new Double(s2);
        double m1 = d1.doubleValue();
        double m2 = d2.doubleValue();
        System.out.println(m1 + m2);
    }
}
