package DesignPatterns.Creational.FactoryMethod;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class ImageReaderFactoryTest {

    @Test
    void getImageReader() {
        ImageReaderFactory imageReaderFactory = new JpgReaderFactory();
        ImageReader imageReader = imageReaderFactory.getImageReader();
        imageReader.read("123.jpg");
        imageReaderFactory = new GifReaderFactory();
        imageReader = imageReaderFactory.getImageReader();
        imageReader.read("123.gif");
    }
}