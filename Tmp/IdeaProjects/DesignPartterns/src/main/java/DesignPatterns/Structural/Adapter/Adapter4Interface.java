package DesignPatterns.Structural.Adapter;

/**
 * Created by kekliu on 6/20/17.
 * 接口适配器
 * <p>
 * 接口的适配器是这样的：有时我们写的一个接口中有多个抽象方法，当我们写该接口的实现类时，必须实现该接口的所有方法，
 * 这明显有时比较浪费，因为并不是所有的方法都是我们需要的，有时只需要某一些，此处为了解决这个问题，
 * 我们引入了接口的适配器模式，借助于一个抽象类，该抽象类实现了该接口，实现了所有的方法，而我们不和原始的接口打交道，
 * 只和该抽象类取得联系，所以我们写一个类，继承该抽象类，重写我们需要的方法就行。
 */
public class Adapter4Interface implements Targetable {
    public void method1() {

    }

    public void method2() {

    }
}
