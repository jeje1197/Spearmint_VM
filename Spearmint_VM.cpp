// Spearmint_VM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
    /*uint8_t mem[] = {
        CALL, PROGRAM_SUCCESS
    };

    if (run(mem) == 0) {
        std::cout << "Program terminated successfully." << std::endl;
    }
    else {
        std::cout << "Program terminated with an error." << std::endl;
    }*/

    SpmFileGenerator spmGen;
    spmGen.generateSpmFile();
}