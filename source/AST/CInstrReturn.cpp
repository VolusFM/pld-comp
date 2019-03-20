#include "CInstrReturn.h"

#include <string>
using std::to_string;

/*
 * Default constructor - If there is no return (return void),
 * set expr to nullptr to be able to recognize it.
 */
CInstrReturn::CInstrReturn() :
        expr(nullptr) {

}

CInstrReturn::CInstrReturn(CExpression * expr) :
        expr(expr) {
}

CInstrReturn::~CInstrReturn() {
    if (expr != nullptr) {
        delete expr;
    }
}

string CInstrReturn::to_asm() const {
    string code;

    int * returnValue = nullptr;
    if (dynamic_cast<CExpressionInt *>(expr) != nullptr) {
        returnValue = &dynamic_cast<CExpressionInt *>(expr)->value;
    }

    if (returnValue != nullptr) {
        code += "  movl $" + to_string(*returnValue) + ", %eax\n";
    }
    code += "  popq %rbp\n";
    code += "  ret\n";
    return code;
}

