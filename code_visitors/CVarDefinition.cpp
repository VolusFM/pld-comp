#include "CVarDefinition.h"


string CVarDefinition::to_asm(int memCase) const {
//TODO : memCase positif, nb case memoire a partir de rbp
	string code="";
	if(expression){
		code += expression.to_asm(); //TODO : return adress resultat expression 
										// soit eax soit $valeur
		code += "movl " + expression.result();
		code += "-" + memCase + "(%rbp) \n";
	} else	{
		return code;
	}
}

