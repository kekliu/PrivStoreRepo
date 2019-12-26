package DesignPatterns.Structural.Adapter;

/**
 * Created by kekliu on 6/20/17.
 * 对象适配器
 * <p>
 * 基本思路和类的适配器模式相同，只是将Adapter类作修改，这次不继承Source类，而是持有Source类的实例，以达到解决兼容性的问题
 */
public class Adapter4Object implements Targetable {
    private Source source;

    public Adapter4Object(Source source) {
        super();
        this.source = source;
    }

    public void method2() {
        System.out.println("this is the targetable method!");
    }

    public void method1() {
        source.method1();
    }
}
