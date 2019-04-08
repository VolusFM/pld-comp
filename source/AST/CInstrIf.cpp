#include "CInstrIf.h"

void CInstrIf::optimize() {
    CExpression* opti = condition->optimize();
    if (opti != nullptr) {
        delete condition;
        condition = opti;
    }
    
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

