#include "IProg.h"

IProg::~IProg() {
    for (auto it = functions.begin(); it != functions.end(); ++it) {
        delete *it;
    }
}

