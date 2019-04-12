#include <string>
using std::string;

typedef struct {
	bool opta; // static analysis
	bool opto; // optimize
	bool optc; // assembly generation
	string fi; // input file
	string fo; // output file

	string lo; // output assembly langage
} arguments;

bool argsparse(int argc, const char* argv[], arguments& args);

