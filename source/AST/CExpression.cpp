#include "CExpression.h"

#include <string>
using std::to_string;

CExpression::~CExpression() {
    //FIXME : could be removed
}

// ----------------- CExpressionInt -----------------

CExpressionInt::CExpressionInt(int value) :
        value(value) {
}

string CExpressionInt::to_asm() const {
    string code;
    code = to_string(value);
    return code;
}

CExpressionInt::~CExpressionInt() {
    // Nothing to do.
}

// ----------------- CExpressionVar -----------------

CExpressionVar::CExpressionVar(const string variable) :
        variable(variable) {

}

string CExpressionVar::to_asm() const {
    string code;
    code = variable;
    return code;
}

CExpressionVar::~CExpressionVar() {
    // Nothing to do.
}

// -------------- CExpressionComposed ---------------

CExpressionComposed::CExpressionComposed(CExpression * lhs, string op,
        CExpression * rhs) :
        lhs(lhs), op(op), rhs(rhs) {

}

string CExpressionComposed::to_asm() const {
    string code;
    code = "(" + lhs->to_asm() + op + rhs->to_asm() + ")";
    return code;
}

CExpressionComposed::~CExpressionComposed() {
    //if (lhs != nullptr) { delete lhs; }
    //if (rhs != nullptr) { delete rhs; }
    //delete lhs;
    //delete rhs;
}

