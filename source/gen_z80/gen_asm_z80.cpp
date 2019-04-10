#include "../AST/CProg.h"
#include "../AST/CFunction.h"
#include "../AST/CFunctionHeader.h"

#include <string>
using std::to_string;
#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;


void CProg::gen_asm_z80(ostream& o) const {
    o << ".text\n";
    o << ".global main\n";
    
    try {
        for (const CFunction& f : functions) {
            TOS* tos = const_cast<TOS*>(&f.tos);
            tos->fill_address_x86();
            f.gen_asm_z80(o);
            tos->clear_temp();
        }
    } catch (...) {
        cerr << "ERROR: couldn't generate assembly code" << endl;
    }
}

void CParameter::gen_asm_z80(ostream& o, const CFunction* f, int index) const {
    static const string registerName[] = { "%edi", "%esi", "%edx", "%ecx", "%e8d", "%e9d" };
    
    string variable = f->tos.get_address_x86(name);
    
    o << "  movl " << registerName[index] << ", " << variable << "\n";
}

void CFunction::gen_asm_z80(ostream& o) const {
    o << name;
    
    /*
        string params = "";
        params += "(";
        for(auto it = parameters.begin(); it != parameters.end(); ++it) {
            if (!params.empty()) params += ", ";
            params += it->type;
        }
        params += ")";
        code += params;
    */
    
    o << ":\n";
    
    o << "  ## prologue\n";
    o << "  pushq %rbp # save %rbp on the stack\n";
    o << "  movq %rsp, %rbp # define %rbp for the current function\n";
    
    int index = 0;
    for (auto it = parameters.cbegin() ; it != parameters.cend() ; ++it) {
        it->gen_asm_z80(o, this, index);
        index++;
    }
    
    o << "  ## contenu\n";
    
    for (const CInstruction* it : block.instructions) {
        it->gen_asm_z80(o, this);
    }
    
    o << "  ## epilogue\n";
    o << "  popq %rbp # restore %rbp from the stack\n";
    o << "  ret\n";
}

