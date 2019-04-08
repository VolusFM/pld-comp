#include "CInstrDoWhile.h"

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

string CInstrDoWhile::to_asm(const CFunction* f) const {
    return nullptr; //FIXME : will have to be removed completely
}

CInstrDoWhile::~CInstrDoWhile() {
    delete condition;
}

