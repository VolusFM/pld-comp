#include "../AST/CProg.h"
#include "IProg.h"

#include "../AST/CFunction.h"
#include "IR.h"

IProg* CProg::to_IR() const {
    IProg* ir = new IProg();
    
    for (const CFunction& f : functions) {
        ir->functions.push_back(f.to_IR());
    }
    
    return ir;
}

CFG* CFunction::to_IR() const {
    CFG* cfg = new CFG(this, name);
    
    //TODO can be improved
    cfg->tos = tos.tos;
    cfg->tosType = tos.tosType;
    cfg->tosIndex = tos.tosIndex;
    cfg->tosIndexLast = tos.tosOffset;
    
    BasicBlock* bb = new BasicBlock(cfg, name + "_body");
    bb->exit_true = nullptr;
    bb->exit_false = nullptr;
    
    cfg->add_bb(bb);
    
    for (const CInstruction* instr : block.instructions) {
        instr->to_IR(cfg);
    }
    
    return cfg;
}

