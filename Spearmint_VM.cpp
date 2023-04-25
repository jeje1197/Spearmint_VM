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
        // CREATE_STATIC, // Creates an array of static variables
        
        I_PUSH, 97, 0, 0, 0,
        I_PUSH, 0, 0, 0, 0,
        STORE_STATIC,

        I_PUSH, 7, 0, 0, 0,
        I_PUSH, 6, 0, 0, 0,
        I_PUSH, 5, 0, 0, 0,
        I_PUSH, 244, 0, 0, 0,

        I_PUSH, 5, 0, 0, 0,
        I_PUSH, 0, 0, 0, 0,
        LOAD_STATIC,
        I_ADD,
        I_PRINT,

       /* I_PUSH, 250, 0, 0, 0,
        I_PUSH, 254, 0, 0, 0,
        I_CMP,
        I_PRINT,*/
        PROGRAM_SUCCESS
    };

    if (run(mem) == -1) {
        std::cout << "Program terminated abruptly" << std::endl;
    }
}