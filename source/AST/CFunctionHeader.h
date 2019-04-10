#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "../CType.h"
class CFunction;
class CParameter;

class CFunctionHeader {
public:
    CFunctionHeader(string name, CType  type, vector<CParameter>& parameters);
    ~CFunctionHeader() = default;
    string to_asm(const CFunction* f) const;
    
    string name;
    CType type;
    vector<CParameter> parameters;
};

class CParameter {
public:
    CParameter(string name, CType type);
    ~CParameter() = default;
    
    string to_asm(const CFunction* f, int index) const;
    
    CType type;
    string name;
};

