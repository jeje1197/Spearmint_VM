// Spearmint_VM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "svm_instructions.h"
#include "SVM.h"
#include "assembler.h"

int main()
{
    std::string asmProgramText = "d_push -15.5 d_push 10 d_cmp d_print";

    SVMAssembler assembler(asmProgramText);
    std::vector<uint8_t> bytecode = assembler.getBytecode();

    uint8_t* memory = bytecode.data();

    run(memory);
}