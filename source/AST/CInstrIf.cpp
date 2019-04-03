#include "CInstrIf.h"

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

