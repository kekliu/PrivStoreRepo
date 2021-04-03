package DesignPatterns.Behavioral.Observer;

public class Test {
    public static void doTest() {
        Subject subject = new ConcreteSubject();
        Observer observer1 = new ConcreteObserver1();
        Observer observer2 = new ConcreteObserver2();
        subject.attach(observer1);
        subject.attach(observer2);
        subject.notifyObservers();
    }
}
