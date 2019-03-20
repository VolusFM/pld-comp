#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <fstream>
using std::ifstream;

#include "antlr4-runtime.h"
#include "antlr/CodeCLexer.h"
#include "antlr/CodeCParser.h"
#include "antlr/CodeCVisitor.h"

#include "AST/Visitor.h"
#include "AST/CProg.h"

using namespace antlr4;

int main(int argc, const char* argv[]) {
    
    if (argc < 2) {
        cerr << "Error: missing input file parameter." << endl;
        exit (EXIT_FAILURE);
    }
    
    ifstream stream(argv[1]);
    
    ANTLRInputStream input(stream);
    CodeCLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CodeCParser parser(&tokens);
    tree::ParseTree* tree = parser.prog();
    
    if (parser.getNumberOfSyntaxErrors() > 0) {
        cerr << "Error: incorrect syntax in the input file." << endl;
        exit (EXIT_FAILURE);
    }
    
    Visitor visitor;
    CProg* result = visitor.visit(tree);
    cout << result->to_asm() << endl;
    delete result;
    
    return 0;
}

