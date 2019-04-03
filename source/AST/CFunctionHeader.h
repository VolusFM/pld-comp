#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

//class CFunction;
class CParameter;

typedef string CType;

static const string registerName[] = { "rdi", "rsi", "rdx", "rcx", "r8d", "r9d" };

/**
 * FunctionHeader contains the name and the wrapper of parameters for a 
 * new function
 */
class CFunctionHeader {
public:
    // CFunctionHeader();
    CFunctionHeader(string name, vector<CParameter>& parameters);
    //~CFunctionHeader();
   
    string name;
    vector<CParameter> parameters;

public:
private:
};

class CParameter {
public:
    // CParameter();
    CParameter(string name, CType type);
    // ~CParameter();
    string to_asm(const CFunction* f, int index) const;
    CType type;
    string name;
};
