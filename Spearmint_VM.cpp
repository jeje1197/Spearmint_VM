// Spearmint_VM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "svm_instructions.h"
#include "SVM.h"
#include "assembler.h"

int main()
{
    // std::string asmProgramText = "d_push -15.5 d_push 10 d_cmp d_print";
    std::string asmProgramText = "d_push 10 d_push 20 jmp d_print program_success";

    /*SVMAssembler assembler(asmProgramText);
    std::vector<uint8_t> bytecode = assembler.getBytecode();*/

    /*uint8_t* memory = bytecode.data();*/
    
    uint8_t mem[] = {
        I_PUSH, 250, 0, 0, 0,
        I_PUSH, 254, 0, 0, 0,
        I_CMP,
        I_PRINT,
        PROGRAM_SUCCESS
    };

    if (run(mem) == -1) {
        std::cout << "Program terminated abruptly" << std::endl;
    }
}