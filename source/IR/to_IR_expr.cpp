#include "IR.h"

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;
#include <string>
using std::string;
using std::to_string;

#include "../AST/CExpression.h"
#include "../AST/CFunctionCall.h"


string CExpressionInt::to_IR(CFG* cfg) const {
    BasicBlock* bb = cfg->current_bb;
    
    string variable = cfg->tos_add_temp("int");
    
    bb->add_IRInstr(op_ldconst, "int", {variable, to_string(value)});
    
    return variable;
}

string CExpressionVar::to_IR(CFG* cfg) const {
    return variable;
}

string CExpressionVarArray::to_IR(CFG* cfg) const {
    //TODO : incomplete
    BasicBlock* bb = cfg->current_bb;
    string addressIndex = index->to_IR(cfg);
    int indexBase = cfg->tos_get_index(variable);

    bb->add_IRInstr(op_index, "int", {addressIndex});

    string addressWanted = "-"+to_string(indexBase)+"(%rbp,%rax,4)";
    return addressWanted;
}

string CExpressionComposed::to_IR(CFG* cfg) const {
    BasicBlock* bb = cfg->current_bb;
    
    string lhsvar = lhs->to_IR(cfg);
    string rhsvar = rhs->to_IR(cfg);
    
    string variable;
    
    if (op == "=") {
        CType type = "int"; //TODO handle other types

        // TODO check if it's a pointer

        bb->add_IRInstr(op_copy, type, {lhsvar, rhsvar});
        variable = lhsvar;
        // to do
    } else {
        variable = cfg->tos_add_temp("int");
        
        vector<string> params = {variable, lhsvar, rhsvar};
        CType type = "int"; //TODO handle other types
        
        if (op == "+") {
            bb->add_IRInstr(op_add, type, params);
        }
        if (op == "-") {
            bb->add_IRInstr(op_sub, type, params);
        }
        if (op == "*") {
            bb->add_IRInstr(op_mul, type, params);
        }
        if (op == "/") {
            bb->add_IRInstr(op_div, type, params);
        }
        if (op == "%") {
            bb->add_IRInstr(op_mod, type, params);
        }
        
        
        //   code += "  cmpl  " + rhsvar + ", %eax\n";
        if (op == "<") {
            bb->add_IRInstr(op_cmp_lt, type, params);
        }
        if (op == "<=") {
            bb->add_IRInstr(op_cmp_le, type, params);
        }
        if (op == ">") {
            bb->add_IRInstr(op_cmp_gt, type, params);
        }
        if (op == ">=") {
            bb->add_IRInstr(op_cmp_ge, type, params);
        }
        if (op == "==") {
            bb->add_IRInstr(op_cmp_eq, type, params);
        }
        if (op == "!=") {
            bb->add_IRInstr(op_cmp_ne, type, params);
        }
        //    code += "  %al\n";
        //    code += "  movzbl  %al, %eax\n";
        
        
        if (op == "!") {
            bb->add_IRInstr(op_not, type, params);
        }
        if (op == "&") {
            bb->add_IRInstr(op_binary_and, type, params);
        }
        if (op == "|") {
	    bb->add_IRInstr(op_binary_or, type, params);
        }
        if (op == "^") {
            bb->add_IRInstr(op_binary_xor, type, params);
        }
        
    }
    // to do
    
    return variable;
}

string CFunctionCall::to_IR(CFG* cfg) const{
    BasicBlock* bb = cfg->current_bb;
    
    string variable = cfg->tos_add_temp("int");
    
    vector<string> results;
    results.push_back(functionName);
    results.push_back(variable);
    for (auto it = parameters.begin(); it != parameters.end(); ++it) {
        results.push_back((*it)->to_IR(cfg));
    }
    
    bb->add_IRInstr(op_call, "int", results);
    
    return variable;
}

