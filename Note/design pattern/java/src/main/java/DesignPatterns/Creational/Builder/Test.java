package DesignPatterns.Creational.Builder;


/**
 * Created by kekliu on 6/17/17.
 * 当类较为复杂且其中许多不是必要参数,
 * 则可以使用Builder模式"逐渐建造"一个复杂的对象
 */
public class Test {

    private Test() {

    }

    public static void DoTest() {
        User user = new User.UserBuilder("李", "四")
                .phone("123456789")
                .address("亚特兰蒂斯大陆")
                .build();

        System.out.println("Build success!!");
    }

}
