#pragma once
#include <iostream>
using namespace std;
#include <string>
using std::string;
#include <vector>
using std::vector;

#include "CFunction.h"

class CProg {
public:
    string to_asm() const;

    vector<CFunction> functions;
};

