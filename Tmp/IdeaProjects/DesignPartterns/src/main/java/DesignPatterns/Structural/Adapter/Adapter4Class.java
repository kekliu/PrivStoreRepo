package DesignPatterns.Structural.Adapter;

/**
 * Created by kekliu on 6/20/17.
 * 类适配器
 * <p>
 * 核心思想：
 * 有一个Source类，拥有一个方法method1()，
 * 待适配目标接口时Targetable，通过Adapter类，将Source的方法method1()扩展到Targetable里
 */
public class Adapter4Class extends Source implements Targetable {
    public void method2() {
        System.out.println("this is the targetable method!");
    }
}
