package DesignPatterns.Structural.Adapter;

/**
 * Created by kekliu on 6/20/17.
 * 接口适配器实现类2
 */
public class SourceSub2 extends Adapter4Interface {
    @Override
    public void method1() {
        System.out.println("the sourceable interface's second Sub2!");
    }
}
