// Spearmint_VM.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>

#include "assembler.h"
#include "spm_file_generator.h"
#include "svm_instructions.h"
#include "svm.h"


int main()
{
    /*SVMAssembler assembler(asmProgramText);
    std::vector<uint8_t> bytecode = assembler.getBytecode();*/

    /*uint8_t* memory = bytecode.data();*/
    //uint8_t mem[] = {
    //    PUSH, 1,    3, 97, 98, 99,  // string length 3 - "abc"
    //    PUSH, 1,    3, 98, 99, 100, // boolean - false
    //    CMP,

    //    PRINT, // print top of stack

    //    //CALL, 
    //    PROGRAM_SUCCESS
    //};

    std::string asmText = "PUSH \"Hello World!\" PRINT PROGRAM_SUCCESS";

    SvmAssembler assembler(asmText);
    vector<uint8_t> bytecode = assembler.getBytecode();
    uint8_t* mem = bytecode.data();

    if (run(mem) == 0) {
        std::cout << "\nProgram terminated successfully." << std::endl;
    }
    else {
        std::cout << "Program terminated with an error." << std::endl;
    }
}