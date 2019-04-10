#include "../AST/CProg.h"
#include "IProg.h"

#include "../AST/CFunction.h"
#include "IR.h"

IProg* CProg::to_IR() const {
    IProg* ir = new IProg();
    
    ir->tos = tos;
    for (const CFunction& f : functions) {
        CFG* cfg = f.to_IR();
        cfg->tos.parent = &ir->tos;
        ir->functions.push_back(cfg);
    }
    
    return ir;
}

CFG* CFunction::to_IR() const {
    CFG* cfg = new CFG(this, name);
    
    cfg->tos = tos;
    cfg->tos.parent = nullptr;
    
    BasicBlock* bb = new BasicBlock(cfg, name + "_body");
    bb->exit_true = nullptr;
    bb->exit_false = nullptr;
    
    cfg->add_bb(bb);
    
    for (const CInstruction* instr : block.instructions) {
        instr->to_IR(cfg);
    }
    
    return cfg;
}

