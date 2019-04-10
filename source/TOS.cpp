#include "TOS.h"

#include <iostream>
using std::cerr;
using std::endl;
#include <string>
using std::to_string;


TOS::TOS(const TOS* parent)
: parent(parent)
{
}

TOS::TOS()
: parent(nullptr)
{
}


bool TOS::has(string name) const {
    return (tosType.find(name) != tosType.end());
}

void TOS::add(string name, CType type, int count) {
    cerr << "TOS.add(" << name << ")" << endl; //FIXME
    
    if (has(name)) {
        cerr << "ERROR: already declared variable '" << name << "'" << endl;
        throw;
    }
    
    tos.push_back(name);
    tosType[name] = type;
    tosCount[name] = 1;
}

string TOS::add_temp(CType type) {
    for (auto it = tosUsed.begin(); it != tosUsed.end(); ++it) {
        if (!it->second) {
            string name = it->first;
            if (tosType[name] == type) {
                tosUsed[name] = true;
                return name;
            }
        }
    }
    
    string name = "temp" + to_string(++tosTemps);
    
    add(name, type);
    tosOffset += 4; //FIXME
    tosIndex[name] = tosOffset;
    tosUsed[name] = true;
    return name;
}

void TOS::free_temp(string name) {
    // if (name.at(0) != '!') return;
    auto it = tosUsed.find(name);
    if (it != tosUsed.end()) (*it).second = false;
}

void TOS::clear_temp() {
    for (auto it = tos.begin(); it != tos.end(); /*rien*/) {
        const string name = (*it);
        if (name.at(0) == '!') {
            tosType.erase(name);
            tosCount.erase(name);
            it = tos.erase(it);
        } else {
            ++it;
        }
    }
    
    tosIndex.clear();
    tosUsed.clear();
    tosOffset = 0;
    tosTemps = 0;
}


void TOS::fill_address_x86() {
    tosOffset = 0;
    
    for (const string& name : tos) {
        tosOffset += 4; //FIXME
        tosIndex[name] = tosOffset;
    }
}

string TOS::get_address_x86(string variable) const {
    if (has(variable)) {
        int addr = -tosIndex.at(variable);
        return to_string(addr) + "(%rbp)";
    } else if (parent != nullptr) {
        return parent->get_address_x86(variable);
    } else {
        cerr << "ERROR: reference to undeclared variable '" << variable << "'" << endl;
        throw;
    }
}

