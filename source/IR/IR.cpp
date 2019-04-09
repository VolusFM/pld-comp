#include "IR.h"

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;
#include <string>
using std::string;
using std::to_string;

#include <utility>
using std::swap;

IRInstr::IRInstr(BasicBlock* bb, Operation op, CType type,
        vector<string> params) :
        bb(bb), op(op), type(type), params(params) {
}

BasicBlock::BasicBlock(CFG* cfg, string name) :
        exit_true(nullptr), exit_false(nullptr), label(name), cfg(cfg) {
}

BasicBlock::~BasicBlock() {
    for (auto it = instrs.begin(); it != instrs.end(); ++it) {
        delete *it;
    }
}

void BasicBlock::add_IRInstr(Operation op, string type, vector<string> params) {
    IRInstr* instr = new IRInstr(this, op, type, params);
    instrs.push_back(instr);
}

CFG::CFG(const CFunction* f, string name) :
        ast(f), name(name), current_bb(nullptr), tosIndexLast(0), tosTempLast(
                0), bbNumberLast(0) {
}

CFG::~CFG() {
    for (auto it = bbs.begin(); it != bbs.end(); ++it) {
        delete *it;
    }
}

void CFG::add_bb(BasicBlock* bb) {
    bbs.push_back(bb);
    current_bb = bb;
}

void CFG::tos_add(string name, CType type) {
    tos.push_back(name);
    tosType[name] = type;
    tosIndexLast += 4;
    tosIndex[name] = tosIndexLast;
}

void CFG::tos_add_array(string name, CType type, int size) {
    tos.push_back(name);
    tosType[name] = type;
    tosIndexLast += 4*size;
    tosIndex[name] = tosIndexLast;
}

string CFG::tos_add_temp(CType type) {
    for (auto it = tosUsed.begin(); it != tosUsed.end(); ++it) {
        if (!it->second) {
            string name = it->first;
            if (tosType[name] == type) {
                tosUsed[name] = true;
                return name;
            }
        }
    }
    
    string name = "!tmp" + to_string(++tosTempLast);
    tos_add(name, type);
    tosUsed[name] = true;
    return name;
}

void CFG::tos_free_temp(string name) {
    // if (name.at(0) != '!') return;
    auto it = tosUsed.find(name);
    if (it != tosUsed.end()) (*it).second = false;
}

int CFG::tos_get_index(string variable) const {
    try {
        return tosIndex.at(variable);
    } catch (...) {
        cerr << "ERROR: reference to undeclared variable '" << variable << "'"
                << endl;
        throw;
    }
}

CType CFG::tos_get_type(string variable) const {
    try {
        return tosType.at(variable);
    } catch (...) {
        cerr << "ERROR: reference to undeclared variable '" << variable << "'"
                << endl;
        throw;
    }
}

string CFG::new_BB_name(const string& prefix) {
    return name + "_" + prefix + to_string(++bbNumberLast);
}

void CFG::optimize() {
    if (bbs.size() == 0) return;
    
    // replace empty bbs
    
    map<BasicBlock*, BasicBlock*> bbReplace;
    
    for (auto it = bbs.begin(); it != bbs.end(); ++it) {
        BasicBlock* b = (*it);
        if (b->instrs.empty()) {
            bbReplace[b] = b->exit_true;
        }
    }
    
    bool evolves = true;
    while (evolves) {
        evolves = false;
        
        for (auto it = bbReplace.begin(); it != bbReplace.end(); ++it) {
            auto itr = bbReplace.find(it->second);
            if (itr != bbReplace.end() && itr->second != it->second) {
                bbReplace[it->first] = itr->second;
                evolves = true;
            }
        }
    }
    
    for (auto itr = bbReplace.begin(); itr != bbReplace.end(); ++itr) {
        for (auto it = bbs.begin(); it != bbs.end(); ++it) {
            BasicBlock* b = (*it);
            if (b->exit_false != nullptr && itr->second == nullptr) continue;
            if (b->exit_true == itr->first) b->exit_true = itr->second;
            if (b->exit_false == itr->first) b->exit_false = itr->second;
        }
    }
    
    // remove unused bbs
    
    map<BasicBlock*, bool> bbUsed;
    bbUsed[bbs[0]] = true;
    
    bool changed = true;
    while (changed) {
        changed = false;
        
        for (auto it = bbs.begin(); it != bbs.end(); ++it) {
            BasicBlock* b = (*it);
            if (bbUsed[b]) {
                if (!bbUsed[b->exit_true]) changed = true;
                if (!bbUsed[b->exit_false]) changed = true;
                bbUsed[b->exit_true] = true;
                bbUsed[b->exit_false] = true;
            }
        }
    }
    
    for (auto it = bbs.begin(); it != bbs.end(); /*rien*/) {
        if (!bbUsed[*it]) {
            delete (*it);
            it = bbs.erase(it);
        } else {
            ++it;
        }
    }
    
    // move empty bbs at the back
    
    vector<BasicBlock*> bbsmoved;
    bool moved = false;
    
    bbsmoved.reserve(bbs.size());
    for (auto it = bbs.begin(); it != bbs.end(); ++it) {
        if (!(*it)->instrs.empty()) {
            bbsmoved.push_back(*it);
        }
    }
    for (auto it = bbs.begin(); it != bbs.end(); ++it) {
        if ((*it)->instrs.empty()) {
            bbsmoved.push_back(*it);
            moved = true;
        }
    }
    
    if (moved) std::swap(bbs, bbsmoved);
    
}

