#pragma once

#include <cstdint>
#include <cmath>

#include "svm_definitions.h"
#include "svm_instructions.h"

void verify_signature(uint8_t* bytecode) {
	string signature = "";
	for (int i = 0; i < 6; i++) {
		signature += (char) bytecode[i];
	}

	if (signature != "joseph") {
		std::cout << "Corrupt file." << std::endl;
		throw "Corrupt file";
	}
}

void reset_vm() {
	svm.sp = svm.stack;
}

void stack_push(value data) {
	if (svm.pc == svm.pc + STACK_MAX) {
		throw "Stack Overflow Exception";
	}
	*svm.sp++ = data;
}

value stack_pop() {
	return *--svm.sp;
}

bool isEqual(value left, value right) {
	if (left.type != right.type) { 
		return false; 
	}
	else if (left.type == TYPE_STRING) {
		return *left.as.string == *right.as.string;
	}
	return left.as.number == right.as.number;
}

double cmp(value left, value right) {
	if (left.type != right.type) {
		throw "Invalid type operation";
	}
	else if (left.type == TYPE_NUMBER) {
		return left.as.number - right.as.number;
	}
	else if (left.type == TYPE_STRING) {
		return (double) (left.as.string->compare(*right.as.string));
	}
	else {
		throw "Invalid type operation";
	}
}


