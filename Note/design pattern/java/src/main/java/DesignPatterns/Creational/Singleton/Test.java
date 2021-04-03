package DesignPatterns.Creational.Singleton;

/**
 * Created by kekliu on 6/17/17.
 * 单例模式
 */
public class Test {

    private Test() {

    }

    public static void DoTest() {
        Singleton s1 = Singleton.INSTANCE;
        s1.speak();
        Singleton s2 = Singleton.INSTANCE;
        s2.speak();
        System.out.println(s1.equals(s2)); // 对枚举类型,equals()和 == 是一样的
    }

}
