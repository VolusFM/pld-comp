#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;

#include "AST/CType.h"

class TOS;

class TOS {
public:
    TOS();
    TOS(const TOS* parent);
    ~TOS() = default;
    
    const TOS* parent;
    
    
    vector<string> tos;
    map<string, CType> tosType;
    map<string, int> tosCount;
    
    void add(string name, CType type, int count = 1);
    
    
    void fill_address_x86();
    string get_address_x86(string variable) const;
    
    
    map<string, int> tosIndex;
    map<string, bool> tosUsed;
    int tosOffset;
    int tosTemps;
    
    string add_temp(CType type);
    void free_temp(string name);
    void clear_temp();
    
private:
    bool has(string name) const;
};

