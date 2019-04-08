#include "CExpression.h"

#include "CFunction.h"

CExpressionInt::CExpressionInt(int value)
: value(value)
{
}

CExpressionVar::CExpressionVar(string variable)
: variable(variable)
{
}

CExpressionVarArray::CExpressionVarArray(string variable, CExpression* index)
: variable(variable), index(index)
{
}

CExpressionVarArray::~CExpressionVarArray() {
    delete index;
}

CExpressionComposed::CExpressionComposed(CExpression* lhs, string op, CExpression* rhs)
: lhs(lhs), op(op), rhs(rhs)
{
}

CExpressionComposed::~CExpressionComposed() {
    delete lhs;
    delete rhs;
}

CExpression* CExpression::optimize() {
    return nullptr;
}

CExpression* CExpressionComposed::optimize()
{
    // optimize each subexpression
    
    CExpression* opti;
    
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

