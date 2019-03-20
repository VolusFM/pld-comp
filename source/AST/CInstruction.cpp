#include "CInstruction.h"

CInstruction::~CInstruction() {
    // Nothing to do.
}

string CInstruction::to_asm() const {
    string code;
    return code;
}

CInstructions::CInstructions() {

}

CInstructions::CInstructions(vector<CInstruction *> instructions) :
        instructions(instructions) {
}

CInstructions::~CInstructions() {
    for (auto it = instructions.begin(); it != instructions.end();
                ++it) {
        delete *it;
    }
}
