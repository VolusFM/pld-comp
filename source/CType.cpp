#include "CType.h"

#include <iostream>
using std::cerr;
using std::endl;

CType::CType() {
    set("");
}

CType::CType(const char* name) {
    set(name);
}

CType::CType(string name) {
    set(name);
}

void CType::set(string name)
{
    base = name;
    if (name != "" && name != "void" && name != "char" && name != "int") {
        cerr << "ERROR: unknown type '" << name << "'" << endl;
        throw;
    }
}

bool CType::has() {
    return (base != "");
}

int CType::size_z80() {
    if (base == "void") return 0;
    if (base == "char") return 1;
    if (base == "int" ) return 2;
    return -1;
}

int CType::size_x86() {
    if (base == "void") return 0;
    if (base == "char") return 1;
    if (base == "int" ) return 4;
    return -1;
}
