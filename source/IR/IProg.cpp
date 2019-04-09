#include "IProg.h"

void IProg::optimize() {
    for (auto it = functions.begin(); it != functions.end(); ++it) {
        (*it)->optimize();
    }
}

IProg::~IProg() {
    for (auto it = functions.begin(); it != functions.end(); ++it) {
        delete *it;
    }
}

