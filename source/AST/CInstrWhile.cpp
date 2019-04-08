#include "CInstrWhile.h"

CInstrWhile::CInstrWhile(CExpression* condition, CInstructions& blockContent_) :
        condition(condition) {
    blockContent = std::move(blockContent_);
    blockContent_.instructions.clear();
}

string CInstrWhile::to_asm(const CFunction* f) const {
    return nullptr; //FIXME : will have to be removed completely
}

CInstrWhile::~CInstrWhile() {
    delete condition;
}

