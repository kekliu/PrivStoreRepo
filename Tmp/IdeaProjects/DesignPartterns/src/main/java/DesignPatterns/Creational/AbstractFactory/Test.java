package DesignPatterns.Creational.AbstractFactory;

/**
 * Created by kekliu on 6/17/17.
 * 抽象工厂模式通过以下方法克服工厂方法模式容易破坏开闭原则的缺点:
 * 1. 创建产品类,继承"产品必要接口"
 * 2. 创建工厂类,继承Provider接口
 * <p>
 * e.g. 本例中,MailSender继承Sender接口,MailSenderFactory类继承Provider接口
 */
public class Test {

    private Test() {

    }

    public static void DoTest() {
        Provider provider = new MailSenderFactory();
        Sender sender = provider.CreateProduct();
        sender.Send();
        Provider provider1 = new SmsSenderFactory();
        Sender sender1 = provider1.CreateProduct();
        sender1.Send();
    }

}
