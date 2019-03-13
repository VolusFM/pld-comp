#include "CVarDefinition.h"


string CVarDefinition::to_asm() const {
//TODO : memCase positif, nb case memoire a partir de rbp
	string code="";
	if(expression){
		code += expression->to_asm(); //TODO : return adress resultat expression 
										// soit eax soit $valeur
		//code += "movl " + expression->result();
		//code += "-4(%rbp) \n";
	}
	return code;
}

