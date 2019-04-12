#include "TOS.h"

#include <iostream>
using std::cerr;
using std::endl;
#include <string>
using std::to_string;

TOS::TOS(const TOS* parent) :
		parent(parent), tosOffset(0), tosTemps(0) {
}

TOS::TOS() :
		parent(nullptr), tosOffset(0), tosTemps(0) {
}

bool TOS::has(string name) const {
	return (tosType.find(name) != tosType.end());
}

void TOS::add(string name, CType type, int count) {
	if (has(name)) {
		cerr << "ERROR: already declared variable '" << name << "'" << endl;
		throw;
	}

	tos.push_back(name);
	tosType[name] = type;
	tosCount[name] = count;
}

string TOS::add_temp(CType type) {
	for (auto it = tosUsed.begin(); it != tosUsed.end(); ++it) {
		if (!it->second) {
			string name = it->first;
			if (tosType[name] == type) {
				tosUsed[name] = true;
				return name;
			}
		}
	}

	string name = "temp" + to_string(++tosTemps);

	add(name, type);

	if (platform == "z80") {
		tosOffset += type.size_z80();
	} else if (platform == "x86") {
		int size = type.size_x86();
		int shift = tosOffset % size;
		if (shift) {
			// align to multiple of size
			tosOffset += size - shift;
		}
		tosOffset += size;
	}
	if (platform != "") {
		tosIndex[name] = tosOffset;
	}

	tosUsed[name] = true;
	return name;
}

void TOS::free_temp(string name) {
	// if (name.at(0) != '!') return;
	auto it = tosUsed.find(name);
	if (it != tosUsed.end())
		(*it).second = false;
}

void TOS::clear_temp() {
	for (auto it = tos.begin(); it != tos.end(); /*rien*/) {
		const string name = (*it);
		if (name.at(0) == '!') {
			tosType.erase(name);
			tosCount.erase(name);
			it = tos.erase(it);
		} else {
			++it;
		}
	}

	clear_address();
}

void TOS::clear_address() {
	platform.clear();
	tosIndex.clear();
	tosUsed.clear();
	tosOffset = 0;
	tosTemps = 0;
}

void TOS::fill_address_z80() {
	tosOffset = 0;
	platform = "z80";

	for (const string& name : tos) {
		int size = tosType.at(name).size_z80();
		tosOffset += size * tosCount[name];
		tosIndex[name] = tosOffset;
	}
}

void TOS::fill_address_x86() {
	tosOffset = 0;
	platform = "x86";

	for (const string& name : tos) {
		int size = tosType.at(name).size_x86();

		int shift = tosOffset % size;
		if (shift) {
			// align to multiple of size
			tosOffset += size - shift;
		}

		tosOffset += size * tosCount[name];
		tosIndex[name] = tosOffset;
	}
}

string TOS::get_address_z80(string name) const {
	if (has(name)) {
		int addr = tosIndex.at(name);
		return to_string(addr);
	} else if (parent != nullptr) {
		return parent->get_address_z80(name);
	} else {
		cerr << "ERROR: reference to undeclared variable '" << name << "'"
				<< endl;
		throw;
	}
}

string TOS::get_address_x86(string name) const {
	if (name.at(0) == '$')
		return name;

	if (has(name)) {
		int addr = -tosIndex.at(name);
		return to_string(addr) + "(%rbp)";
	} else if (parent != nullptr) {
		return parent->get_address_x86(name);
	} else {
		cerr << "ERROR: reference to undeclared variable '" << name << "'"
				<< endl;
		throw;
	}
}

string TOS::get_address_x86_array(string name) const {
	if (has(name)) {
		int addr = -tosIndex.at(name);
		return to_string(addr) + "(%rbp,%rax,4)";
	} else if (parent != nullptr) {
		return parent->get_address_x86_array(name);
	} else {
		cerr << "ERROR: reference to undeclared variable '" << name << "'"
				<< endl;
		throw;
	}
}

int TOS::get_index(string name) const {
	try {
		return tosIndex.at(name);
	} catch (...) {
		cerr << "ERROR: reference to undeclared variable '" << name << "'"
				<< endl;
		throw;
	}
}

CType TOS::get_type(string name) const {
	if (has(name)) {
		return tosType.at(name);
	} else {
		cerr << "ERROR: reference to undeclared variable '" << name << "'"
				<< endl;
		throw;
	}
}

