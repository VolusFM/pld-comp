#include "CInstrArray.h"

#include <iostream>
using std::cerr;
using std::endl;

#include "CExpression.h"

void CInstrArray::explore_tos(TOS& tos) const {
    cerr << "WARNING: CInstrArray::explore_tos isn't implemented" << endl;
}

void CInstrArray::optimize() {
}

CInstrArray::CInstrArray(string name, int size)
: name(name), size(size)
{
}

CInstrArray::CInstrArray(string name, int size, list<CExpression*> exprs)
: name(name), size(size), exprs(exprs)
{
    if (exprs.size() > size) {
        cerr << "ERROR: number of inputs is superior to the array size" << endl;
        throw;
    }
}

CInstrArray::~CInstrArray() {
    for (auto expr : exprs){
        if (expr != nullptr) {
            delete expr;
        }
    }
}

