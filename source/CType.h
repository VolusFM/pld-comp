#pragma once

#include <string>
using std::string;

class CType {
public:
	CType();
	CType(const char* name);
	CType(string name);

	int size_x86();
	int size_z80();

	bool has();
	void set(string name);

protected:
	friend bool operator ==(const CType& lhs, const CType& rhs);
	friend bool operator !=(const CType& lhs, const CType& rhs);

private:
	string base;
};

inline bool operator ==(const CType& lhs, const CType& rhs) {
	return lhs.base == rhs.base;
}

inline bool operator !=(const CType& lhs, const CType& rhs) {
	return lhs.base != rhs.base;
}

