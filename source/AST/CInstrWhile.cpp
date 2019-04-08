#include "CInstrWhile.h"

CInstrWhile::CInstrWhile(CExpression* condition, CInstructions& blockTrue_) :
        condition(condition) {
    blockTrue = std::move(blockTrue_);
    blockTrue_.instructions.clear();
}

string CInstrWhile::to_asm(const CFunction* f) const {
    return nullptr; //FIXME : will have to be removed completely
}

CInstrWhile::~CInstrWhile() {
    delete condition;
}

