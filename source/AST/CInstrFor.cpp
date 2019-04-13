#include "CInstrFor.h"

void CInstrFor::explore_tos(TOS& tos) const {
	blockContent.explore_tos(tos);
}

void CInstrFor::optimize() {
	blockContent.optimize();

	CExpression* opti;

	if (start != nullptr) {
		start->optimize();
	}

	if (stopCondition != nullptr) {
		stopCondition->optimize();
	}

	if (evolution != nullptr) {
		evolution->optimize();
	}
}

CInstrFor::CInstrFor(CExpression* start, CExpression* stopCondition,
		CExpression* evolution, CInstructions& blockContent_) :
		start(start), stopCondition(stopCondition), evolution(evolution) {
	blockContent = std::move(blockContent_);
	blockContent_.instructions.clear();
}

CInstrFor::~CInstrFor() {
	if (start != nullptr) {
		delete start;
	}

	if (stopCondition != nullptr) {
		delete stopCondition;
	}

	if (evolution != nullptr) {
		delete evolution;
	}
}

