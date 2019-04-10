#include "CInstrIf.h"

void CInstrIf::explore_tos(TOS& tos) const {
    blockTrue.explore_tos(tos);
    blockFalse.explore_tos(tos);
}

void CInstrIf::optimize() {
    condition->optimize();
    blockTrue.optimize();
    blockFalse.optimize();
}

CInstrIf::CInstrIf(CExpression* condition, CInstructions& blockTrue_,
        CInstructions& blockFalse_)
: condition(condition)
{
    blockTrue = std::move(blockTrue_);
    blockTrue_.instructions.clear();
        
    blockFalse = std::move(blockFalse_);
    blockFalse_.instructions.clear();
}

CInstrIf::~CInstrIf() {
    delete condition;
}

