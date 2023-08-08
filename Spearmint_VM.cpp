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
        PUSH, 1,    3, 97, 98, 99,
        PUSH, 2,    1,
        ADD,

        PRINT, // print top of stack
        PROGRAM_SUCCESS
    };

    if (run(mem) == 0) {
        std::cout << "\nProgram terminated successfully." << std::endl;
    }
    else {
        std::cout << "Program terminated with an error." << std::endl;
    }



    /*SpmFileGenerator spmGen;
    vector<uint8_t> bytecode = spmGen.generateSpmFile();
    spmGen.disassembleSpmBytecode(bytecode);*/
}