#include "CInstrIf.h"

CInstrIf::CInstrIf(CExpression* condition, CInstructions* blockTrue,
        CInstructions* blockFalse) :
        condition(condition), blockTrue(blockTrue), blockFalse(blockFalse) {

}

string CInstrIf::to_asm(const CFunction* f) const {
    return "on verra plus tard slt";
}
