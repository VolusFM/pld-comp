#include "antlr4-runtime.h"
#include "code_antlr/CodeCLexer.h"
#include "code_antlr/CodeCParser.h"
#include "code_antlr/CodeCVisitor.h"
// #include "code_visitors/Visitor.h"

using namespace antlr4;
using namespace std;

int main(int argc, const char* argv[]) {
  ANTLRInputStream input("int main() { return 42; }");
  CodeCLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  
  CodeCParser parser(&tokens);
  tree::ParseTree* tree = parser.prog();
  
  // Visitor visitor;
  // string resultat = (string) visitor.visit(tree);
  // cout << "Résultat " << resultat << endl;
  
  return 0;
}

