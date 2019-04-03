#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "CType.h"
class CFunction;
class CParameter;

/**
 * FunctionHeader contains the name and the wrapper of parameters for a 
 * new function
 */
class CFunctionHeader {
public:
    CFunctionHeader(string name, vector<CParameter>& parameters);
    ~CFunctionHeader() = default;
    string to_asm(const CFunction* f) const;
    
    string name;
    vector<CParameter> parameters;
};

class CParameter {
public:
    CParameter(string name, CType type);
    ~CParameter() = default;
    
    string to_asm(const CFunction* f, int index) const;
    
    string name;
    CType type;
};

