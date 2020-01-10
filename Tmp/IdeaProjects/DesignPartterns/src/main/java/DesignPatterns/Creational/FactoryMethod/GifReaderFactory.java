package DesignPatterns.Creational.FactoryMethod;

public class GifReaderFactory implements ImageReaderFactory {
    @Override
    public ImageReader getImageReader() {
        return new GifReader();
    }
}
