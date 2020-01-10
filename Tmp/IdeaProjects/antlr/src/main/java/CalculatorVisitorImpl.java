import grammer.CalculatorBaseVisitor;
import grammer.CalculatorParser;

public class CalculatorVisitorImpl extends CalculatorBaseVisitor<Double> {
    @Override
    public Double visitExpression(CalculatorParser.ExpressionContext ctx) {
        if (ctx.expression() == null) return visit(ctx.multiplyingExpression());
        if (ctx.PLUS() != null) return visit(ctx.expression()) + visit(ctx.multiplyingExpression());
        return visit(ctx.expression()) - visit(ctx.multiplyingExpression());
    }

    @Override
    public Double visitMultiplyingExpression(CalculatorParser.MultiplyingExpressionContext ctx) {
        return visit(ctx.powExpression());
    }

    @Override
    public Double visitPowExpression(CalculatorParser.PowExpressionContext ctx) {
        return visit(ctx.signedAtom());
    }

    @Override
    public Double visitSignedAtom(CalculatorParser.SignedAtomContext ctx) {
        return visit(ctx.atom());
    }

    @Override
    public Double visitAtom(CalculatorParser.AtomContext ctx) {
        return visit(ctx.scientific());
    }

    @Override
    public Double visitScientific(CalculatorParser.ScientificContext ctx) {
        var a = visit(ctx.SCIENTIFIC_NUMBER());
//        return Double.parseDouble(ctx.SCIENTIFIC_NUMBER().getText());
        return visit(ctx.SCIENTIFIC_NUMBER());
    }

}