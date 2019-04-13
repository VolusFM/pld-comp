#include "CInstrDoWhile.h"

void CInstrDoWhile::explore_tos(TOS& tos) const {
	blockContent.explore_tos(tos);
}

void CInstrDoWhile::optimize() {
	blockContent.optimize();
	condition->optimize();
}

CInstrDoWhile::CInstrDoWhile(CExpression* condition,
		CInstructions& blockContent_) :
		condition(condition) {
	blockContent = std::move(blockContent_);
	blockContent_.instructions.clear();
}

CInstrDoWhile::~CInstrDoWhile() {
	delete condition;
}

