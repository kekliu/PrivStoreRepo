public class Book {
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public String getPromowords() {
        return promowords;
    }

    public void setPromowords(String promowords) {
        this.promowords = promowords;
    }

    @Override
    public String toString() {
        return "Book{" +
                "name='" + name + '\'' +
                ", price=" + price +
                ", promowords='" + promowords + '\'' +
                '}';
    }

    private String name;
    private double price;
    private String promowords;

}
