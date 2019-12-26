import grammer.*;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.ANTLRInputStream;

public class MainClass {

    private static void run(String expr) throws Exception {
        //对每一个输入的字符串，构造一个 ANTLRStringStream 流 in
        ANTLRInputStream in = new ANTLRInputStream(expr);
        //用 in 构造词法分析器 lexer，词法分析的作用是产生记号
        calculatorLexer lexer = new calculatorLexer(in);
        //用词法分析器 lexer 构造一个记号流 tokens
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        //再使用 tokens 构造语法分析器 parser,至此已经完成词法分析和语法分析的准备工作
        calculatorParser parser = new calculatorParser(tokens);
        //最终调用语法分析器的规则 prog，完成对表达式的验证
        parser.expression();
    }

    public static void main(String[] args) throws Exception {

        run("1+3*sqrt(cos(0))");

    }
}