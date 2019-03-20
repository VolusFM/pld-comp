#include "CExpression.h"

#include <string>
using std::to_string;

#include "CFunction.h"

CExpression::~CExpression() {
    //FIXME : could be removed
}

// ----------------- CExpressionInt -----------------

CExpressionInt::CExpressionInt(int value) :
        value(value) {
}

pair<string,string> CExpressionInt::to_asm(CFunction* f) const {
    string variable = f->tos_add_temp("int");
    string varaddr = f->tos_addr(variable);
    string code = "  movl $" + to_string(value) + ", " + varaddr + "\n";
    return pair<string,string>(code,varaddr);
}

CExpressionInt::~CExpressionInt() {
    // Nothing to do.
}

// ----------------- CExpressionVar -----------------

CExpressionVar::CExpressionVar(string variable) :
        variable(variable) {

}

pair<string,string> CExpressionVar::to_asm(CFunction* f) const {
    return pair<string,string>("",f->tos_addr(variable));
}

CExpressionVar::~CExpressionVar() {
    // Nothing to do.
}

// -------------- CExpressionComposed ---------------

CExpressionComposed::CExpressionComposed(CExpression * lhs, string op,
        CExpression * rhs) :
        lhs(lhs), op(op), rhs(rhs) {

}

pair<string,string> CExpressionComposed::to_asm(CFunction* f) const {
    string code;
    string variable;
    
    auto reslhs = lhs->to_asm(f);
    auto resrhs = rhs->to_asm(f);
    
    code += reslhs.first;
    code += resrhs.first;
    
    string lhsvar = reslhs.second;
    string rhsvar = resrhs.second;
    
    if (op == "=") {
        code += "  movl  " + rhsvar + ", %eax\n";
        code += "  movl  %eax, " + lhsvar + "\n";
        variable = lhsvar;
    } else {
        variable = f->tos_addr(f->tos_add_temp("int"));
        string dest = variable; variable = "%eax"; // begin bricolage
        code += "  movl  " + rhsvar + ", " + variable + "\n";
        if (op == "*") code += "  imull " + variable + ", " + lhsvar + "\n";
        if (op == "/") code += "# idivl " + variable + ", " + lhsvar + "\n";
        if (op == "+") code += "  addl  " + variable + ", " + lhsvar + "\n";
        if (op == "-") code += "  subl  " + variable + ", " + lhsvar + "\n";
        variable = dest; // end bricolage
    }
    return pair<string,string>(code,variable);
}

CExpressionComposed::~CExpressionComposed() {
    //if (lhs != nullptr) { delete lhs; }
    //if (rhs != nullptr) { delete rhs; }
    //delete lhs;
    //delete rhs;
}

