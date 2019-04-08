#include "CProg.h"

#include "CFunction.h"

void CProg::optimize() {
    for (auto it = functions.begin(); it != functions.end(); ++it) {
        (*it).optimize();
    }
}

