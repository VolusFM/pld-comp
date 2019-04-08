#include "IProg.h"

void IProg::optimize() {
}

IProg::~IProg() {
    for (auto it = functions.begin(); it != functions.end(); ++it) {
        delete *it;
    }
}

