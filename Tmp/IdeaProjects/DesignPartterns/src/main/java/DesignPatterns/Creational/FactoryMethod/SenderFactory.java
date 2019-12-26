package DesignPatterns.Creational.FactoryMethod;

/**
 * Created by kekliu on 6/17/17.
 */
public class SenderFactory {

    private SenderFactory() {

    }

    /**
     * 简单工厂方法
     *
     * @param type
     * @return
     */
    public static Sender CreateProduct(String type) {
        if (type.equals("mail")) {
            return new MailSender();
        } else if (type.equals("sms")) {
            return new SmsSender();
        } else {
            return null;
        }
    }

    public static Sender CreateProduct(Class<?> _class) {
        if (_class.equals(MailSender.class)) {
            return new MailSender();
        } else if (_class.equals(SmsSender.class)) {
            return new SmsSender();
        } else {
            return null;
        }
    }

    /*
    // 静态工厂方法
    public static Sender CreateProductSmsSender(){
        return new SmsSender();
    }

    public static Sender CreateProductMailSender(){
        return new MailSender();
    }
    */
}
