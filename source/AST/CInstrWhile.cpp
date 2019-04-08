#include "CInstrWhile.h"

CInstrWhile::CInstrWhile(CExpression* condition, CInstructions& blockTrue_) :
        condition(condition) {
    blockTrue = std::move(blockTrue_);
    blockTrue_.instructions.clear();
}

CInstrWhile::~CInstrWhile() {
    delete condition;
}

