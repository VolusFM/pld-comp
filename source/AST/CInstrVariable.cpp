#include "CInstrVariable.h"

CInstrVariable::CInstrVariable()
: expr(nullptr)
{
}

string CInstrVariable::to_asm() const {
//TODO : memCase positif, nb case memoire a partir de rbp
	string code;
	if (expr != nullptr) {
		code += expr->to_asm(); //TODO : return adress resultat expression 
										// soit eax soit $valeur
		//code += "movl " + expr->result();
		//code += "-4(%rbp) \n";
	}
	return code;
}

