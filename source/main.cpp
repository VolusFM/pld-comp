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
#include "IR/IProg.h"

using namespace antlr4;


typedef struct {
    bool tmp; /* temporary */
    
    bool opta; // static analysis
    bool opto; // optimize
    bool optc; // assembly generation
    string fi; // input file
    string fo; // output file
} arguments;

inline bool strequal(const char* str1, const char* str2) {
    return strcmp(str1,str2) == 0;
}

bool argsparse(int argc, const char* argv[], arguments& args)
{
    args.tmp = false; /* temporary */
    
    args.fi.clear();
    args.fo.clear();
    args.opta = false;
    args.opto = false;
    args.optc = false;
    
    for(int i=1; i < argc; ++i) {
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
            
            /* temporary */
            else if (strequal(arg, "dev"))
                args.tmp = true;
            
            else {
                cerr << "ERROR: unknown argument : '" << arg << "'" << endl;
                return false;
            }
        } else {
            if (args.fi.empty())
                args.fi = arg;
            else if (args.fo.empty())
                args.fo = arg;
            else {
                cerr << "ERROR: too many arguments" << endl;
                return false;
            }
        }
    }
    
    if (args.fi.empty()) {
        cerr << "ERROR: missing file input argument" << endl;
        return false;
    }
    
    if (!args.optc && !args.fo.empty()) {
        cerr << "ERROR: too many arguments" << endl;
        return false;
    }
    
    return true;
}


int main(int argc, const char* argv[]) {
    
    // ANALYSE DES ARGUMENTS EN LIGNE DE COMMANDE
    
    arguments args;
    
    if (!argsparse(argc, argv, args)) {
        cerr << "ERROR: incorrect arguments" << endl;
        exit(EXIT_FAILURE);
    }
    
    // OUVERTURE DU FICHIER D'ENTREE
    // ET ANALYSE DU CODE SOURCE
    
    ifstream ifs(args.fi);
    
    if (!ifs.is_open()) {
        cerr << "ERROR: can't open input file in reading mode" << endl;
        exit(EXIT_FAILURE);
    }
    
    ANTLRInputStream input(ifs);
    CodeCLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CodeCParser parser(&tokens);
    tree::ParseTree* tree = parser.prog();
    
    if (parser.getNumberOfSyntaxErrors() > 0) {
        cerr << "ERROR: incorrect syntax in the input file" << endl;
        exit(EXIT_FAILURE);
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
            exit(EXIT_FAILURE);
        }
    
        os = &ofs;
    }
    
    Visitor visitor;
    CProg* ast = visitor.visit(tree);
    IProg* ir; if (args.tmp) /* temporary */ ir = ast->to_IR();
    if (args.tmp) delete ast; /* temporary */
    
    if (args.optc) {
        if (args.tmp) /* temporary */
        ir->gen_asm_x86(*os);
        else *os << ast->to_asm(); /* temporary */
        *os << endl;
        if (!args.fo.empty())
            ofs.close();
    }
    if (!args.tmp) delete ast; else /* temporary */
    delete ir;
    
    return 0;
}

