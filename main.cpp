#include <iostream>
#include <fstream>
#include <sstream>

#include "antlr4-runtime.h"
#include "code_antlr/CodeCLexer.h"
#include "code_antlr/CodeCParser.h"
#include "code_antlr/CodeCVisitor.h"
#include "code_visitors/Visitor.h"
#include "code_visitors/CProg.h"

using namespace antlr4;
using namespace std;

int main(int argc, const char* argv[]) {

  if (argc != 2) {
    cout << "Syntaxe : exe <fichier.c>" << endl;
    exit(EXIT_FAILURE);
  } 

  stringstream in; 
  if (argc == 2) {
    ifstream fichier(argv[1]);
    in << fichier.rdbuf();
  }

  ANTLRInputStream input(in.str());
  CodeCLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  
  CodeCParser parser(&tokens);
  tree::ParseTree* tree = parser.prog();
  
  Visitor visitor;
  CProg * resultat = visitor.visit(tree);
  cout << resultat->to_asm() << endl;
  
  return 0;
}

