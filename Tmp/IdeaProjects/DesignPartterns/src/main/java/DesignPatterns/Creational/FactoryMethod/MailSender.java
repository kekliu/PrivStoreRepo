package DesignPatterns.Creational.FactoryMethod;

public class MailSender implements Sender {
    public void Send() {
        System.out.println("Send() in MailSender called");
    }
}
