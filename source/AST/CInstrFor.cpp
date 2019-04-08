#include "CInstrFor.h"

void CInstrFor::optimize() {
    blockContent.optimize();
    
    CExpression* opti;
    
    if (start != nullptr) {
        opti = start->optimize();
        if (opti != nullptr) {
            delete start;
            start = opti;
        }
    }
    
    if (stopCondition != nullptr) {
        opti = stopCondition->optimize();
        if (opti != nullptr) {
            delete stopCondition;
            stopCondition = opti;
        }
    }
    
    if (evolution != nullptr) {
        opti = evolution->optimize();
        if (opti != nullptr) {
            delete evolution;
            evolution = opti;
        }
    }
}

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
