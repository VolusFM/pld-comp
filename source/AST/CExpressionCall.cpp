#include "CExpressionCall.h"

CExpressionPart* CExpressionCall::optimize() {
    for (auto it = parameters.begin(); it != parameters.end(); ++it) {
        CExpressionPart* opti = (*it)->optimize();
        if (opti != nullptr) {
            delete (*it);
            (*it) = opti;
        }
    }
    
    return nullptr;
}

CExpressionCall::CExpressionCall(string name, vector<CExpressionPart*> parameters)
: functionName(name), parameters(parameters)
{
}

CExpressionCall::~CExpressionCall() {
    for (auto it = parameters.begin(); it != parameters.end(); ++it) {
        delete *it;
    }
}

