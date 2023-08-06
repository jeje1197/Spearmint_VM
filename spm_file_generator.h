#pragma once

#include <string>
#include <vector>
#include <set>
#include <cstdint>
#include <iostream>

using std::vector;
using std::set;
using std::string;

class SpmFileGenerator {
private:
	vector<uint8_t> bytecode;

	uint8_t* fileSignature =  new uint8_t[6] { 0x6A, 0x6F, 0x73, 0x65, 0x70, 0x68 }; // joseph
	uint8_t* version = new uint8_t[2] { 0x1, 0x0 }; // 1.0

	uint32_t  constantPoolCount = 0;
	uint8_t* constantPoolEntries;

	uint32_t prototypeCount = 0;
	uint8_t* prototypeEntries;

	uint32_t functionCount = 0;
	uint8_t*  functionEntries;

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

	void setConstantPool(uint8_t constantPoolEntries[]) {
		this->constantPoolEntries = constantPoolEntries;
	}

	void setPrototypeCount(uint32_t prototypeCount) {
		this->prototypeCount = prototypeCount;
	}

	void setPrototypePool(uint8_t prototypeEntries[]) {
		this->prototypeEntries = prototypeEntries;
	}

	void setFunctionCount(uint32_t functionCount) {
		this->functionCount = functionCount;
	}

	void setFunctionEntries(uint8_t functionEntries[]) {
		this->functionEntries = functionEntries;
	}

	void generateSpmFile() {
		vector<uint8_t> bytecode;

		bytecode.insert(bytecode.end(), fileSignature, fileSignature + 6);
		bytecode.insert(bytecode.end(), version, version + 2);


		/*bytecode.insert(bytecode.end(), constantPoolCount, constantPool + 6);
		bytecode.insert(bytecode.end(), version, version + 2);*/

		std::cout << "Bytes:" << bytecode.data();
	}
};