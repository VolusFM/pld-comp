#include "CFunction.h"

#include <iostream>
using std::cerr;
using std::endl;
#include <string>
using std::to_string;

#include "CFunctionHeader.h"
#include "CInstrVariable.h"
#include "CInstrExpression.h"
#include "CExpression.h"
#include "CInstruction.h"


CFunction::CFunction(string name, vector<CParameter> parameters, CInstructions& block_)
: name(name), parameters(parameters)
{
    temp_id = 0;
    tosOffset = 0;
    
    block = std::move(block_);
    block_.instructions.clear();
}

string CFunction::to_asm() const {
    string code;
    code += name;
    
    /*
        string params = "";
        params += "(";
        for(auto it = parameters.begin(); it != parameters.end(); ++it) {
            if (!params.empty()) params += ", ";
            params += it->type;
        }
        params += ")";
        code += params;
    } */
    
    code += ":\n";

    code += "  ## prologue\n";
    code += "  pushq %rbp # save %rbp on the stack\n";
    code += "  movq %rsp, %rbp # define %rbp for the current function\n";

    int index = 0;
    for (auto it = parameters.begin() ; it!= parameters.end() ; ++it) {
        code += it->to_asm(this, index);
        index++;
    }

    code += "  ## contenu\n";

    for (const CInstruction* i : block.instructions) {
        code += i->to_asm(this);
    }

    code += "  ## epilogue\n";
    code += "  popq %rbp # restore %rbp from the stack\n";
    code += "  ret\n";

    return code;
}

void CFunction::fill_tos() {
    fill_tos(parameters);
    fill_tos(block);
    
    for (const string& i : tos) {
        //code += "  # variable " + tosType.at(i) + " " + i + "\n";
        //une fois qu'on aura d'autres tailles de variables, faudra changer ça
        tosOffset -= 4;
        tosAddress[i] = tosOffset;
    }

    // code += "sub rsp, "
    // arrondi supérieur ou égal de offset
    // pour obtenir un multiple de 16, pour appel de fonction
}

string CFunction::tos_addr(string variable) const {
    try {
        int addr = tosAddress.at(variable);
        return to_string(addr) + "(%rbp)";
    } catch(...) {
        cerr << "ERROR: reference to undeclared variable '" << variable << "'" << endl;
        throw;
    }
}

string CFunction::tos_add_temp(CType type) {
    temp_id++;
    string name = "temp" + to_string(temp_id);
    
    tos_add(name, type);
    tosOffset -= 4;
    tosAddress[name] = tosOffset;
    return name;
}

void CFunction::tos_add(string name, CType type) {
    auto it = tosType.find(name);
    if(it != tosType.end()) {
        cerr << "ERROR: already declared variable '" << name << "'" << endl;
        throw;
    }
    
    tos.push_back(name);
    tosType[name] = type;
}

void CFunction::fill_tos(const CInstructions& block) {
    for (auto it = block.instructions.begin();
              it != block.instructions.end(); ++it) {
        const CInstruction* i = *it;
        
        const CInstructions* instrlist = dynamic_cast<const CInstructions*>(i);
        if (instrlist != nullptr) fill_tos(*instrlist);
        
        const CInstrVariable* instrvar = dynamic_cast<const CInstrVariable*>(i);
        if (instrvar != nullptr) tos_add(instrvar->name, instrvar->type);
    }
}

void CFunction::fill_tos(const vector<CParameter>& parameters) {
    for(auto it = parameters.begin(); it!= parameters.end(); ++it) {
        const CParameter& param = *it;
        tos_add(param.name, param.type);
    }    
}

