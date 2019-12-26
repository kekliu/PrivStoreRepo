package DesignPatterns.Structural.Adapter;

/**
 * Created by kekliu on 6/20/17.
 * 接口适配器实现类1
 */
public class SourceSub1 extends Adapter4Interface {
    @Override
    public void method1() {
        System.out.println("the sourceable interface's first Sub1!");
    }
}
