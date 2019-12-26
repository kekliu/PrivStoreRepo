import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.util.ArrayList;

public class MainClass {

    static ArrayList<Book> books;

    static String keyword = "余光中";

    public static void main(String[] args) {

        books = new ArrayList<Book>();

        try {

            // 获取网页内容
            Document doc = Jsoup.connect("https://search.jd.com/Search?keyword="
                    + keyword + "&enc=utf-8")
                    .userAgent("Mozilla")
                    .timeout(3000)
                    .post();

            // 获取所有书的列表
            Elements book_nodes = doc.getElementsByClass("gl-item");

            // 获取每一本书的名字，价格，简介
            for (Element e : book_nodes) {
                Document book_node_ = Jsoup.parse(e.toString());
                Element name_node = book_node_.selectFirst(".p-name em");
                Element price_node = book_node_.selectFirst(".p-price i");
                Element promowords_node = book_node_.selectFirst(".promo-words");

                Book book = new Book();

                book.setName(name_node.text());
                book.setPrice(Double.parseDouble(price_node.text()));
                book.setPromowords(promowords_node.text());

                books.add(book);

                System.out.println(book);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
