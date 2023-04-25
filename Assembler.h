//#pragma once
//
//#include "svm_instructions.h"
//
//#include <iostream>
//#include <string>
//#include <vector>
//#include <unordered_map>
//
//class SVMAssembler {
//private:
//	std::string text;
//	int index;
//	char cur;
//	bool hasError = false;
//
//	std::unordered_map<std::string, uint64_t> labels = {};
//
//	/* HashMap of mnemonics and their values in bytecode */
//	std::unordered_map<std::string, uint8_t> mnemonics = {
//		{"program_success", PROGRAM_SUCCESS},
//		{"program_fail", PROGRAM_FAIL},
//		{"pop", POP},
//
//		{"b_push", B_PUSH},
//		{"b_print", B_PRINT},
//
//		{"d_push", D_PUSH},
//		{"d_add", D_ADD},
//		{"d_sub", D_SUB},
//		{"d_mul", D_MUL},
//		{"d_div", D_DIV},
//		{"d_rem", D_REM},
//		{"d_cmp", D_CMP},
//		{"d_print", D_PRINT},
//
//		{"bz", BZ},
//		{"bltz", BLTZ},
//		{"blez", BLEZ},
//		{"bgtz", BGTZ},
//		{"bgez", BGEZ},
//
//		{"jmp", JMP},
//		{"jmpr", JMPR}
//	};
//
//	bool hasNext() {
//		return index + 1 < (int)text.size();
//	}
//
//	void getNext() {
//		if (!hasNext()) {
//			cur = '\0';
//		}
//		else {
//			cur = text.at(++index);
//		}
//	}
//
//	uint8_t translateMnemonic(std::string mnemonic) {
//		if (mnemonics.find(mnemonic) == mnemonics.end()) {
//			hasError = true;
//			std::cout << "Mnemonic not found: " + mnemonic << std::endl;
//			return -1;
//		}
//		return mnemonics.at(mnemonic);
//	}
//
//	uint64_t findLabel(std::string label) {
//		if (labels.find(label) == labels.end()) {
//			hasError = true;
//			std::cout << "Label not found: " + label << std::endl;
//			return -1;
//		}
//		return labels.at(label);
//	}
//
//public:
//	SVMAssembler(std::string text) {
//		this->text = text;
//		this->index = -1;
//		getNext();
//	}
//
//	std::vector<uint8_t> getBytecode() {
//		std::vector<uint8_t> bytecode;
//		std::cout << "Generating bytecode..." << std::endl;
//
//		while (cur != '\0') {
//			if (isspace(cur)) { // Skip whitespace
//				getNext();
//			}
//			else if (isalpha(cur)) { // Get mnemonic
//				std::string operation = "";
//
//				while (isalnum(cur) || cur == '_') {
//					operation += cur;
//					getNext();
//				}
//
//				if (operation.size() > 0 && operation.at(operation.size() - 1) == '_') {
//					bytecode.push_back(NOP); // byte corresponding to a label
//					labels.insert({operation.substr(operation.size()), bytecode.size()});
//					continue;
//				}
//
//				uint8_t byte = translateMnemonic(operation);
//				bytecode.push_back(byte);
//			}
//			else if (isdigit(cur) || cur == '-' || cur == '+') { // Get a number as double and store it as bytecode
//				std::string number;
//				int numDots = 0;
//				if (cur == '+' || cur == '-') {
//					number += cur;
//					getNext();
//				}
//
//				while (isdigit(cur) || cur == '.') {
//					if (cur == '.') {
//						if (numDots == 1) {
//							break;
//						}
//						numDots++;
//					}
//					number += cur;
//					getNext();
//				}
//
//				double value = std::stod(number);
//				// std::cout << "Number is: " << value << std::endl;
//
//				uint8_t* doubleAsBytes = (uint8_t*)&(value);
//				
//				for (int i = 0; i < 8; i++) {
//					bytecode.push_back(doubleAsBytes[i]);
//				}
//
//				// std::cout << "Number is: " << *(double*) doubleAsBytes << std::endl;
//			}
//			else if (cur == '"') { // Get a string and store it as bytecode
//				getNext();
//
//				while (cur != '"') {
//					bytecode.push_back((uint8_t) cur);
//					getNext();
//				}
//				getNext();
//
//			}
//			else if (cur == '\'') { // Encode char in bytecode
//				getNext();
//
//				bytecode.push_back((uint8_t) cur);
//				getNext();
//				if (cur != '\'') {
//					hasError = true;
//					std::cout << "Unterminated single quote" << std::endl;
//				}
//				getNext();
//			}
//			else {
//				hasError = true;
//				std::cout << "SVM Assembler Error: Invalid syntax." << std::endl;
//			}
//		}
//
//		if (hasError) {
//			std::cout << "Failed to generate bytecode." << std::endl;
//		}
//		else {
//			std::cout << "Successfully generated bytecode" << std::endl;
//		}
//
//		return bytecode;
//	}
//};
//
//