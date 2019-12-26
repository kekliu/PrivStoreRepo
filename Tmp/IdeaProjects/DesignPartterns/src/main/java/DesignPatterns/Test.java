package DesignPatterns;

/**
 * Created by kekliu on 6/17/17.
 * 测试类,可以选择何种模式进行测试
 */
public class Test {

    private Test() {

    }

    public static void DoTest(DesignPatterns.Type type) {
        switch (type) {
            case C_FACTORY_METHOD:
                DesignPatterns.Creational.FactoryMethod.Test.DoTest();
                break;
            case C_ABSTRACT_FACTORY:
                DesignPatterns.Creational.AbstractFactory.Test.DoTest();
                break;
            case C_BUILDER:
                DesignPatterns.Creational.Builder.Test.DoTest();
                break;
            case C_SINGLETON:
                DesignPatterns.Creational.Singleton.Test.DoTest();
                break;
            case C_PROTOTYPE:
                DesignPatterns.Creational.Prototype.Test.DoTest();
                break;
            case S_ADAPTER:
                DesignPatterns.Structural.Adapter.Test.DoTest();
                break;
            case S_DECORATOR:
                break;
            default:
                System.out.println("pattern not defined yet");
                break;
        }
    }

}
