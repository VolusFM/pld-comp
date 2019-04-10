#include "CInstrDoWhile.h"

void CInstrDoWhile::explore_tos(TOS& tos) const {
    blockContent.explore_tos(tos);
}

void CInstrDoWhile::optimize() {
    blockContent.optimize();
    
    CExpression* opti = condition->optimize();
    if (opti != nullptr) {
        delete condition;
        condition = opti;
    }
}

CInstrDoWhile::CInstrDoWhile(CExpression* condition, CInstructions& blockContent_) :
        condition(condition) {
    blockContent = std::move(blockContent_);
    blockContent_.instructions.clear();
}

CInstrDoWhile::~CInstrDoWhile() {
    delete condition;
}

