package DesignPatterns.Creational.FactoryMethod;

public class JpgReader extends ImageReader {
    @Override
    public void read(String filename) {
        System.out.printf("jpg::read(%s)\n", filename);
    }
}
