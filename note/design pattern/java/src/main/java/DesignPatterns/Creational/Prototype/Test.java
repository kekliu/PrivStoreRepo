package DesignPatterns.Creational.Prototype;

import java.io.IOException;

/**
 * Created by kekliu on 6/17/17.
 * 原型模式
 * <p>
 * 关键词: 深复制 浅复制
 */
public class Test {

    private Test() {

    }

    public static void DoTest() {
        try {
            Prototype prototype = new Prototype();
            prototype.setObj(new SerializableObject());
            Prototype prototype1 = (Prototype) prototype.deepClone();
            System.out.println(prototype == prototype1);
            System.out.println(prototype.getObj() == prototype1.getObj());
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

}
