#include "CExpressionCall.h"

#include <string>
using std::to_string;

CExpressionCall::CExpressionCall(string name, vector<CExpression*> parameters)
: functionName(name), parameters(parameters)
{
}

CExpressionCall::~CExpressionCall() {
    for (auto it = parameters.begin(); it != parameters.end(); ++it) {
        delete *it;
    }
}

