#include "CInstrWhile.h"

void CInstrWhile::optimize() {
    blockContent.optimize();
    
    CExpression* opti = condition->optimize();
    if (opti != nullptr) {
        delete condition;
        condition = opti;
    }
}

CInstrWhile::CInstrWhile(CExpression* condition, CInstructions& blockContent_) :
        condition(condition) {
    blockContent = std::move(blockContent_);
    blockContent_.instructions.clear();
}

CInstrWhile::~CInstrWhile() {
    delete condition;
}

