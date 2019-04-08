#include "IR.h"

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;
using std::to_string;

#include "../AST/CExpression.h"
#include "../AST/CInstruction.h"
#include "../AST/CInstrExpression.h"
#include "../AST/CInstrVariable.h"
#include "../AST/CInstrReturn.h"
#include "../AST/CInstrArray.h"
#include "../AST/CInstrIf.h"
#include "../AST/CInstrWhile.h"
#include "../AST/CInstrFor.h"

void CInstructions::to_IR(CFG* cfg) const {
    for (auto it = instructions.begin(); it != instructions.end(); ++it) {
        (*it)->to_IR(cfg);
    }
}

void CInstrExpression::to_IR(CFG* cfg) const {
    expr->to_IR(cfg);
}

void CInstrArray::to_IR(CFG* cfg) const {
    if (exprs.size() <= size) {
        BasicBlock* bb = cfg->current_bb;

        int index;

        cfg->tos_add_array(name, type, size);
        int address = cfg->tos_get_index(name);

        if (exprs.size() != size && exprs.size() != 0) {
            for (index = 0; index < size; index++) {
                bb->add_IRInstr(op_ldconst_mem, type,
                        { to_string(address - 4 * index), "0" });
            }
        }

        index = 0;
        for (auto expr : exprs) {
            if (dynamic_cast<CExpressionInt*>(expr) != NULL) {
                bb->add_IRInstr(op_ldconst_mem, type,
                        { to_string(address - 4 * index), to_string(
                                dynamic_cast<CExpressionInt*>(expr)->value) });
            } else {
                string temp = expr->to_IR(cfg);
                bb->add_IRInstr(op_copy_mem, type,
                        { to_string(address - 4 * index), temp });
            }
            index++;
        }
    } else {
        cerr
                << "ERROR: too many initializers for '" + type + "["
                        + to_string(size) + "]'" << endl;
        throw;
    }
}

void CInstrVariable::to_IR(CFG* cfg) const {
    if (expr != nullptr)
        expr->to_IR(cfg);
}

void CInstrReturn::to_IR(CFG* cfg) const {
    if (expr != nullptr)
        expr->to_IR(cfg);

    // to do
}

void CInstrIf::to_IR(CFG* cfg) const {
    BasicBlock* bb = cfg->current_bb;

    // Create new blocks for if statement
    BasicBlock* bbNext = new BasicBlock(cfg, cfg->new_BB_name());
    BasicBlock* bbTrue = new BasicBlock(cfg, cfg->new_BB_name());
    BasicBlock* bbFalse =
            blockFalse.instructions.empty() ?
                    nullptr : new BasicBlock(cfg, cfg->new_BB_name());

    // Add condition to the cfg
    condition->to_IR(cfg);

    // Link current block to the contents of the if
    bb->exit_true = bbTrue;
    bb->exit_false = bbFalse ? bbFalse : bbNext;

    // Prepare the exit_true and link it to the next block
    cfg->current_bb = bbTrue;
    blockTrue.to_IR(cfg);
    bbTrue->exit_true = bbNext;
    cfg->add_bb(bbTrue);

    if (bbFalse != nullptr) { // If there is an exit_false, prepare it as well
        cfg->current_bb = bbFalse;
        blockFalse.to_IR(cfg);
        bbFalse->exit_true = bbNext;
        cfg->add_bb(bbFalse);
    }

    // Add next block to CFG
    cfg->current_bb = bbNext;
    cfg->add_bb(bbNext);
}

void CInstrWhile::to_IR(CFG* cfg) const {
    BasicBlock* bb = cfg->current_bb;

    // Create new blocks for while statement
    BasicBlock* bbNext = new BasicBlock(cfg, cfg->new_BB_name());
    BasicBlock* bbContent = new BasicBlock(cfg, cfg->new_BB_name());

    // Add condition to the cfg
    condition->to_IR(cfg);

    // Link current block to the contents of the while
    bb->exit_true = bbContent;
    bb->exit_false = bbNext;

    // Prepare the exit_true and exit_false and link them to the next block
    cfg->current_bb = bbContent;
    blockContent.to_IR(cfg);
    bbContent->exit_true = bbContent;
    bbContent->exit_false = bbNext;
    cfg->add_bb(bbContent);

    // Add next block to CFG
    cfg->current_bb = bbNext;
    cfg->add_bb(bbNext);
}

void CInstrFor::to_IR(CFG* cfg) const {
    // TODO
}
