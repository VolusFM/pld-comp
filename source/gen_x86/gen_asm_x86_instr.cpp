#include "../IR/IR.h"

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;

#include <string>
using std::stoi;
using std::to_string;

#include "gen_asm_x86_util.h"

void IRInstr::gen_asm_x86(ostream& o) const {
	CFG* cfg = bb->cfg;
	TOS& tos = cfg->tos;
	int index, address;
	string loc;

	/*
		for 3-op instrs: d, x, y;
		for ldconst: d, c;
		for call: label, d, params;
		for wmem and rmem: variable, address;
	*/
	switch (op) {
	case op_copy:
		o << "  movl  " << tos.get_address_x86(params[1]) << ", %eax\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_ldconst:
		o << "  movl  " << params[1] << ", " << tos.get_address_x86(params[0])
				<< "\n";
		break;
	case op_copy_array:
		o << "  movl  " << tos.get_address_x86(params[1]) << ", %edx\n";
		o << "  movl  %edx, " << tos.get_address_x86_array(params[0]) << "\n";
		break;
	case op_ldconst_array:
		o << "  movl  " << params[1] << ", "
				<< tos.get_address_x86_array(params[0]) << "\n";
		break;
	case op_copy_from_array:
		o << "  movl  " << tos.get_address_x86_array(params[1]) << ", %eax\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_copy_to_array_index:
		address = cfg->tos.get_index(params[0]);
		index = stoi(params[1]);
		loc = "-" + to_string(address - 4 * index) + "(%rbp)";
		o << "  movl  " << tos.get_address_x86(params[2]) << ", %edx\n";
		o << "  movl  %edx, " << loc << "\n";
		break;
	case op_ldconst_to_array_index:
		address = cfg->tos.get_index(params[0]);
		index = stoi(params[1]);
		loc = "-" + to_string(address - 4 * index) + "(%rbp)";
		o << "  movl  " << params[2] << ", " << loc << "\n";
		break;
	case op_index:
		o << "  movl  " << tos.get_address_x86(params[0]) << ", %eax\n";
		o << "  cltq \n";
		break;
	case op_index_ldconst:
		o << "  movl  " << params[0] << ", %eax\n";
		o << "  cltq \n";
		break;
	case op_add:
		o << "  movl  " << tos.get_address_x86(params[1]) << ", %eax" << "\n";
		o << "  addl  " << tos.get_address_x86(params[2]) << ", %eax" << "\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_sub:
		o << "  movl  " << tos.get_address_x86(params[1]) << ", %eax" << "\n";
		o << "  subl  " << tos.get_address_x86(params[2]) << ", %eax" << "\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_mul:
		o << "  movl  " << tos.get_address_x86(params[1]) << ", %eax" << "\n";
		o << "  imull " << tos.get_address_x86(params[2]) << ", %eax" << "\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_div:
		o << "  movl  " << tos.get_address_x86(params[1]) << ", %eax" << "\n";
		o << "  cltd\n";
		o << "  idivl " << tos.get_address_x86(params[2]) << "\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_mod:
		o << "  movl  " << tos.get_address_x86(params[1]) << ", %eax" << "\n";
		o << "  cltd\n";
		o << "  idivl " << tos.get_address_x86(params[2]) << "\n";
		o << "  movl  %edx, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_binary_and:
		o << "  movl  " << tos.get_address_x86(params[1]) << ", %eax" << "\n";
		o << "  andl  " << tos.get_address_x86(params[2]) << ", %eax" << "\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_binary_or:
		o << "  movl  " << tos.get_address_x86(params[1]) << ", %eax" << "\n";
		o << "  orl   " << tos.get_address_x86(params[2]) << ", %eax" << "\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_binary_xor:
		o << "  movl  " << tos.get_address_x86(params[1]) << ", %eax" << "\n";
		o << "  xorl  " << tos.get_address_x86(params[2]) << ", %eax" << "\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_not:
		o << "  cmpl  $0, " << tos.get_address_x86(params[2]) << "\n";
		o << "  sete    %al\n";
		o << "  movzbl  %al, %eax\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_cmp_eq:
		o << "  movl  " << tos.get_address_x86(params[1]) << ", %eax" << "\n";
		o << "  cmpl  " << tos.get_address_x86(params[2]) << ", %eax\n";
		o << "  sete    %al\n";
		o << "  movzbl  %al, %eax\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_cmp_ne:
		o << "  movl  " << tos.get_address_x86(params[1]) << ", %eax" << "\n";
		o << "  cmpl  " << tos.get_address_x86(params[2]) << ", %eax\n";
		o << "  setne   %al\n";
		o << "  movzbl  %al, %eax\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_cmp_lt:
		o << "  movl  " << tos.get_address_x86(params[1]) << ", %eax" << "\n";
		o << "  cmpl  " << tos.get_address_x86(params[2]) << ", %eax\n";
		o << "  setl    %al\n";
		o << "  movzbl  %al, %eax\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_cmp_le:
		o << "  movl  " << tos.get_address_x86(params[1]) << ", %eax" << "\n";
		o << "  cmpl  " << tos.get_address_x86(params[2]) << ", %eax\n";
		o << "  setle   %al\n";
		o << "  movzbl  %al, %eax\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_cmp_gt:
		o << "  movl  " << tos.get_address_x86(params[1]) << ", %eax" << "\n";
		o << "  cmpl  " << tos.get_address_x86(params[2]) << ", %eax\n";
		o << "  setg    %al\n";
		o << "  movzbl  %al, %eax\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_cmp_ge:
		o << "  movl  " << tos.get_address_x86(params[1]) << ", %eax" << "\n";
		o << "  cmpl  " << tos.get_address_x86(params[2]) << ", %eax\n";
		o << "  setge   %al\n";
		o << "  movzbl  %al, %eax\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[0]) << "\n";
		break;
	case op_call:
		index = 0;
		for (auto it = params.begin() + 2; it != params.end(); ++it) {
			o << "  movl " << tos.get_address_x86(*it) << ", "
					<< registerName[index] << "\n";
			if (++index == 6)
				break;
		}
		o << "  call  " << params[0] << "\n";
		o << "  movl  %eax, " << tos.get_address_x86(params[1]) << "\n";
		break;
	case op_return:
		o << "  movl  "
				<< (params[0].at(0) == '$' ?
						params[0] : tos.get_address_x86(params[0]))
				<< ", %eax\n";
		break;

	/*
	case op_rmem:
		break;
	case op_wmem:
		break;
	*/
	default:
		cerr << "PROBLEM: operator not yet supported" << endl;
		throw;
		break;
	}
}

