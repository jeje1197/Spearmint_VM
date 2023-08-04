// Spearmint_VM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "svm_instructions.h"
#include "svm.h"

int main()
{
    // std::string asmProgramText = "d_push -15.5 d_push 10 d_cmp d_print";
    std::string asmProgramText = "d_push 10 d_push 20 jmp d_print program_success";

    /*SVMAssembler assembler(asmProgramText);
    std::vector<uint8_t> bytecode = assembler.getBytecode();*/

    /*uint8_t* memory = bytecode.data();*/

    uint8_t dasArr[8];
    double d = 97.0;

    uint8_t* arr = (uint8_t*) & d;
    
    uint8_t mem[] = {

        PUSH, TYPE_NUMBER,
        arr[0], arr[1], arr[2], arr[3],
        arr[4],  arr[5], arr[6], arr[7],

        PRINT,
        PROGRAM_SUCCESS
    };

    if (run(mem) == 0) {
        std::cout << "Program terminated successfully." << std::endl;
    }
    else {
        std::cout << "Program terminated with an error." << std::endl;
    }
}