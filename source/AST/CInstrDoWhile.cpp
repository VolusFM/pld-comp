#include "CInstrDoWhile.h"

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

