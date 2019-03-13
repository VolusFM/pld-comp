#include "antlr4-runtime.h"
#include "code_antlr/CodeCLexer.h"
#include "code_antlr/CodeCParser.h"
#include "code_antlr/CodeCVisitor.h"
#include "code_visitors/Visitor.h"
#include "code_visitors/CProg.h"

using namespace antlr4;
using namespace std;

int main(int argc, const char* argv[]) {
  // CodeCLexer lexer(CharStream.fromFileName("./input.c"));
  ANTLRInputStream input("int main() { return 42; }");
  CodeCLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  
  CodeCParser parser(&tokens);
  tree::ParseTree* tree = parser.prog();
  
  Visitor visitor;
  CProg * resultat = visitor.visit(tree);
  cout << resultat->to_asm() << endl;
  
  return 0;
}

