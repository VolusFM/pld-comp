#include "CInstrExpression.h"

#include <string>
using std::to_string;

CInstrExpression::CInstrExpression(CExpression * expr) :
        expr(expr) {
}

CInstrExpression::~CInstrExpression() {
    if (expr != nullptr) {
        delete expr;
    }
}

string CInstrExpression::to_asm() const {
    string code;
    code = "  # " + expr->to_asm() + "\n";
    return code;
}

