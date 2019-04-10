#include "CFunction.h"

#include <iostream>
using std::cerr;
using std::endl;
#include <string>
using std::to_string;

#include "CFunctionHeader.h"
#include "CInstrVariable.h"
#include "CInstrExpression.h"
#include "CExpression.h"
#include "CInstruction.h"
#include "CProg.h"


CFunction::CFunction(const CProg* prog, string name, CType type, vector<CParameter>& parameters_, CInstructions& block_)
: prog(prog), name(name), tos(prog != nullptr ? &prog->tos : nullptr)
{
    parameters = std::move(parameters_);
    parameters_.clear();
    
    block = std::move(block_);
    block_.instructions.clear();
}

void CFunction::explore_tos() {
    for (auto it = parameters.cbegin(); it != parameters.cend(); ++it) {
        const CParameter& param = *it;
        tos.add(param.name, param.type);
    }
    
    block_explore_tos(tos);
}

void CFunction::block_explore_tos(TOS& tos) {
    for (auto it = block.instructions.cbegin();
              it != block.instructions.cend(); ++it) {
        const CInstruction* i = *it;
        
        // FIXME
        // const CInstructions* instrlist = dynamic_cast<const CInstructions*>(i);
        // if (instrlist != nullptr) fill_tos(*instrlist);
        
        // FIXME
        const CInstrVariable* instrvar = dynamic_cast<const CInstrVariable*>(i);
        if (instrvar != nullptr) tos.add(instrvar->name, instrvar->type);
    }
}

void CFunction::optimize() {
    block.optimize();
}

