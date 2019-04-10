#include "../AST/CExpression.h"
#include "../AST/CExpressionCall.h"

#include <string>
using std::to_string;
#include <iostream>
using std::cerr;
using std::endl;

#include "../AST/CFunction.h"


pair<string, string> CExpression::to_asm(const CFunction* f) const {
    return this->to_asm(const_cast<CFunction*>(f));
}

pair<string, string> CExpressionInt::to_asm(CFunction* f) const {
    string variable = f->tos.add_temp("int");
    string varaddr = f->tos.get_address_x86(variable);
    string code = "  movl  $" + to_string(value) + ", " + varaddr + "\n";
    return pair<string, string>(code, varaddr);
}

pair<string, string> CExpressionVar::to_asm(CFunction* f) const {
    string varaddr = f->tos.get_address_x86(variable);
    return pair<string, string>("", varaddr);
}

pair<string, string> CExpressionVarArray::to_asm(CFunction* f) const {
    cerr << "PROBLEM: to_asm unimplemented for array expressions" << endl;
    throw;
}

pair<string, string> CExpressionComposed::to_asm(CFunction* f) const {
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
        variable = f->tos.get_address_x86(f->tos.add_temp("int"));
        code += "  movl  " + lhsvar + ", %eax\n";
        if (op == "*") {
            code += "  imull " + rhsvar + ", %eax\n";
        }
        if (op == "/" || op == "%") {
            code += "  cltd\n"; // convert values to long double
            code += "  idivl " + rhsvar + "\n"; // do the division
        }
        if (op == "+") {
            code += "  addl " + rhsvar + ", %eax \n";
        }
        if (op == "-") {
            code += "  subl  " + rhsvar + ", %eax\n";
        }
        if (op == "<" || op == "<=" || op == ">" || op == ">=" || op == "=="
                || op == "!=") {
            code += "  cmpl  " + rhsvar + ", %eax\n";
            if (op == "<") {
                code += "  setl";
            }
            if (op == "<=") {
                code += "  setle";
            }
            if (op == ">") {
                code += "  setg";
            }
            if (op == ">=") {
                code += "  setge";
            }
            if (op == "==") {
                code += "  sete";
            }
            if (op == "!=") {
                code += "  setne";
            }
            code += "  %al\n";
            code += "  movzbl  %al, %eax\n";
        }
        if (op == "&") {
            code += "  andl  " + rhsvar + ", %eax\n";
        }
        if (op == "|") {
            code += "  orl  " + rhsvar + ", %eax\n";
        }
        if (op == "^") {
            code += "  xorl  " + rhsvar + ", %eax\n";
        }

        if (op == "%") {
            code += "  movl  %edx, ";
        } else {
            code += "  movl  %eax, ";
        }
        code += variable + "\n";
    }
    
    f->tos.free_temp(lhsvar);
    f->tos.free_temp(rhsvar);
    
    return pair<string, string>(code, variable);
}

pair<string, string> CExpressionCall::to_asm(CFunction* f) const {
    cerr << "PROBLEM: to_asm unimplemented for control statements" << endl;
    throw;
}

