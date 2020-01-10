package DesignPatterns.Behavioral.Observer;

public class ConcreteSubject extends Subject {
    @Override
    public void notifyObservers() {
        System.out.println("notifying observers...");
        for (var o : observers) {
            o.update();
        }
    }
}
