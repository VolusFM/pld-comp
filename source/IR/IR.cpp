#include "IR.h"

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;
#include <string>
using std::string;
using std::to_string;

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
        ast(f), name(name), current_bb(nullptr), tosIndexNext(0), tosTempNext(
                1), bbNumberNext(1) {
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
    tosIndexNext += 4;
    tosIndex[name] = tosIndexNext;
}

void CFG::tos_add_array(string name, CType type, int size) {
    tos.push_back(name);
    tosType[name] = type;
    tosIndexNext += 4*size;
    tosIndex[name] = tosIndexNext;
}

string CFG::tos_add_temp(CType type) {
    string name = "!tmp" + to_string(tosTempNext++);
    tos_add(name, type);
    return this->tos_get_asm_x86(name);
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

string CFG::new_BB_name() {
    return ""; //TODO
}

