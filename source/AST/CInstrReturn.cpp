#include "CInstrReturn.h"

#include "CExpression.h"

/*
 * Default constructor - If there is no return (return void),
 * set expr to nullptr to be able to recognize it.
 */
CInstrReturn::CInstrReturn()
: expr(nullptr)
{
}

CInstrReturn::CInstrReturn(CExpression* expr)
: expr(expr)
{
}

CInstrReturn::~CInstrReturn() {
    if (expr != nullptr) {
        delete expr;
    }
}

