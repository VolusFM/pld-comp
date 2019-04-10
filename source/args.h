#include <string>
using std::string;

typedef struct {
    bool opta; // static analysis
    bool opto; // optimize
    bool optc; // assembly generation
    string fi; // input file
    string fo; // output file

    bool tmp; // temporary
} arguments;

bool argsparse(int argc, const char* argv[], arguments& args);

