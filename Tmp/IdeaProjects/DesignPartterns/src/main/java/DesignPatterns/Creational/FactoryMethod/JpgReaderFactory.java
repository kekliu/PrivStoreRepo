package DesignPatterns.Creational.FactoryMethod;

public class JpgReaderFactory implements ImageReaderFactory {
    @Override
    public ImageReader getImageReader() {
        return new JpgReader();
    }
}
