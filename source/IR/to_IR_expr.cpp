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
    //BasicBlock* bb = cfg->current_bb;
    
    //string variable = cfg->tos_add_temp("int");
    
    //bb->add_IRInstr(op_ldconst, "int", {variable, to_string(value)});
    
    return '$'+to_string(value);
}

string CExpressionVar::to_IR(CFG* cfg) const {
    return variable;
}

string CExpressionVarArray::to_IR(CFG* cfg) const {
    //TODO : incomplete

    BasicBlock* bb = cfg->current_bb;
    string addressIndex = index->to_IR(cfg);
    
    string temp = cfg->tos_add_temp("int");
    
    if (addressIndex.at(0) == '$')
        bb->add_IRInstr(op_index_ldconst, "int", {addressIndex});
    else
        bb->add_IRInstr(op_index, "int", {addressIndex});
    bb->add_IRInstr(op_copy_from_array, "int", {temp,variable});
    
    return temp;
}

string CExpressionVarArray::to_IR_address(CFG* cfg) const {
    BasicBlock* bb = cfg->current_bb;
    string addressIndex = index->to_IR(cfg);
    
    if (addressIndex.at(0) == '$')
        bb->add_IRInstr(op_index_ldconst, "int", {addressIndex});
    else
        bb->add_IRInstr(op_index, "int", {addressIndex});
    
    return variable;
}

string CExpressionComposed::to_IR(CFG* cfg) const {
    BasicBlock* bb = cfg->current_bb;

    string variable;

    if (op == "=") {
        string lhsvar;

        CExpressionVarArray* vararray = dynamic_cast<CExpressionVarArray*>(lhs);
        if (vararray == nullptr)
            lhsvar = lhs->to_IR(cfg);
        else
            lhsvar = vararray->to_IR_address(cfg);
        string rhsvar = rhs->to_IR(cfg);

        CType type = "int"; //TODO handle other types

        // TODO check if it's a pointer

        if (vararray == nullptr){
            if (rhsvar.at(0) == '$')
                bb->add_IRInstr(op_ldconst, type, {lhsvar, rhsvar});
            else
                bb->add_IRInstr(op_copy, type, {lhsvar, rhsvar});
        }
        else {
            if (rhsvar.at(0) == '$')
                bb->add_IRInstr(op_ldconst_array, type, {lhsvar, rhsvar});
            else
                bb->add_IRInstr(op_copy_array, type, {lhsvar, rhsvar});
        }

        variable = lhsvar;
        // to do
    } else {
        string lhsvar = lhs->to_IR(cfg);
        string rhsvar = rhs->to_IR(cfg);

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
        
        cfg->tos_free_temp(lhsvar);
        cfg->tos_free_temp(rhsvar);
    }
    // to do

    return variable;
}

string CFunctionCall::to_IR(CFG* cfg) const {
    BasicBlock* bb = cfg->current_bb;

    string variable = cfg->tos_add_temp("int");

    vector < string > results;
    results.push_back(functionName);
    results.push_back(variable);
    for (auto it = parameters.begin(); it != parameters.end(); ++it) {
        results.push_back((*it)->to_IR(cfg));
    }

    bb->add_IRInstr(op_call, "int", results);

    return variable;
}

