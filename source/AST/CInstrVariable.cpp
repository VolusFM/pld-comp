#include "CInstrVariable.h"

CInstrVariable::CInstrVariable(CType type, string name) :
        type(type), name(name), expr(nullptr) {
}

CInstrVariable::CInstrVariable(CType type, string name, CExpression * expr) :
        type(type), name(name), expr(expr) {
}

CInstrVariable::~CInstrVariable() {
    if (expr != nullptr) {
        delete expr;
    }
}

string CInstrVariable::to_asm() const {
//TODO : memCase positif, nb case memoire a partir de rbp
    string code;
    if (expr != nullptr) {
        code += expr->to_asm(); //TODO : return adress resultat expression
                                // soit eax soit $valeur
        //code += "movl " + expr->result();
        //code += "-4(%rbp) \n";
    }
    return code;
}

