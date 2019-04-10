#include "CExpression.h"

#include "CFunction.h"

void CExpression::optimize() {
    CExpressionPart* opti = expr->optimize();
    if (opti != nullptr) {
        delete expr;
        expr = opti;
    }
}

CExpression::CExpression(CExpressionPart* expr)
: expr(expr)
{
}

CExpression::~CExpression() {
    delete expr;
}

CExpressionInt::CExpressionInt(int value)
: value(value)
{
}

CExpressionVar::CExpressionVar(string variable)
: variable(variable)
{
}

CExpressionVarArray::CExpressionVarArray(string variable, CExpressionPart* index)
: variable(variable), index(index)
{
}

CExpressionVarArray::~CExpressionVarArray() {
    delete index;
}

CExpressionComposed::CExpressionComposed(CExpressionPart* lhs, string op, CExpressionPart* rhs)
: lhs(lhs), op(op), rhs(rhs)
{
}

CExpressionComposed::~CExpressionComposed() {
    delete lhs;
    delete rhs;
}

CExpressionPart* CExpressionPart::optimize() {
    return nullptr;
}

CExpressionPart* CExpressionComposed::optimize()
{
    // optimize each subexpression
    
    CExpressionPart* opti;
    
    opti = lhs->optimize();
    if (opti != nullptr) {
        delete lhs;
        lhs = opti;
    }
    
    opti = rhs->optimize();
    if (opti != nullptr) {
        delete rhs;
        rhs = opti;
    }
    
    // optimize composed expression
    
    CExpressionInt* lhsval = dynamic_cast<CExpressionInt*>(lhs);
    CExpressionInt* rhsval = dynamic_cast<CExpressionInt*>(rhs);
    
    if ((lhsval == nullptr) || (rhsval == nullptr)) return nullptr;
    
    int lval = lhsval->value;
    int rval = rhsval->value;
    
    if (op == "*") {
        return new CExpressionInt(lval * rval);
    }
    if (op == "/") {
        if (rval != 0) return new CExpressionInt(lval / rval);
    }
    if (op == "%") {
        if (rval != 0) return new CExpressionInt(lval % rval);
    }
    if (op == "+") {
        return new CExpressionInt(lval + rval);
    }
    if (op == "-") {
        return new CExpressionInt(lval - rval);
    }
    
    if (op == "<") {
        return new CExpressionInt(lval < rval ? 1 : 0);
    }
    if (op == "<=") {
        return new CExpressionInt(lval <= rval ? 1 : 0);
    }
    if (op == ">") {
        return new CExpressionInt(lval > rval ? 1 : 0);
    }
    if (op == ">=") {
        return new CExpressionInt(lval >= rval ? 1 : 0);
    }
    if (op == "==") {
        return new CExpressionInt(lval == rval ? 1 : 0);
    }
    if (op == "!=") {
        return new CExpressionInt(lval != rval ? 1 : 0);
    }
    
    if (op == "&") {
        return new CExpressionInt(lval & rval);
    }
    if (op == "|") {
        return new CExpressionInt(lval | rval);
    }
    if (op == "^") {
        return new CExpressionInt(lval ^ rval);
    }
    
    if (op == "&&") {
        return new CExpressionInt(lval ? (rval ? 1 : 0) : 0);
    }
    if (op == "||") {
        return new CExpressionInt(lval ? 1 : (rval ? 1 : 0));
    }
    
    return nullptr;
}

