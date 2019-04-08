#include "IR.h"

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;

static const string registerName[] = { "%rdi", "%rsi", "%rdx", "%rcx", "%r8d", "%r9d" };

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
        o << "  movl  " << params[1] << ", %eax\n";
        o << "  movl  %eax, " << params[0] << "\n";
        break;
    case op_ldconst:
        o << "  movl  " << params[1] << ", " << params[0]
                << "\n";
        break;
    case op_index:
        o << "  movl  " << params[0] << ", %eax \n";
        o << "  cltq \n";
        break;
    case op_add:
        o << "  movl  " << params[1] << ", %eax" << "\n";
        o << "  addl  " << params[2] << ", %eax" << "\n";
        o << "  movl  %eax, " << params[0] << "\n";
        break;
    case op_sub:
        o << "  movl  " << params[1] << ", %eax" << "\n";
        o << "  subl  " << params[2] << ", %eax" << "\n";
        o << "  movl  %eax, " << params[0] << "\n";
        break;
    case op_mul:
        o << "  movl  " << params[1] << ", %eax" << "\n";
        o << "  imull " << params[2] << ", %eax" << "\n";
        o << "  movl  %eax, " << params[0] << "\n";
        break;
    case op_div:
        o << "  movl  " << params[1] << ", %eax" << "\n";
        o << "  cltd\n";
        o << "  idivl " << params[2] << "\n";
        o << "  movl  %eax, " << params[0] << "\n";
        break;
    case op_mod:
        o << "  movl  " << params[1] << ", %eax" << "\n";
        o << "  cltd\n";
        o << "  idivl " << params[2] << "\n";
        o << "  movl  %edx, " << params[0] << "\n";
        break;
    case op_binary_and : 
	    o << "  movl  " << params[1] << ", %eax" << "\n";
	    o << "  andl  " << params[2] << ", %eax" << "\n";
        o << "  movl  %eax, " << params[0] << "\n"; 
 	break;
    case op_binary_or : 
	    o << "  movl  " << params[1] << ", %eax" << "\n";
	    o << "  orl   " << params[2] << ", %eax" << "\n";
        o << "  movl  %eax, " << params[0] << "\n"; 
	break;
    case op_binary_xor :
	    o << "  movl  " << params[1] << ", %eax" << "\n";
	    o << "  xorl  " << params[2] << ", %eax" << "\n";
        o << "  movl  %eax, " << params[0] << "\n"; 
	break;
    case op_not:
	    o << "  cmpl  $0, " << params[2] << "\n";
        o << "  sete    %al\n";
        o << "  movzbl  %al, %eax\n"; 
        o << "  movl  %eax, " << params[0] << "\n";
	break;
    case op_cmp_eq :
        o << "  movl  " << params[1] << ", %eax" << "\n";
        o << "  cmpl  " << params[2] << ", %eax\n";
        o << "  sete    %al\n";
        o << "  movzbl  %al, %eax\n";
        o << "  movl  %eax, " << params[0] << "\n";
        break;
    case op_cmp_ne :
        o << "  movl  " << params[1] << ", %eax" << "\n";
        o << "  cmpl  " << params[2] << ", %eax\n";
        o << "  setne   %al\n";
        o << "  movzbl  %al, %eax\n";
        o << "  movl  %eax, " << params[0] << "\n";
        break;
    case op_cmp_lt :
        o << "  movl  " << params[1] << ", %eax" << "\n";
        o << "  cmpl  " << params[2] << ", %eax\n";
        o << "  setl    %al\n";
        o << "  movzbl  %al, %eax\n";
        o << "  movl  %eax, " << params[0] << "\n";
        break;
    case op_cmp_le :
        o << "  movl  " << params[1] << ", %eax" << "\n";
        o << "  cmpl  " << params[2] << ", %eax\n";
        o << "  setle   %al\n";
        o << "  movzbl  %al, %eax\n";
        o << "  movl  %eax, " << params[0] << "\n";
        break;
    case op_cmp_gt :
        o << "  movl  " << params[1] << ", %eax" << "\n";
        o << "  cmpl  " << params[2] << ", %eax\n";
        o << "  setg    %al\n";
        o << "  movzbl  %al, %eax\n";
        o << "  movl  %eax, " << params[0] << "\n";
        break;
    case op_cmp_ge :
        o << "  movl  " << params[1] << ", %eax" << "\n";
        o << "  cmpl  " << params[2] << ", %eax\n";
        o << "  setge   %al\n";
        o << "  movzbl  %al, %eax\n";
        o << "  movl  %eax, " << params[0] << "\n";
        break;
    //TODO : quoi de la fuck de l accolade ?
    case op_call : {
        int index = 0;
        for (auto it = params.begin()+2 ; it != params.end() ; ++it) {
            o << "  movl " << cfg->tos_get_asm_x86(*it) << ", " << registerName[index] << "\n";
            if (++index==6) break;
        }
        o << "  call " << params[0] << "\n";
        o << "  movl  %eax, " << params[1] << "\n";
        break;
    }

        /*
        case op_rmem:
            break;
        case op_wmem:
            break;
        case op_cmp_eq:
            break;
        case op_cmp_lt:
            break;
        case op_cmp_le:
            break;
        */
        // to do
    default:
        cerr << "PROBLEM: operator not yet supported" << endl;
        throw;
        break;
    }
}

