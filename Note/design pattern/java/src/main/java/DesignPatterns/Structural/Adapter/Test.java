package DesignPatterns.Structural.Adapter;

/**
 * Created by kekliu on 6/17/17.
 * 适配器模式:
 * <p>
 * 种类: 类适配器 对象适配器 接口适配器
 */
public class Test {

    private Test() {

    }

    public static void DoTest() {
        System.out.println("Adapter for class:");
        Targetable target = new Adapter4Class();
        target.method1();
        target.method2();

        System.out.println("Adapter for object:");
        Source source = new Source();
        Targetable target1 = new Adapter4Object(source);
        target1.method1();
        target1.method2();

        System.out.println("Adapter for interface:");
        Targetable targetable = new SourceSub1();
        Targetable targetable1 = new SourceSub2();
        targetable.method1();
        targetable.method2();
        targetable1.method1();
        targetable1.method2();
    }

}
