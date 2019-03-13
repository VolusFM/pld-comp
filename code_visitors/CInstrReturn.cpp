#pragma once

#include "CInstrReturn.h"


string CInstrReturn::to_asm() const
{
    string code;
    if(returnValue == nullptr)
    {
        code += "  nop\n";
    }
    else
    {
       code += "  movl $" + to_string(* returnValue) + ", %eax\n"; 
    }
    code += "  popq %rbp\n";
    code += "  ret\n";
    return code;
}
