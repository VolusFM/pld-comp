#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <fstream>
using std::ifstream;
using std::ofstream;

#include "antlr4-runtime.h"
#include "antlr/CodeCLexer.h"
#include "antlr/CodeCParser.h"
#include "antlr/CodeCVisitor.h"
using namespace antlr4;

#include "args.h"
#include "AST/Visitor.h"
#include "AST/CProg.h"
#include "IR/IR.h"
#include "IR/IProg.h"

int main(int argc, const char* argv[]) {
    
    arguments args;
    
    // ANALYSE DES ARGUMENTS EN LIGNE DE COMMANDE

    if (!argsparse(argc, argv, args)) {
        cerr << "Syntax: ./yottacompilatron9001 <input_file> [-o] [-a] [-c [<output_file>]]" << endl;
        exit (EXIT_FAILURE);
    }

    // OUVERTURE DU FICHIER D'ENTREE
    // ET ANALYSE DU CODE SOURCE

    ifstream ifs(args.fi);

    if (!ifs.is_open()) {
        cerr << "ERROR: can't open input file in reading mode." << endl;
        exit (EXIT_FAILURE);
    }

    ANTLRInputStream input(ifs);
    CodeCLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CodeCParser parser(&tokens);
    tree::ParseTree* tree = parser.prog();

    if (parser.getNumberOfSyntaxErrors() > 0) {
        cerr << "ERROR: incorrect syntax in the input file." << endl;
        exit (EXIT_FAILURE);
    }

    ifs.close();

    // OUVERTURE DU FICHIER DE DESTINATION
    // ET COMPILATION DU CODE SOURCE

    ostream* os;

    ofstream ofs;
    if (args.fo.empty()) {
        os = &cout;
    } else {
        ofs.open(args.fo);

        if (!ofs.is_open()) {
            cerr << "ERROR: can't open output file in writing mode" << endl;
            exit (EXIT_FAILURE);
        }

        os = &ofs;
    }

    Visitor visitor;
    CProg* ast = visitor.visit(tree);
    
    if (args.opto) ast->optimize();
    
    IProg* ir = ast->to_IR();
    if (args.opto) ir->optimize();
    
    if (args.opta && !args.optc) {
        args.optc = true;
        args.fo = "/dev/null";
    }
    
    if (args.optc) {
        if (!args.tmp) // temporary
            ir->gen_asm_x86(*os);

        // temporary
        else
            ast->gen_asm(*os);

        *os << endl;
        if (!args.fo.empty())
            ofs.close();
    }

    delete ast;
    delete ir;

    return 0;
}

