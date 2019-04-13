#include "CInstrVariable.h"

#include "CExpression.h"

#include "../TOS.h"

void CInstrVariable::explore_tos(TOS& tos) const {
	tos.add(name, type);
}

void CInstrVariable::optimize() {
	if (expr != nullptr) {
		expr->optimize();
	}
}

CInstrVariable::CInstrVariable(string name, CType type) :
		name(name), type(type), expr(nullptr) {
}

CInstrVariable::CInstrVariable(string name, CType type, CExpressionPart* expr_) :
		name(name), type(type) {
	CExpressionVar* exprvar = new CExpressionVar(name);
	CExpressionPart* affect = new CExpressionComposed(exprvar, "=", expr_);
	expr = new CExpression(affect);
}

CInstrVariable::~CInstrVariable() {
	if (expr != nullptr) {
		delete expr;
	}
}

