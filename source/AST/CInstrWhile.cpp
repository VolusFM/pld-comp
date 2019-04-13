#include "CInstrWhile.h"

void CInstrWhile::explore_tos(TOS& tos) const {
	blockContent.explore_tos(tos);
}

void CInstrWhile::optimize() {
	condition->optimize();
	blockContent.optimize();
}

CInstrWhile::CInstrWhile(CExpression* condition, CInstructions& blockContent_) :
		condition(condition) {
	blockContent = std::move(blockContent_);
	blockContent_.instructions.clear();
}

CInstrWhile::~CInstrWhile() {
	delete condition;
}