// Interpret bytecode
int run(uint8_t *bytecode) {
	reset_vm();

	// Check if bytecode is valid
	verify_signature(bytecode);

	// Set initial address for program counter
	svm.pc = bytecode + 6;

	int tBefore = 0;
	bool reportBenchmark = false;

	for (;;) {
		uint8_t instruction = *svm.pc++;
		
		switch (instruction) {
		case PROGRAM_SUCCESS: {
			int tAfter = duration_cast<milliseconds>(
				system_clock::now().time_since_epoch()
			).count();

			std::cout << "CPP Time Elapsed: " << test::benchmarkCpp << std::endl;
			if (reportBenchmark) {
				int benchmarkSpm = tAfter - tBefore;
				std::cout << "Program Benchmark Time: Elapsed: " << benchmarkSpm << std::endl;
			}
			
			return 0;
		}
		case PROGRAM_FAIL: return -1;

		case STORE_GLOBAL: {
			value data = stack_pop();
			value index = stack_pop();

			svm.global[(int) index.as.number] = data;
			break;
		}

		case LOAD_GLOBAL: {
			value index = stack_pop();
			stack_push(svm.global[(int) index.as.number]);
			break;
		}

		case PUSH: {
			value data;

			int datatype = *svm.pc++;
			data.type = static_cast<ValueType>(datatype);

			if (datatype == TYPE_NUMBER) {
				data.as.number = *(double*)svm.pc;
				svm.pc += 8;
			}
			else if (datatype == TYPE_STRING) {
				int stringLength = *svm.pc++;

				string str = "";
				for (int i = 0; i < stringLength; i++) {
					str += (char)*svm.pc++;
				}
				data.as.string = new string(str);
				svm.stringPool.insert(data.as.string);
			}
			else if (datatype == TYPE_BOOLEAN) {
				data.as.boolean = (bool)*svm.pc++;
			}
			else {
				std::cout << datatype << std::endl;
				throw "Unimplemented operation";
			}

			stack_push(data);
			break;
		}

		case POP: {
			stack_pop();
			break;
		}

		case COPY: {
			value temp =  *(svm.sp - 1);
			value copy;
			copy.type = temp.type;
			copy.as.object_ptr = temp.as.object_ptr;
			stack_push(copy);
			break;
		}

	
		case ADD: {
			value result;
			result.type = TYPE_NIL;
			result.as.boolean = false;

			value right = stack_pop();
			value left = stack_pop();


			if (left.type == right.type && left.type == TYPE_NUMBER) {
				result.type = TYPE_NUMBER;
				result.as.number = left.as.number + right.as.number;
			} else if (left.type == right.type && left.type == TYPE_STRING) {
				result.type = TYPE_STRING;
				string str = *(left.as.string) + *(right.as.string);

				string* newString = new string(str);
				result.as.string = newString;
				svm.stringPool.insert(newString);
			}
			else if (left.type == TYPE_NUMBER && right.type == TYPE_STRING) {
				result.type = TYPE_STRING;
				string str = std::to_string(left.as.number) + *(right.as.string);

				string* newString = new string(str);
				result.as.string = newString;
				svm.stringPool.insert(newString);
			}
			else if (left.type == TYPE_STRING && right.type == TYPE_NUMBER) {
				result.type = TYPE_STRING;
				string str = *(left.as.string) + std::to_string(right.as.number);
				
				string* newString = new string(str);
				result.as.string = newString;
				svm.stringPool.insert(newString);
			}
			else if (left.type == TYPE_BOOLEAN && right.type == TYPE_STRING) {
				result.type = TYPE_STRING;
				string str = (left.as.boolean ? "true" : "false") + *right.as.string;

				string* newString = new string(str);
				result.as.string = newString;
				svm.stringPool.insert(newString);
			}
			else if (left.type == TYPE_STRING && right.type == TYPE_BOOLEAN) {
				result.type = TYPE_STRING;
				string str = *left.as.string + (right.as.boolean ? "true" : "false");

				string* newString = new string(str);
				result.as.string = newString;
				svm.stringPool.insert(newString);
			}
			else {
				std::cout << "L:" << std::to_string(left.type) << " R: " << std::to_string(right.type) << std::endl;
				throw "Invalid operation";
			}
			stack_push(result);
			break;
		}

		case SUB: {
			value result;
			value right = stack_pop();
			value left = stack_pop();

			if (left.type == right.type && left.type == TYPE_NUMBER) {
				result.type = TYPE_NUMBER;
				result.as.number = left.as.number - right.as.number;
			}
			else {
				throw "Invalid operation";
			}
			stack_push(result);
			break;
		}

		case MUL: {
			value result;
			value right = stack_pop();
			value left = stack_pop();

			if (left.type == right.type && left.type == TYPE_NUMBER) {
				result.type = TYPE_NUMBER;
				result.as.number = left.as.number * right.as.number;
			}
			else {
				throw "Invalid operation";
			}
			stack_push(result);
			break;
		}

		case DIV: {
			value result;
			value right = stack_pop();
			value left = stack_pop();

			if (left.type == right.type && left.type == TYPE_NUMBER) {
				result.type = TYPE_NUMBER;
				result.as.number = left.as.number / right.as.number;
			}
			else {
				throw "Invalid operation";
			}
			stack_push(result);
			break;
		}

		case MOD: {
			value result;
			value right = stack_pop();
			value left = stack_pop();

			if (left.type == right.type && left.type == TYPE_NUMBER) {
				result.type = TYPE_NUMBER;
				result.as.number = std::fmod(left.as.number, right.as.number);
			}
			else {
				throw "Invalid operation";
			}
			stack_push(result);
			break;
		}

		case EQ: {
			value result;
			value right = stack_pop();
			value left = stack_pop();

			result.type = TYPE_BOOLEAN;
			result.as.boolean = isEqual(left, right);
			stack_push(result);
			break;
		}

		case NEQ: {
			value result;
			value right = stack_pop();
			value left = stack_pop();

			result.type = TYPE_BOOLEAN;
			result.as.boolean = !isEqual(left, right);
			stack_push(result);
			break;
		}

		case CMP: {
			value result;
			value right = stack_pop();
			value left = stack_pop();

			result.type = TYPE_NUMBER;
			result.as.number = cmp(left, right);
			stack_push(result);
			break;
		}

		/*case GOTO: {
			uint8_t* address = (uint8_t*) stack_pop().as.object_ptr;
			svm.pc = address;
			break;
		}*/

		case PRINT: {
			value data = stack_pop();

			if (data.type == TYPE_NUMBER) {
				std::cout << data.as.number;
			} else if (data.type == TYPE_STRING) {
				std::cout << *data.as.string;
			} else if (data.type == TYPE_BOOLEAN) {
				std::cout << (data.as.boolean != 0)? "true" : "false";
			} else if (data.type == TYPE_OBJECT) {
				std::cout << "[Object at " << data.as.object_ptr << "]";
			}
			else if (data.type == TYPE_NIL) {
				std::cout << "nil";
			}
			break;
		}

		case PRINTLN: {
			value data = stack_pop();

			if (data.type == TYPE_NUMBER) {
				std::cout << data.as.number << std::endl;
			}
			else if (data.type == TYPE_STRING) {
				std::cout << *data.as.string << std::endl;
			}
			else if (data.type == TYPE_BOOLEAN) {
				std::cout << ((data.as.boolean != 0) ? "true" : "false") << std::endl;
			}
			else if (data.type == TYPE_OBJECT) {
				std::cout << "[Object at " << data.as.object_ptr << "]" << std::endl;
			}
			else if (data.type == TYPE_NIL) {
				std::cout << "nil" << std::endl;
			}
			break;
		}

		case JUMP: {
			int newAddress = *(int*)svm.pc;
			// svm.pc += 4;
			svm.pc = bytecode + newAddress;
			break;
		}

		case JEZ: {
			value val = stack_pop();

			int newAddress = *(int*)svm.pc;
			svm.pc += 4;

			if (val.as.number == 0) {
				svm.pc = bytecode + newAddress;
			}
			break;
		}

		case JLTZ: {
			value val = stack_pop();

			int newAddress = *(int*)svm.pc;
			svm.pc += 4;

			if (val.as.number < 0) {
				svm.pc = bytecode + newAddress;
			}
			break;
		}

		case JGTZ: {
			value val = stack_pop();

			int newAddress = *(int*)svm.pc;
			svm.pc+= 4;

			if (val.as.number > 0) {
				svm.pc = bytecode + newAddress;
			}
			break;
		}

		case CALL: {
			value str = stack_pop();
			int ms = duration_cast<milliseconds>(
				system_clock::now().time_since_epoch()
			).count();

			svm.nativeFunctions[*str.as.string]();

			int endMs = duration_cast<milliseconds>(
				system_clock::now().time_since_epoch()
			).count();

			test::benchmarkCpp = endMs - ms;
			break;
		}

		case BENCHMARK: {
			reportBenchmark = true;
			tBefore = duration_cast<milliseconds>(
				system_clock::now().time_since_epoch()
			).count();
			break;
		}

		default:
			return -1;
		}
	}
	return -1;
}

