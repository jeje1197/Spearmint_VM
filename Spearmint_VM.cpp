// Spearmint_VM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "SVM.h"
#include "Assembler.h"

int main()
{
    std::string asmProgramText = "pushint 16 alloc pushint 12 storestr \"God is good!\" printstr exit"; 
        //"alloc 18 storestr \"Joseph is awesome!\" printstr";

    SVMAssembler assembler(asmProgramText);
    std::vector<uint8_t> bytecode = assembler.getBytecode();

    uint8_t* memory = bytecode.data();
    run(memory);

    //std::cout << "Text passed: " << std::endl;

    //for (auto instruction: assembler.getMapping()) {
    //    std::cout <<  instruction.first << ":" << (int) instruction.second << std::endl;
    //}
    //std::cout << "Resulting Bytecode Instructions: " << (int) bytecode.size() << std::endl;
    //for (auto byte : bytecode) {
    //    std::cout << (int) byte << std::endl;
    //}

}