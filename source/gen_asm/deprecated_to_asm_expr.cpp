#include "../AST/CExpression.h"
#include "../AST/CExpressionCall.h"

#include <string>
using std::to_string;
#include <iostream>
using std::cerr;
using std::endl;

#include "../AST/CFunction.h"


string CExpressionInt::gen_asm(ostream& o, CFunction* f) const {
    string variable = f->tos.add_temp("int");
    string varaddr = f->tos.get_address_x86(variable);
    o << "  movl  $" << value << ", " << varaddr << "\n";
    return varaddr;
}

string CExpressionVar::gen_asm(ostream& o, CFunction* f) const {
    string varaddr = f->tos.get_address_x86(variable);
    return varaddr;
}

string CExpressionVarArray::gen_asm(ostream& o, CFunction* f) const {
    cerr << "PROBLEM: gen_asm unimplemented for array expressions" << endl;
    throw;
}

string CExpressionComposed::gen_asm(ostream& o, CFunction* f) const {
    string code;
    string variable;
    
    string lhsvar = lhs->gen_asm(o, f);
    string rhsvar = rhs->gen_asm(o, f);
    
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
    
    o << code; //FIXME
    return variable;
}

string CExpressionCall::gen_asm(ostream& o, CFunction* f) const {
    cerr << "PROBLEM: gen_asm unimplemented for control statements" << endl;
    throw;
}

