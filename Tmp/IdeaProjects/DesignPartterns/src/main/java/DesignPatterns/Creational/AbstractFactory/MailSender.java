package DesignPatterns.Creational.AbstractFactory;

public class MailSender implements Sender {
    public void Send() {
        System.out.println("Send() in MailSender called");
    }
}
