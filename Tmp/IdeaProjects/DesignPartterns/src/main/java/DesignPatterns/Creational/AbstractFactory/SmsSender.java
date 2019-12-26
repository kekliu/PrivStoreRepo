package DesignPatterns.Creational.AbstractFactory;

/**
 * Created by kekliu on 6/17/17.
 */
public class SmsSender implements Sender {
    public void Send() {
        System.out.println("Send() in SmsSender called");
    }
}
