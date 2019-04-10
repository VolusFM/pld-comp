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
}

CInstrArray::CInstrArray(string name, CType type, int count)
: name(name), type(type), count(count)
{
}

CInstrArray::CInstrArray(string name, CType type, int count, list<CExpression*> exprs)
: name(name), type(type), count(count), exprs(exprs)
{
    if (exprs.size() > count) {
        cerr << "ERROR: array '" << name << "' initalized with too many items" << endl;
        throw;
    }
}

CInstrArray::~CInstrArray() {
    for (CExpression* expr : exprs){
        delete expr;
    }
}

