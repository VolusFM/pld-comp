#include "CFunctionHeader.h"

#include "CFunction.h"

CFunctionHeader::CFunctionHeader(string name, vector<CParameter>& parameters_)
: name(name)
{
    parameters = std::move(parameters_);
}

CParameter::CParameter(string name, CType type)
: name(name), type(type)
{
}

