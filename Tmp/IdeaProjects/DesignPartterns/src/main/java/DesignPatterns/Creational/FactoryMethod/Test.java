package DesignPatterns.Creational.FactoryMethod;

/**
 * Created by kekliu on 6/17/17.
 * 工厂方法模式包括普通工厂方法模式(可能返回null)和静态工厂方法模式(在工厂中为每一种对象写一个静态方法)
 * 缺点: 容易破坏开闭原则,想添加一种产品就要修改工厂类的代码,扩展性差
 */
public class Test {

    private Test() {

    }

    public static void DoTest() {
        Sender sender = SenderFactory.CreateProduct("sms");
        assert sender != null;
        sender.Send();
    }

}
