#include "CInstruction.h"

CInstruction::~CInstruction() {
    // Nothing to do.
}

CInstructions::CInstructions() {

}

CInstructions::CInstructions(vector<CInstruction*>& instructions_)
{
    instructions = std::move(instructions_);
}

CInstructions::~CInstructions() {
    for (auto it = instructions.begin(); it != instructions.end();
                ++it) {
        delete *it;
    }
}

