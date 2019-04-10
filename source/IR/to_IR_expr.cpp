#include "IR.h"

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;
#include <string>
using std::string;
using std::to_string;

#include "../AST/CExpression.h"
#include "../AST/CExpressionCall.h"

string CExpressionInt::to_IR(CFG* cfg) const {
    /*
    BasicBlock* bb = cfg->current_bb;
    string variable = cfg->tos.add_temp(type);
    bb->add_IRInstr(op_ldconst, type, {variable, to_string(value)});
    return variable;
    */
    
    return '$' + to_string(value);
}

string CExpressionVar::to_IR(CFG* cfg) const {
    return variable;
}

string CExpressionVarArray::to_IR(CFG* cfg) const {
    BasicBlock* bb = cfg->current_bb;
    string addressIndex = index->to_IR(cfg);
    
    //FIXME find type of array
    CType type = "int";
    
    if (addressIndex.at(0) == '$')
        bb->add_IRInstr(op_index_ldconst, type, {addressIndex});
    else
        bb->add_IRInstr(op_index, type, {addressIndex});
    
    string temp = cfg->tos.add_temp(type);
    bb->add_IRInstr(op_copy_from_array, type, {temp,variable});
    
    cfg->tos.free_temp(addressIndex);
    
    return temp;
}

string CExpressionVarArray::to_IR_address(CFG* cfg) const {
    BasicBlock* bb = cfg->current_bb;
    string addressIndex = index->to_IR(cfg);
    
    //FIXME find type
    CType type = "int";
    
    if (addressIndex.at(0) == '$')
        bb->add_IRInstr(op_index_ldconst, type, {addressIndex});
    else
        bb->add_IRInstr(op_index, type, {addressIndex});
    
    cfg->tos.free_temp(addressIndex);
    return variable;
}

string CExpressionComposed::to_IR(CFG* cfg) const {
    BasicBlock* bb = cfg->current_bb;
    
    string variable;
    
    if (op == "=") {
        string lhsvar;
        
        CExpressionVarArray* vararray = dynamic_cast<CExpressionVarArray*>(lhs);
        //CExpressionCall* functionCall = dynamic_cast<CExpressionCall*>(rhs);
        
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
            else //if(functionCall==nullptr || funcType[functionCall->functionName].compare("void") == 0)
                bb->add_IRInstr(op_copy, type, {lhsvar, rhsvar});
            //else
            //    cerr << "ERROR : " << functionCall->functionName << " does not return anything";
        }
        else {
            if (rhsvar.at(0) == '$')
                bb->add_IRInstr(op_ldconst_array, type, {lhsvar, rhsvar});
            else //if(functionCall==nullptr || funcType[functionCall->functionName].compare("void") == 0)
                bb->add_IRInstr(op_copy_array, type, {lhsvar, rhsvar});
            //else
            //    cerr << "ERROR : " << functionCall->functionName << " does not return anything";
        }
        
        variable = lhsvar;
        // to do
    } else {
        string lhsvar = lhs->to_IR(cfg);
        string rhsvar = rhs->to_IR(cfg);
        
        CType type = "int"; //FIXME find type
        variable = cfg->tos.add_temp(type);
        
        vector<string> params = {variable, lhsvar, rhsvar};
        
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
            CExpressionInt* exprint = dynamic_cast<CExpressionInt*>(rhs);
            if (exprint != nullptr) {
                string var = cfg->tos.add_temp(type);
                bb->add_IRInstr(op_ldconst, type, {var, rhsvar});
                rhsvar = var;
            }
            bb->add_IRInstr(op_div, type, {variable,lhsvar,rhsvar});
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
        
        cfg->tos.free_temp(lhsvar);
        cfg->tos.free_temp(rhsvar);
    }
    // to do
    
    return variable;
}

string CExpressionCall::to_IR(CFG* cfg) const {
    BasicBlock* bb = cfg->current_bb;
    
    /*
    bool functionExist = false;
    
    // ...
    
    if (!functionExist) {
        cerr << "ERROR: reference to undefined function '" << functionName << "'" << endl;
        throw;
    }
    */
    
    //FIXME find type of called function
    CType functype = "int";
    
    string variable = cfg->tos.add_temp(functype);
    
    vector<string> results;
    
    results.push_back(functionName);
    results.push_back(variable);
    for (auto it = parameters.begin(); it != parameters.end(); ++it) {
        results.push_back((*it)->to_IR(cfg));
    }
    
    bb->add_IRInstr(op_call, functype, results);
    
    for (const string& result : results) {
        cfg->tos.free_temp(result);
    }
    
    return variable;
}

