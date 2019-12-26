package DesignPatterns.Creational.AbstractFactory;

/**
 * Created by kekliu on 6/17/17.
 */
public class MailSenderFactory implements Provider {
    public Sender CreateProduct() {
        return new MailSender();
    }
}
