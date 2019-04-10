#include "IR.h"

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;

void IRInstr::gen_asm_x86(ostream& o) const {
    CFG* cfg = bb->cfg;
    
    /*
        for 3-op instrs: d, x, y;
        for ldconst: d, c;
        for call: label, d, params;
        for wmem and rmem: choose yourself
    */
    switch (op) {
    case op_copy:
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    case op_ldconst:
        o << "  movl  " << params[1] << ", " << cfg->tos_get_asm_x86(params[0])
                << "\n";
        break;
    case op_copy_array:
        o << "  movl  "  << cfg->tos_get_asm_x86(params[1]) << ", %edx\n";
        o << "  movl  %edx, " << cfg->tos_get_asm_x86_array(params[0]) << "\n";
        break;
    case op_ldconst_array:
        o << "  movl  " << params[1] << ", " << cfg->tos_get_asm_x86_array(params[0])<< "\n";
        break;
    case op_copy_from_array:
        o << "  movl  "  << cfg->tos_get_asm_x86_array(params[1]) << ", %eax\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    case op_copy_mem:
        o << "  movl  "  << cfg->tos_get_asm_x86(params[1]) << ", %eax\n";
        o << "  movl  %eax, -" << params[0] << "(%rbp) \n";
        break;
    case op_ldconst_mem:
        o << "  movl  " << params[1] << ", -" << params[0] << "(%rbp) \n";
        break;
    case op_index:
        o << "  movl  " << cfg->tos_get_asm_x86(params[0]) << ", %eax \n";
        o << "  cltq \n";
        break;
    case op_index_ldconst:
        o << "  movl  " << params[0] << ", %eax \n";
        o << "  cltq \n";
        break;
    case op_add:
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
        o << "  addl  " << cfg->tos_get_asm_x86(params[2]) << ", %eax" << "\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    case op_sub:
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
        o << "  subl  " << cfg->tos_get_asm_x86(params[2]) << ", %eax" << "\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    case op_mul:
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
        o << "  imull " << cfg->tos_get_asm_x86(params[2]) << ", %eax" << "\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    case op_div:
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
        o << "  cltd\n";
        o << "  idivl " << cfg->tos_get_asm_x86(params[2]) << "\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    case op_mod:
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
        o << "  cltd\n";
        o << "  idivl " << cfg->tos_get_asm_x86(params[2]) << "\n";
        o << "  movl  %edx, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    case op_binary_and : 
	o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
	o << "  andl  " << cfg->tos_get_asm_x86(params[2]) << ", %eax" << "\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n"; 
 	break;
    case op_binary_or : 
	o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
	o << "  orl   " << cfg->tos_get_asm_x86(params[2]) << ", %eax" << "\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n"; 
	break;
    case op_binary_xor :
	o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
	o << "  xorl  " << cfg->tos_get_asm_x86(params[2]) << ", %eax" << "\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n"; 
	break;
    case op_not:
	o << "  cmpl  $0, " << cfg->tos_get_asm_x86(params[2]) << "\n";
        o << "  sete    %al\n";
        o << "  movzbl  %al, %eax\n"; 
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
	break;
    case op_cmp_eq :
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
        o << "  cmpl  " << cfg->tos_get_asm_x86(params[2]) << ", %eax\n";
        o << "  sete    %al\n";
        o << "  movzbl  %al, %eax\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    case op_cmp_ne :
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
        o << "  cmpl  " << cfg->tos_get_asm_x86(params[2]) << ", %eax\n";
        o << "  setne   %al\n";
        o << "  movzbl  %al, %eax\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    case op_cmp_lt :
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
        o << "  cmpl  " << cfg->tos_get_asm_x86(params[2]) << ", %eax\n";
        o << "  setl    %al\n";
        o << "  movzbl  %al, %eax\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    case op_cmp_le :
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
        o << "  cmpl  " << cfg->tos_get_asm_x86(params[2]) << ", %eax\n";
        o << "  setle   %al\n";
        o << "  movzbl  %al, %eax\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    case op_cmp_gt :
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
        o << "  cmpl  " << cfg->tos_get_asm_x86(params[2]) << ", %eax\n";
        o << "  setg    %al\n";
        o << "  movzbl  %al, %eax\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    case op_cmp_ge :
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
        o << "  cmpl  " << cfg->tos_get_asm_x86(params[2]) << ", %eax\n";
        o << "  setge   %al\n";
        o << "  movzbl  %al, %eax\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    //TODO : quoi de la fuck de l accolade ?
    case op_call :
        {
        int index = 0;
        for (auto it = params.begin()+2 ; it != params.end() ; ++it) {
            o << "  movq " << cfg->tos_get_asm_x86(*it) << ", " << registerName[index] << "\n";
            if (++index==6) break;
        }
        }
        o << "  call  " << params[0] << "\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[1]) << "\n";
        break;
    case op_return:
        o << "  movl  " << (params[0].at(0) == '$' ? params[0] : cfg->tos_get_asm_x86(params[0])) << ", %eax\n";
        break;
    
        // to do
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

