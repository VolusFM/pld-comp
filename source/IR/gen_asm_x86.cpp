#include "IR.h"
#include "IProg.h"

#include "../AST/CFunction.h"
#include "../AST/CInstruction.h"
#include "../AST/CExpression.h"

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;
#include <string>
using std::to_string;

void IProg::gen_asm_x86(ostream& o) const {
    o << ".text\n" << ".global main\n";

    try {
        for (const CFG* f : functions) {
            f->gen_asm_x86(o);
        }
    } catch (...) {
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
      
      /* TODO : adapt for different types (size has to change) */
      << "  subq $" << to_string((1+(int)(4*(ast->tosAddress).size()/16))*16) << ", %rsp\n";

    int index = 0;
    for (auto it = ast->parameters.cbegin(); it != ast->parameters.cend() ; ++it) {
        o << "  movl : " << registerName[index++] << ", " << ast->tos_addr(it->name) << "\n";
    }
    
    o << "  ## contenu\n";
}

void CFG::gen_asm_x86(ostream& o) const {

    gen_asm_x86_prologue(o);

    for (const BasicBlock* b : bbs) {
        b->gen_asm_x86(o);
    }

    gen_asm_x86_epilogue(o);
}

void CFG::gen_asm_x86_epilogue(ostream& o) const {
    o << "  ## epilogue\n" << "  popq %rbp # restore %rbp from the stack\n"
            << "  ret\n";
}

void BasicBlock::gen_asm_x86(ostream& o) const {
    o << label << ":\n";

    for (auto it = instrs.begin(); it != instrs.end(); ++it) {
        (*it)->gen_asm_x86(o);
    }

    if (exit_false == nullptr) {
        if (exit_true != nullptr) {
            o << "  jmp " << exit_true->label << "\n";
        }
    } else if (exit_true != nullptr) {
        // FIXME %eax could be not hardcoded
        o << "  cmpl $0, %eax" << "\n";
        o << "  jne " << exit_true->label << "\n";
        o << "  jmp " << exit_false->label << "\n";
    }

}

