
import DesignPatterns.Test;
import DesignPatterns.Type;

public class MainClass {
    public static void main(String[] args) {

        for (Type type :
                Type.values()) {
            System.out.println(type + ":");
            Test.DoTest(type);
            System.out.println();
        }

    }
}
