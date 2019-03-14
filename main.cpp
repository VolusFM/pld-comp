#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <fstream>
using std::ifstream;

#include "antlr4-runtime.h"
#include "code_antlr/CodeCLexer.h"
#include "code_antlr/CodeCParser.h"
#include "code_antlr/CodeCVisitor.h"

#include "code_visitors/Visitor.h"
#include "code_visitors/CProg.h"

using namespace antlr4;

int main(int argc, const char* argv[]) {
  
  if (argc < 2) {
    cerr << "Error: missing input file parameter." << endl;
    exit(EXIT_FAILURE);
  }
  
  ifstream stream(argv[1]);
  
  ANTLRInputStream input(stream);
  CodeCLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  
  CodeCParser parser(&tokens);
  tree::ParseTree* tree = parser.prog();
  
  Visitor visitor;
  CProg* resultat = visitor.visit(tree);
  cout << resultat->to_asm() << endl;
  
  return 0;
}

