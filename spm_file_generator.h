#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdint>

using std::vector;
using std::set;
using std::string;

class SpmFileGenerator {
private:
	vector<uint8_t> bytecode;

	uint8_t* fileSignature =  new uint8_t[6] { 0x6A, 0x6F, 0x73, 0x65, 0x70, 0x68 }; // joseph
	uint8_t* version = new uint8_t[2] { 0x1, 0x0 }; // 1.0

	uint32_t  constantPoolCount = 0;
	vector<uint8_t> constantPoolEntries;

	uint32_t globalsCount = 0;
	vector<uint8_t>  globalEntries;

	void addByte(uint8_t byte) {
		bytecode.push_back(byte);
	}

	void addBytes(vector<uint8_t> bytes) {
		bytecode.insert(std::end(bytecode), std::begin(bytes), std::end(bytes));
	}

	void addString(string str) {
		addByte(str.length()); // Add length in String header

		for (auto c : str) { // Add characters as bytes
			addByte(c);
		}
	}

public:

	void setFileSignature(uint8_t fileSignature[6]) {
		this->fileSignature = fileSignature;
	}

	void setVersion(uint8_t version[2]) {
		this->version = version;
	}

	void setConstantPoolCount(uint32_t constantPoolCount) {
		this->constantPoolCount = constantPoolCount;
	}

	void setConstantPool(vector<uint8_t> constantPoolEntries) {
		this->constantPoolEntries = constantPoolEntries;
	}

	/*void setPrototypeCount(uint32_t prototypeCount) {
		this->prototypeCount = prototypeCount;
	}

	void setPrototypePool(vector<uint8_t> prototypeEntries) {
		this->prototypeEntries = prototypeEntries;
	}

	void setFunctionCount(uint32_t functionCount) {
		this->functionCount = functionCount;
	}

	void setFunctionEntries(vector<uint8_t> functionEntries) {
		this->functionEntries = functionEntries;
	}*/

	vector<uint8_t> generateSpmFile() {
		vector<uint8_t> bytecode;

		bytecode.insert(bytecode.end(), fileSignature, fileSignature + 6);
		bytecode.insert(bytecode.end(), version, version + 2);

		// Constant Pool Data
		bytecode.insert(bytecode.end(), static_cast<uint8_t*>(static_cast<void*>(&constantPoolCount)), 
			(uint8_t*) &constantPoolCount + 4);
		
		if (constantPoolCount > 0) {
			bytecode.insert(bytecode.end(), constantPoolEntries.begin(), constantPoolEntries.end());
		}

		//// Prototype Data
		//bytecode.insert(bytecode.end(), static_cast<uint8_t*>(static_cast<void*>(&prototypeCount)),
		//	(uint8_t*) &prototypeCount + 4);

		//if (prototypeCount > 0) {
		//	bytecode.insert(bytecode.end(), prototypeEntries.begin(), prototypeEntries.end());
		//}

		//// Function Data
		//bytecode.insert(bytecode.end(), static_cast<uint8_t*>(static_cast<void*>(&functionCount)),
		//	(uint8_t*) &functionCount + 4);

		//if (functionCount > 0) {
		//	bytecode.insert(bytecode.end(), functionEntries.begin(), functionEntries.end());
		//}

		return bytecode;
	}

	void disassembleSpmBytecode(vector <uint8_t> v) {
		string content;

		// Grab
		content = "--- Spearmint Bytecode ---\n";

		uint8_t* bytecode = v.data();

		content += "File Signature: ";
		for (int i = 0; i < 6; i++) {
			content += string(1, (char)bytecode[i]);
		}


		content += "\nVersion: " + std::to_string(bytecode[6]) + "." + std::to_string(bytecode[7]);

		uint8_t* index = bytecode+8;

		uint32_t constantPoolCount = *(uint32_t*)index;
		index += 4;
		content += "\n\nConstant Pool (" + std::to_string(constantPoolCount) + ")";

		uint32_t numberParsed = 0;
		for (int i = 0; i < constantPoolCount; i++) {
			uint8_t datatype = *(index++);
			

		}
		
		uint32_t prototypeCount = *(uint32_t*)index;
		index += 4;
		content += "\nPrototypes (" + std::to_string(prototypeCount) + ")";

		uint32_t functionCount = *(uint32_t*)index;
		index += 4;
		content += "\nFunctions (" + std::to_string(functionCount) + ")";

		std::cout << content << std::endl;
	}


};