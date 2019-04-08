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

