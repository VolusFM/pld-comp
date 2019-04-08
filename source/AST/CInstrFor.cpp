#include "CInstrFor.h"

CInstrFor::CInstrFor(CExpression* start, CExpression* stopCondition,
        CExpression* evolution, CInstructions& blockContent_) :
        start(start), stopCondition(stopCondition), evolution(evolution) {
    blockContent = std::move(blockContent_);
    blockContent_.instructions.clear();
}

string CInstrFor::to_asm(const CFunction* f) const {
    return nullptr; //FIXME : will have to be removed completely
}

CInstrFor::~CInstrFor() {
    delete start;
    delete stopCondition;
    delete evolution;
}
