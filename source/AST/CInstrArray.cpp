#include "CInstrArray.h"

#include <iostream>
using std::cerr;
using std::endl;

#include "../TOS.h"
#include "CExpression.h"

void CInstrArray::explore_tos(TOS& tos) const {
    tos.add(name, type, count);
}

void CInstrArray::optimize() {
    for (auto it = exprs.begin(); it != exprs.end(); ++it) {
        CExpressionPart* opti = (*it)->optimize();
        if (opti != nullptr) {
            delete (*it);
            (*it) = opti;
        }
    }
}

CInstrArray::CInstrArray(string name, CType type, int count)
: name(name), type(type), count(count)
{
}

CInstrArray::CInstrArray(string name, CType type, int count, list<CExpressionPart*> exprs)
: name(name), type(type), count(count), exprs(exprs)
{
    if (exprs.size() > count) {
        cerr << "ERROR: array '" << name << "' initalized with too many items" << endl;
        throw;
    }
}

CInstrArray::~CInstrArray() {
    for (CExpressionPart* expr : exprs){
        delete expr;
    }
}

