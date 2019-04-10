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
: prog(prog), name(name), type(type), tos(prog != nullptr ? &prog->tos : nullptr)
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
    
    block.explore_tos(tos);
}

void CFunction::optimize() {
    block.optimize();
}

