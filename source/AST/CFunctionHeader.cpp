#include "CFunctionHeader.h"


CFunctionHeader::CFunctionHeader(string name, vector<CParameter>& parameters) :
        name(name), parameters(parameters){}

CParameter::CParameter(string name, CType type) :
        name(name), type(type){}

string CParameter::to_asm(const CFunction* f, int index) const {
    string variable = f->tos_addr(name);
    string code = "  movl %" + registerName[index] + ", " + variable + " # Move the parameter to one of the function registers\n";
    return code;
}

