#include "CInstruction.h"
#include "CInstrExpression.h"
#include "CInstrReturn.h"
#include "CInstrVariable.h"
#include "CInstrArray.h"
#include "CInstrIf.h"
#include "CInstrFor.h"
#include "CInstrDoWhile.h"
#include "CInstrWhile.h"

#include <iostream>
using std::cerr;
using std::endl;
#include <string>
using std::to_string;
#include <utility>
using std::pair;

#include "CExpression.h"

string CInstructions::to_asm(const CFunction* f) const {
    string code = "";
    for (auto instruction : instructions){
        code += instruction->to_asm(f);
    }
    return code;
}

string CInstrExpression::to_asm(const CFunction* f) const
{
    CFunction* fm = const_cast<CFunction*>(f);
    return expr->to_asm(fm).first;
}

string CInstrArray::to_asm(const CFunction* f) const
{
    //to do
    return "todo";
}

string CInstrVariable::to_asm(const CFunction* f) const {
    if (expr == nullptr) {
        return "";
    } else {
        return expr->to_asm(f).first;
    }
}

string CInstrReturn::to_asm(const CFunction* f) const {
    string code;
    
    if (expr != nullptr) {
        pair<string, string> res = expr->to_asm(f);
        code += res.first;
        code += "  movl " + res.second + ", %eax\n";
    }
    code += "  popq %rbp\n";
    code += "  ret\n";
    return code;
}

string CInstrIf::to_asm(const CFunction* f) const {
    cerr << "PROBLEM: to_asm unimplemented for control statements" << endl;
    throw;
}

string CInstrDoWhile::to_asm(const CFunction* f) const {
    cerr << "PROBLEM: to_asm unimplemented for control statements" << endl;
    throw;
}

string CInstrFor::to_asm(const CFunction* f) const {
    cerr << "PROBLEM: to_asm unimplemented for control statements" << endl;
    throw;
}

string CInstrWhile::to_asm(const CFunction* f) const {
    cerr << "PROBLEM: to_asm unimplemented for control statements" << endl;
    throw;
}

