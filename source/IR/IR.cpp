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

IRInstr::IRInstr(BasicBlock* bb, Operation op, CType type, vector<string> params)
: bb(bb), op(op), type(type), params(params)
{
}

BasicBlock::BasicBlock(CFG* cfg, string name)
: exit_true(nullptr), exit_false(nullptr), label(name), cfg(cfg)
{
}

BasicBlock::~BasicBlock() {
    for (auto it = instrs.begin(); it != instrs.end(); ++it) {
        delete *it;
    }
}

void BasicBlock::add_IRInstr(Operation op, const CType& type, vector<string> params) {
    IRInstr* instr = new IRInstr(this, op, type, params);
    instrs.push_back(instr);
}

CFG::CFG(const CFunction* f, string name)
: ast(f), name(name), current_bb(nullptr), bbNumberLast(0)
{
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

string CFG::new_BB_name(const string& prefix) {
    return name + "_" + prefix + to_string(++bbNumberLast);
}

void CFG::optimize() {
    if (bbs.size() == 0) return;
    
    // replace empty bbs
    
    map<BasicBlock*, BasicBlock*> bbReplace;
    
    for (auto it = bbs.begin(); it != bbs.end(); ++it) {
        BasicBlock* b = (*it);
        if (b->instrs.empty() && b->exit_false == nullptr) {
            bbReplace[b] = b->exit_true;
        }
    }
    
    bool evolves = true;
    while (evolves) {
        evolves = false;
        
        for (auto itr = bbReplace.begin(); itr != bbReplace.end(); ++itr) {
            if (itr->first != itr->second) {
                for (auto it = bbs.begin(); it != bbs.end(); ++it) {
                    BasicBlock* b = (*it);
                    if (b->exit_false != nullptr && itr->second == nullptr) continue;
                    if (b->exit_true == itr->first) {
                        b->exit_true = itr->second;
                        evolves = true;
                    }
                    if (b->exit_false == itr->first) {
                        b->exit_false = itr->second;
                        evolves = true;
                    }
                }
            }
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

