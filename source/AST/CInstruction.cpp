#include "CInstruction.h"

CInstruction::~CInstruction() {
    // Nothing to do.
}

/*
string CInstruction::to_asm(const CFunction* f) const {
    string code;
    return code;
}
*/

CInstructions::CInstructions() {

}

CInstructions::CInstructions(vector<CInstruction*>& instructions_)
{
    instructions = std::move(instructions_);
}

CInstructions::~CInstructions() {
    // the following lines should be uncommented
    /* for (auto it = instructions.begin(); it != instructions.end();
                ++it) {
        delete *it;
    } */
    // uncommenting the previous lines leads to a segmentation fault
}

