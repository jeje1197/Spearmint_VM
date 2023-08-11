#include <iostream>
#include <string>
#include <fstream>

#include "assembler.h"
#include "spm_file_generator.h"
#include "svm_instructions.h"
#include "svm.h"

std::string getFileText(std::string fileName) {
    std::string fileText, text;
    std::ifstream MyReadFile(fileName);

    while (getline(MyReadFile, text)) {
        fileText += text + "\n";
    }

    if (fileText.size() > 0) {
        return fileText.erase(fileText.length() - 1, 1);
    }
    return "";
}


int main()
{
    //uint8_t mem[] = {
    //    PUSH, 1,    3, 97, 98, 99,  // string length 3 - "abc"
    //    PUSH, 1,    3, 98, 99, 100, // boolean - false
    //    CMP,

    //    PRINT, // print top of stack

    //    //CALL, 
    //    PROGRAM_SUCCESS
    //};

    std::string asmText = getFileText("example.spm");
    //std::cout << asmText << std::endl;


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