#include "CFunctionCall.h"

#include <string>
using std::to_string;


CFunctionCall::CFunctionCall(string name, vector<CExpression*> parameters)
        : functionName(name), parameters(parameters) {}

CFunctionCall::~CFunctionCall() {
    for (auto it = parameters.begin(); it != parameters.end(); ++it) {
        delete *it;
    }
}

pair<string, string> CFunctionCall::to_asm(CFunction* f) const {
    return pair<string, string>("","");
}

