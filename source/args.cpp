#include "args.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <cstring>

inline bool strequal(const char* str1, const char* str2) {
    return strcmp(str1, str2) == 0;
}

bool argsparse(int argc, const char* argv[], arguments& args) {
    args.fi.clear();
    args.fo.clear();
    args.opta = false;
    args.opto = false;
    args.optc = false;

    // temporary
    args.tmp = false;

    for (int i = 1; i < argc; ++i) {
        const char* arg = argv[i];
        const char* val;

        if (*arg == '-') {
            arg++;

            if (strequal(arg, "a"))
                args.opta = true;
            else if (strequal(arg, "o"))
                args.opto = true;
            else if (strequal(arg, "c"))
                args.optc = true;

            // temporary
            else if (strequal(arg, "-AST"))
                args.tmp = true;
            else if (strequal(arg, "-IR"))
                args.tmp = false;

            else {
                cerr << "ERROR: unknown argument : '" << arg << "'." << endl;
                return false;
            }
        } else {
            if (args.fi.empty())
                args.fi = arg;
            else if (args.fo.empty())
                args.fo = arg;
            else {
                cerr << "ERROR: too many arguments." << endl;
                return false;
            }
        }
    }

    if (args.fi.empty()) {
        cerr << "ERROR: missing file input argument." << endl;
        return false;
    }

    if (!args.optc && !args.fo.empty()) {
        cerr << "ERROR: too many arguments." << endl;
        return false;
    }

    return true;
}
