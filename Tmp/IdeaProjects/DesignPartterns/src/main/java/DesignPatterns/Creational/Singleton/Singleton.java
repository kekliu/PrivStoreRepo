package DesignPatterns.Creational.Singleton;

/**
 * Created by kekliu on 6/19/17.
 * 经过高度优化后的单例模式
 * 原文: http://www.jianshu.com/p/25b995824638
 */
public enum Singleton {
    INSTANCE;

    public void speak() {
        System.out.println(this + " is speaking! ");
    }
}
