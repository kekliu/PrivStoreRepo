package DesignPatterns.Behavioral.Observer;

public class ConcreteObserver1 implements Observer{
    @Override
    public void update() {
        System.out.println("observer1");
    }
}
