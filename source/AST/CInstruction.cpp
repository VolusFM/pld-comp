#include "CInstruction.h"

CInstructions::CInstructions(vector<CInstruction*>& instructions_) {
    instructions = std::move(instructions_);
}

CInstructions::~CInstructions() {
    for (auto it = instructions.begin(); it != instructions.end(); ++it) {
        delete *it;
    }
}

void CInstructions::optimize() {
    for (auto it = instructions.begin(); it != instructions.end(); ++it) {
        (*it)->optimize();
    }
}

void CInstructions::explore_tos(TOS& tos) const {
    for (auto it = instructions.cbegin(); it != instructions.cend(); ++it) {
        (*it)->explore_tos(tos);
    }
}

