#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;

#include "CType.h"
#include "CInstruction.h"
class CParameter;

class CFG;

class CFunction {
public:
    CFunction(string name, vector<CParameter>& parameters, CInstructions& block);
    ~CFunction() = default;
    
    CFG* to_IR() const;
    string to_asm() const;
    
    string name;
    
    vector<string> tos;
    map<string, CType> tosType;
    map<string, int> tosAddress;
    int tosOffset;
    
    vector<CParameter> parameters;
    CInstructions block;
    
    int temp_id;
    string tos_add_temp(CType type);
    string tos_addr(string variable) const;
    void tos_add(CType type, string name);
    
    void fill_tos();
private:
    void fill_tos(const CInstructions& block);
    void fill_tos(const vector<CParameter>& parameters);
    
public:
    // enable move semantics
    CFunction(CFunction&&) = default;
    CFunction& operator=(CFunction&&) = default;
};

