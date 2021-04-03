package DesignPatterns.Creational.Builder;

/**
 * Created by kekliu on 6/19/17.
 * 非常有意思的一个例子
 * 原文地址: http://www.jianshu.com/p/e2a2fe3555b9
 */
public class User {

    // final成员变量必须在声明的时候初始化或者在构造函数中初始化
    private final String firstName;     // 必传参数
    private final String lastName;      // 必传参数
    private final int age;              // 可选参数
    private final String phone;         // 可选参数
    private final String address;       // 可选参数

    // private是为了避免构造函数被外部调用
    private User(UserBuilder builder) {
        this.firstName = builder.firstName;
        this.lastName = builder.lastName;
        this.age = builder.age;
        this.phone = builder.phone;
        this.address = builder.address;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public int getAge() {
        return age;
    }

    public String getPhone() {
        return phone;
    }

    public String getAddress() {
        return address;
    }

    public static class UserBuilder {
        // final对应于上面的必要参数
        private final String firstName;
        private final String lastName;
        private int age;
        private String phone;
        private String address;

        public UserBuilder(String firstName, String lastName) {
            this.firstName = firstName;
            this.lastName = lastName;
        }

        public UserBuilder age(int age) {
            this.age = age;
            return this;
        }

        public UserBuilder phone(String phone) {
            this.phone = phone;
            return this;
        }

        public UserBuilder address(String address) {
            this.address = address;
            return this;
        }

        /**
         * Builder函数
         *
         * 由于Builder是非线程安全的，所以如果要在Builder内部类中检查一个参数的合法性，必需要在对象创建完成之后再检查。
         * @return
         */
        public User build() {
            User user = new User(this);
            if (user.getAge() > 120) {
                throw new IllegalStateException("Age out of range"); // 线程安全
            }
            return user;
        }
    }
}
