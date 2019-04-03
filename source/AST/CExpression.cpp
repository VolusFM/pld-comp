#include "CExpression.h"

#include <string>
using std::to_string;

#include "CFunction.h"

pair<string, string> CExpression::to_asm(const CFunction* f) const {
    return this->to_asm(const_cast<CFunction*>(f));
}

// ----------------- CExpressionInt -----------------

CExpressionInt::CExpressionInt(int value)
: value(value)
{
}

pair<string, string> CExpressionInt::to_asm(CFunction* f) const {
    string variable = f->tos_add_temp("int");
    string varaddr = f->tos_addr(variable);
    string code = "  movl  $" + to_string(value) + ", " + varaddr + "\n";
    return pair<string, string>(code, varaddr);
}

// ----------------- CExpressionVar -----------------

CExpressionVar::CExpressionVar(string variable) :
        variable(variable) {
}

pair<string, string> CExpressionVar::to_asm(CFunction* f) const {
    string ret = f->tos_addr(variable);
    return pair<string, string>("", ret);
}

// -------------- CExpressionComposed ---------------

CExpressionComposed::CExpressionComposed(CExpression* lhs, string op,
        CExpression* rhs)
: lhs(lhs), op(op), rhs(rhs)
{
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
        variable = f->tos_addr(f->tos_add_temp("int"));
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
    return pair<string, string>(code, variable);
}

CExpressionComposed::~CExpressionComposed() {
    delete lhs;
    delete rhs;
}

