#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

class CFunction;
class CParameter;

typedef string CType;

/**
 * FunctionHeader contains the name and the wrapper of parameters for a 
 * new function
 */
class CFunctionHeader {
public:
    // CFunctionHeader();
    CFunctionHeader(string name, vector<CParameter>& parameters) 
        : name(name), parameters(parameters){};
    // ~CFunctionHeader();
    string to_asm(const CFunction* f) const;
    
    string name;
    vector<CParameter> parameters;

public:
private:
};

class CParameter {
public:
    // CParameter();
    CParameter(string name, CType type) 
        : name(name), type(type){}; 
    // ~CParameter();
    CType type;
    string name;
};
