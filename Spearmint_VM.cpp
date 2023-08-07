// Spearmint_VM.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "svm_instructions.h"
#include "svm.h"
#include "spm_file_generator.h"

int main()
{
    // std::string asmProgramText = "d_push -15.5 d_push 10 d_cmp d_print";
    std::string asmProgramText = "d_push 10 d_push 20 jmp d_print program_success";

    /*SVMAssembler assembler(asmProgramText);
    std::vector<uint8_t> bytecode = assembler.getBytecode();*/

    /*uint8_t* memory = bytecode.data();*/
    uint8_t mem[] = {
        I_PUSH, 2, 0, 0, 0,
        I_PUSH, 97, 0, 0, 0,
        STORE_GLOBAL, // globals[2] = 97

        I_PUSH, 6, 2, 1, 0,
        I_PUSH, 2, 0, 0, 0,
        LOAD_GLOBAL, // push globals[2] to stack
        I_PRINT, // print top of stack
        PROGRAM_SUCCESS
    };

    if (run(mem) == 0) {
        std::cout << "Program terminated successfully." << std::endl;
    }
    else {
        std::cout << "Program terminated with an error." << std::endl;
    }



    /*SpmFileGenerator spmGen;
    vector<uint8_t> bytecode = spmGen.generateSpmFile();
    spmGen.disassembleSpmBytecode(bytecode);*/
}