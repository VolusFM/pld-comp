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
    if (name.at(0) == '$')
        return name;
    int index = tos_get_index(name);
    return "-" + to_string(index) + "(%rbp)";
}

string CFG::tos_get_asm_x86_array(string name) const {
    int index = tos_get_index(name);
    return "-" + to_string(index) + "(%rbp,%rax,4)";
}

void CFG::gen_asm_x86_prologue(ostream& o) const {
    o << name << ":\n"
    
      << "  ## prologue\n"
      << "  pushq %rbp # save %rbp on the stack\n"
      << "  movq %rsp, %rbp # define %rbp for the current function\n";
    
    // TODO : adapt for different types (size has to change)
    int rspshift = (1+(int)(4*(ast->tosAddress).size()/16))*16;
    if (rspshift != 0) {
        o << "  subq $" << rspshift << ", %rsp\n";
    }
    
    int index = 0;
    for (auto it = ast->parameters.cbegin(); it != ast->parameters.cend() ; ++it) {
        o << "  movq " << registerName[index++] << ", " << ast->tos_addr(it->name) << "\n";
    }
    
    o << "  ## contenu\n";
}

void CFG::gen_asm_x86(ostream& o) const {
    gen_asm_x86_prologue(o);
    
    // merge all basic blocks at the end that are empty and terminating
    
    auto nullbbs = bbs.cbegin();
    for (auto it = bbs.cbegin(); it != bbs.cend(); ++it) {
	    const BasicBlock* b = (*it);
        if (b->exit_true != nullptr || b->exit_false != nullptr || !b->instrs.empty()) {
            nullbbs = it+1;
        }
    }
    
    // remove unnecessary basic block jumps
    
	for (auto it = bbs.cbegin(); it != nullbbs; ++it) {
	    const BasicBlock* b = (*it);
        
	    auto itn = it+1;
	    const BasicBlock* bn = nullptr;
	    if (itn != bbs.cend() && !(*it)->instrs.empty()) bn = (*itn);
	    
        // generate basic block code and necessary jumps
        
        b->gen_asm_x86(o);
        
        if (b->exit_false != nullptr) {
            o << "  cmpl $0, %eax" << "\n";
            o << "  je " << b->exit_false->label << "\n";
        }
        if (b->exit_true != nullptr) {
            if (bn != b->exit_true)
            o << "  jmp " << b->exit_true->label << "\n";
        }
        if (b->exit_true == nullptr && b->exit_false == nullptr) {
            if (itn != nullbbs)
            o << "  jmp " << name << "_end\n";
        }
	}
    
    for (auto it = nullbbs; it != bbs.cend(); ++it) {
        o << (*it)->label << ":\n";
    }
    
    gen_asm_x86_epilogue(o);
}

void CFG::gen_asm_x86_epilogue(ostream& o) const {
    o << name << "_end:\n"
      << "  ## epilogue\n"
      << "  leave\n"
      << "  ret\n";
}

void BasicBlock::gen_asm_x86(ostream& o) const {
    o << label << ":\n";
    
    for (auto it = instrs.cbegin(); it != instrs.cend(); ++it) {
        (*it)->gen_asm_x86(o);
    }
}

