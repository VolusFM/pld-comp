#include <iostream>

#include "CInstrArray.h"

#include "CExpression.h"

void CInstrArray::optimize() {
}

CInstrArray::CInstrArray(string name, int size)
: name(name), size(size)
{
}

CInstrArray::CInstrArray(string name, int size, list<CExpression*> exprs)
: name(name), size(size), exprs(exprs)
{
    if(exprs.size() > size){
        std::cerr << "error : number of inputs is superior to the array size";
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

