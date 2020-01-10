import grammer.*;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;

public class MainClass {

    private static void run(String expr) throws Exception {
        CalculatorLexer lexer = new CalculatorLexer(CharStreams.fromString(expr));
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        CalculatorParser parser = new CalculatorParser(tokens);
        var tree = parser.expression();
        CalculatorVisitorImpl impl = new CalculatorVisitorImpl();
        System.out.println(impl.visit(tree));
    }

    public static void main(String[] args) throws Exception {
        run("5-2-1");
    }
}