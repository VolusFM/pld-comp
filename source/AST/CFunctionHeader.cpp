#include "CFunctionHeader.h"

#include "CFunction.h"

#include <iostream>

CFunctionHeader::CFunctionHeader(string name, CType type, vector<CParameter>& parameters_)
: name(name), type(type)
{
    parameters = std::move(parameters_);
    parameters_.clear();
}

CParameter::CParameter(string name, CType type)
: name(name), type(type)
{}
