#include "IR.h"
#include "IProg.h"

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;
#include <string>
using std::to_string;

void IProg::gen_asm_x86(ostream& o) const {
    o << ".text\n"
      << ".global main\n";
    
    try {
        for (const CFG* f : functions) {
            f->gen_asm_x86(o);
        }
    } catch(...) {
        cerr << "ERROR: couldn't generate assembly code" << endl;
    }
}

string CFG::tos_get_asm_x86(string name) const {
    int index = tos_get_index(name);
    return "-" + to_string(index) + "(%rbp)";
}

void CFG::gen_asm_x86_prologue(ostream& o) const {
    o << name << ":\n"
    
      << "  ## prologue\n"
      << "  pushq %rbp # save %rbp on the stack\n"
      << "  movq %rsp, %rbp # define %rbp for the current function\n"

    /* TODO : rajouter les registres d'entrees */
    //cfg->ast->parameters
    
      << "  ## contenu\n";
}

void CFG::gen_asm_x86(ostream& o) const {
    gen_asm_x86_prologue(o);
    
    for (const BasicBlock* b : bbs) {
        b->gen_asm_x86(o);
    }
    
    gen_asm_x86_epilogue(o);
}

void CFG::gen_asm_x86_epilogue(ostream& o) const {
    o << "  ## epilogue\n"
      << "  popq %rbp # restore %rbp from the stack\n"
      << "  ret\n";
}

void BasicBlock::gen_asm_x86(ostream& o) const {
    for (auto it = instrs.begin(); it != instrs.end(); ++it) {
        (*it)->gen_asm_x86(o);
    }
}

