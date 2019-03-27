#include "CInstrVariableMulti.h"

CInstrVariableMulti::CInstrVariableMulti(vector<CInstrVariable*> varDefs){
    this->varDefs = vector<CInstrVariable*>(varDefs);
}

CInstrVariableMulti::~CInstrVariableMulti(){
}

string CInstrVariableMulti::to_asm(const CFunction * f) const{
    string result = "";
    for (auto varDef : varDefs){
        result+=varDef->to_asm(f);
    }
    return result;
}