#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <fstream>
using std::ifstream;
using std::ofstream;

#include <cstring>

#include "antlr4-runtime.h"
#include "antlr/CodeCLexer.h"
#include "antlr/CodeCParser.h"
#include "antlr/CodeCVisitor.h"

#include "AST/Visitor.h"
#include "AST/CProg.h"
#include "IR/IR.h"

using namespace antlr4;

bool staticAnalysis = false;
bool simplifyProgram = false;

bool incorrectSyntax(int argc, const char* argv[]) {
    return (argc < 3 || strcmp(argv[argc - 1], "-o") == 0
            || strcmp(argv[argc - 1], "-a") == 0);
}

int main(int argc, const char* argv[]) {

    if (incorrectSyntax(argc, argv)) {
        cerr
                << "Syntax: yottacompilatron9001 <c_file> [-o -a] <destination_file>"
                << endl;
        exit (EXIT_FAILURE);
    }

    int i = 2;

    while (i < argc) { // Check if there are options
        if (strcmp(argv[i], "-o") == 0) {
            cout << "Detected -o option (will be implemented later!)" << endl;
            simplifyProgram = true;
        }
        if (strcmp(argv[i], "-a") == 0) {
            cout << "Detected -a option (will be implemented later!)" << endl;
            staticAnalysis = true;
        }
        i++;
    }

    ifstream ifs(argv[1]);

    if (!ifs.is_open()) {
        cerr
                << "Error: input file cannot be opened (did you check the file exists and you have the permission to read it ?)."
                << endl;
        exit (EXIT_FAILURE);
    }

    ofstream ofs(argv[argc - 1]);

    if (!ofs.is_open()) {
        cerr
                << "Error: output file cannot be opened (did you check you have the permission to write there ?)."
                << endl;
        exit (EXIT_FAILURE);
    }

    ANTLRInputStream input(ifs);
    CodeCLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CodeCParser parser(&tokens);
    tree::ParseTree* tree = parser.prog();
    ifs.close();

    if (parser.getNumberOfSyntaxErrors() > 0) {
        cerr << "Error: incorrect syntax in the input file." << endl;
        exit (EXIT_FAILURE);
    }

    Visitor visitor;
    CProg* result = visitor.visit(tree);
    ofs << result->to_asm() << endl;
    delete result;
    ofs.close();

    return 0;
}

