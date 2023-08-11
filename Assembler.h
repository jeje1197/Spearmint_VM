#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "svm_instructions.h"
#include "AsmToken.h"
#include "Mnemonics.h"

using std::string;
using std::vector;

class SvmAssembler {
private:
	string text;
	int index;
	char cur;
	bool haserror = false;

	unordered_map<string, int> offset;

	bool hasnext() {
		return index + 1 < (int)text.size();
	}

	void getnext() {
		if (!hasnext()) {
			cur = '\0';
		}
		else {
			cur = text.at(++index);
		}
	}

public:
	SvmAssembler(string text) {
		this->text = text;
		this->index = -1;
		getnext();
	}

	vector<AsmToken> getTokens() {
		vector<AsmToken> tokens;

		while (cur != '\0') {
			if (isspace(cur)) { // skip whitespace
				getnext();
			}
			else if (cur == '#') {
				getnext();
				while (cur != '\n') {
					getnext();
				}
			}
			else if (isalpha(cur)) { // scan instructions
				string operation = "";

				while (isalnum(cur) || cur == '_') {
					operation += cur;
					getnext();
				}

				bool isLabel = false;
				if (cur == ':') {
					getnext();
					isLabel = true;
				}

				AsmToken token;
				token.type = isLabel ? ASM_LABEL : ASM_INSTRUCTION;
				token.value.string = new string(operation);
				tokens.push_back(token);
			}
			else if (cur == '@') { // label reference
				getnext();
				string operation = "";

				while (isalnum(cur) || cur == '_') {
					operation += cur;
					getnext();
				}

				AsmToken token;
				token.type = ASM_LABEL_REFERENCE;
				token.value.string = new string(operation);
				tokens.push_back(token);
			}
			else if (isdigit(cur) || cur == '-' || cur == '+') { // get a number as double and store it as bytecode
				string number;
				int numdots = 0;
				if (cur == '+' || cur == '-') {
					number += cur;
					getnext();
				}

				while (isdigit(cur) || cur == '.') {
					if (cur == '.') {
						if (numdots == 1) {
							break;
						}
						numdots++;
					}
					number += cur;
					getnext();
				}

				AsmToken token;
				token.type = ASM_NUMBER;
				token.value.value = std::stod(number);
				tokens.push_back(token);
			}
			else if (cur == '"') { // get a string and store it
				getnext();

				string str_value;
				while (cur != '"' && cur != '\0') {
					str_value += cur;
					getnext();
				}
				getnext();

				AsmToken token;
				token.type = ASM_STRING;
				token.value.string = new string(str_value);

				tokens.push_back(token);
			}
			else {
				haserror = true;
				std::cout << "svm assembler error: invalid syntax." << std::endl;
			}
		}

		if (haserror) {
			std::cout << "Failed to generate bytecode." << std::endl;
			tokens.clear();
		}

		return tokens;
	}

	vector<uint8_t> parse(vector<AsmToken> tokens) {
		vector<uint8_t> bytecode;
		unordered_map<string, int> labels;
		unordered_map<string, int> unresolvedLabelReferences;
		int i = 0;

		char signature[7] = "joseph";
		bytecode.insert(bytecode.end(), signature, signature + 6);

		while (i < (int)tokens.size()) {
			AsmToken cur = tokens.at(i++);
			if (cur.type == ASM_INSTRUCTION) {
				//std::cout << "INSTRUCTION" << std::endl;
				if (mnemonics.find(*cur.value.string) == mnemonics.end()) {
					throw "Instruction not found";
				}
				uint8_t byte = mnemonics.at(*cur.value.string);
				bytecode.push_back(byte);
			}
			else if (cur.type == ASM_LABEL) {
				labels[*cur.value.string] = (int)bytecode.size();
			}
			else if (cur.type == ASM_LABEL_REFERENCE) {
				string labelName = *cur.value.string;

				int offsetFromStartOfBytecode = 0;
				if (labels.find(labelName) == labels.end()) {
					unresolvedLabelReferences[labelName] = (int)bytecode.size();
				}
				else {
					offsetFromStartOfBytecode = labels.at(labelName);
				}

				bytecode.insert(bytecode.end(), static_cast<uint8_t*>(static_cast<void*>(&offsetFromStartOfBytecode)),
					(uint8_t*)&offsetFromStartOfBytecode + 4);
			}
			else if (cur.type == ASM_NUMBER) {
				//std::cout << "NUMBER" << std::endl;
				bytecode.push_back(0x0); // Type flag
				bytecode.insert(bytecode.end(), static_cast<uint8_t*>(static_cast<void*>(&cur.value.value)),
					(uint8_t*)&cur.value.value + 8);
			}
			else if (cur.type == ASM_STRING) {
				//std::cout << "STRING" << std::endl;
				bytecode.push_back(0x1); // Type flag
				bytecode.push_back((uint8_t)cur.value.string->length());
				for (auto c : *cur.value.string) {
					//std::cout << c << std::endl;
					bytecode.push_back(c);
				}
			}
			else {
				throw "Unimplemented";
			}
		}

		// Resolve unresolved
		for (auto unresolvedLabel : unresolvedLabelReferences) {
			int byteOffsetToReplace = (int)unresolvedLabel.second;
			uint8_t* bytes = (uint8_t*) &labels.at(unresolvedLabel.first);

			bytecode.at(byteOffsetToReplace) = bytes[0];
			bytecode.at(byteOffsetToReplace + 1) = bytes[1];
			bytecode.at(byteOffsetToReplace + 2) = bytes[2];
			bytecode.at(byteOffsetToReplace + 3) = bytes[3];
		}

		return bytecode;
	}

	vector<uint8_t> getBytecode() {
		return parse(getTokens());
	}
};

