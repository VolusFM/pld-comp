#include "CFunction.h"

#include "CInstrVariable.h"
#include "CInstrExpression.h"
#include "CExpression.h"

using std::to_string;

CFunction::CFunction(string name, CInstructions * blockToMove) :
        name(name) {
    temp_id = 0;
    tosOffset = 0;
    block = std::move(*blockToMove);
}

CFunction::~CFunction() {
    // Nothing to do.
}

string CFunction::to_asm() const {
    string code;
    code += name + ":\n";

    code += "  ## prologue\n";
    code += "  pushq %rbp # save %rbp on the stack\n";
    code += "  movq %rsp, %rbp # define %rbp for the current function\n";

    code += "  ## contenu\n";

    for (const CInstruction* i : block.instructions) {
        code += i->to_asm(this);
    }

    code += "  ## epilogue\n";
    code += "  popq %rbp # restore %rbp from the stack\n";
    code += "  ret\n";

    return code;
}

void CFunction::fill_tos() {
    fill_tos(block);

    for (const string& i : tos) {
        //code += "  # variable " + tosType.at(i) + " " + i + "\n";
        //une fois qu'on aura d'autres tailles de variables, faudra changer ça
        tosOffset -= 4;
        tosAddress[i] = tosOffset;
    }
	
    // code += "sub rsp, "
    // arrondi supérieur ou égal de offset
    // pour obtenir un multiple de 16, pour appel de fonction
}

string CFunction::tos_addr(string variable) const {
    int addr = tosAddress.at(variable);
    return to_string(addr)+"(%rbp)";
}

string CFunction::tos_add_temp(CType type) {
    temp_id++;
    string name = "temp" + to_string(temp_id);
    tos.push_back(name);
    tosType[name] = type;
    tosOffset -= 4;
    tosAddress[name] = tosOffset;
    return name;
}

void CFunction::fill_tos(CInstructions& block) {
    for (auto it = block.instructions.begin(); it != block.instructions.end();
            ++it) {
        const CInstruction* i = *it;
        const CInstrVariable* instrVar = dynamic_cast<const CInstrVariable*>(i);
        if (instrVar != nullptr) {
            string variable = instrVar->name;
            tos.push_back(variable);
            tosType[variable] = "int";

            CExpressionVar * exprVar = new CExpressionVar(variable);
            CExpressionComposed * affectation = new CExpressionComposed(exprVar,
                    "=", instrVar->expr);
            CInstrExpression * instrExpr = new CInstrExpression(affectation);
            *it = instrExpr;
        }
    }
}

