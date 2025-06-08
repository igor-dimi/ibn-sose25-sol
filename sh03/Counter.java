public class Counter {
    static int counter = 0;
    public static class Counter_Thread_A extends Thread {
        public void run() {
            synchronized(Counter.class){
                counter = 5;
                counter++;
                counter++;
                System.out.println("A-Counter: " + counter);
            }
        }
    }
    public static class Counter_Thread_B extends Thread {
        public void run() {
            synchronized(Counter.class) {
                counter = 6;
                counter++;
                counter++;
                counter++;
                counter++;
                System.out.println("B-Counter: " + counter);
            }
        }
    }
    public static void main(String[] args) {
        Thread a = new Counter_Thread_A();
        Thread b = new Counter_Thread_B();
        a.start();
        b.start();
    }
}