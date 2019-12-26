package DesignPatterns.Creational.Prototype;

import java.io.*;

/**
 * Created by kekliu on 6/19/17.
 * 原型模式
 * 包含浅复制和深复制
 */
public class Prototype implements Cloneable, Serializable {

    private static final long serialVersionUID = 1L;

    private String string;

    private SerializableObject obj;

    /* 浅复制 */
    @Override
    protected Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    /* 深复制 */
    Object deepClone() throws IOException, ClassNotFoundException {

        /* 写入当前对象的二进制流 */
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
        ObjectOutputStream objectOutputStream = new ObjectOutputStream(byteArrayOutputStream);
        objectOutputStream.writeObject(this);

        /* 读出二进制流产生的新对象 */
        ByteArrayInputStream byteArrayInputStream = new ByteArrayInputStream(byteArrayOutputStream.toByteArray());
        ObjectInputStream objectInputStream = new ObjectInputStream(byteArrayInputStream);
        return objectInputStream.readObject();
    }

    void setObj(SerializableObject obj) {
        this.obj = obj;
    }

    SerializableObject getObj() {
        return obj;
    }
}
