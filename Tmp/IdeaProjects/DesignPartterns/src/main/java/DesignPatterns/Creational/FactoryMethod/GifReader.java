package DesignPatterns.Creational.FactoryMethod;

public class GifReader extends ImageReader {
    @Override
    public void read(String filename) {
        System.out.printf("gif::read(%s)\n", filename);
    }
}
