#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class SVMAssembler {
private:
	std::string text;
	int index;
	char cur;

	/* HashMap of mnemonics and their values in bytecode */
	std::unordered_map<std::string, uint8_t> mnemonics = {
		// Core
		{"pushi", 0},
		{"add", 1},
		{"sub", 2},
		{"mul", 3},
		{"div", 4},
		{"pop_res", 5},
		{"exit", 6},

		// Data Type Stack Operations (Load to stack)
		{"pushbool", 7},
		{"pushchar", 8},
		{"pushint", 9},
		{"pushfloat", 10},
		{"pushstr", 11},

		// Print from stack (pops size of reference)
		{"print", 12},
		{"printl", 13},
		{"printbool", 14},
		{"printchar", 15},
		{"printint", 16},
		{"printfloat", 17},
		{"printlong", 18},
		{"printstr", 19},


		// Allocate & Deallocate
		{"alloc", 20},
		{"dealloc", 21},

		{"storestr", 22},
	};

	bool hasNext() {
		return index + 1 < (int) text.size();
	}

	void getNext() {
		if (!hasNext()) {
			cur = '\0';
		}
		else {
			cur = text.at(++index);
		}
	}

	uint8_t translateMnemonic(std::string mnemonic) {
		try {
			return mnemonics[mnemonic];
		} catch (...) {
				throw "Mnemonic not found: " + mnemonic;
		}
		return -1;
	}

	// Converts integer to array of bytes
	void intToByteArr(int num, uint8_t* byteArray) {
		for (int i = 0; i < 4; i++) {
			byteArray[i] = (num >> (24 - 8 * i)) & 0xFF;
		}
	}

public:
	SVMAssembler(std::string text) {
		this->text = text;
		this->index = -1;
		getNext();
	}

	std::string getText() {
		return this->text;
	}

	std::unordered_map<std::string, uint8_t> getMapping() {
		return this->mnemonics;
	}

	std::vector<uint8_t> getBytecode() {
		std::vector<uint8_t> bytecode;
		std::cout << "Generating bytecode..." << std::endl;
		while (cur != '\0') {
			if (isspace(cur)) { // Skip whitespace
				getNext();
			}
			else if (isalpha(cur)) { // Get mnemonics
				std::string operation;

				while (isalnum(cur) || cur == '_') {
					operation += cur;
					getNext();
				}

				uint8_t byte = translateMnemonic(operation);
				bytecode.push_back(byte);
			}
			else if (isdigit(cur)) { // Get numbers and store it in bytecode
				std::string number;

				while (isdigit(cur)) {
					number += cur;
					getNext();
				}

				int num = stoi(number);

				uint8_t byteArr[4];
				intToByteArr(num, byteArr);
				for (uint8_t byte: byteArr) {
					bytecode.push_back(byte);
				}
			}
			else if (cur == '"') { // Get strings and convert it to bytecode with length at header
				getNext();

				int head = (int) bytecode.size();
				int len = 0;

				// Add characters to bytecode
				while (cur != '"') {
					bytecode.push_back((uint8_t) cur);
					len++;
					getNext();
				}
				getNext();

			}
			else if (cur == '\'') { // Encode char in bytecode
				getNext();

				bytecode.push_back((uint8_t) cur);
				getNext();

				if (cur != '\'') {
					throw "Unterminated char";
				}
				getNext();
			}
			else {
				std::cout << "Something went wrong" << std::endl;
			}
		}

		return bytecode;
	}
};


