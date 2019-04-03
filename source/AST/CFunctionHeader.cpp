#include "CFunctionHeader.h"

#include "CFunction.h"

CFunctionHeader::CFunctionHeader(string name, vector<CParameter>& parameters_)
: name(name)
{
    parameters = std::move(parameters_);
}

CParameter::CParameter(string name, CType type)
: name(name), type(type)
{
}

string CParameter::to_asm(const CFunction* f, int index) const {
    static const string registerName[] = { "rdi", "rsi", "rdx", "rcx", "r8d", "r9d" };
    
    string variable = f->tos_addr(name);
    string code = "  movl %" + registerName[index] + ", " + variable + " # Move the parameter to one of the function registers\n";
    return code;
}

