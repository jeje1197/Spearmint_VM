#pragma once

#include <cstdint>
#include <cmath>

#include "svm_definitions.h"
#include "svm_instructions.h"


void reset_vm() {
	svm.sp = svm.stack;
}

void stack_push(value data) {
	*svm.sp++ = data;
}

value stack_pop() {
	return *--svm.sp;
}


// Interpret bytecode
int run(uint8_t *bytecode) {
	reset_vm();
	std::cout << "Process running.\n" << std::endl;

	// Set initial address for program counter
	svm.pc = bytecode;

	for (;;) {
		uint8_t instruction = *svm.pc++;
		
		switch (instruction) {
		case PROGRAM_SUCCESS:
			return 0;

		case PROGRAM_FAIL:
			return -1;

		case PUSH: {
			value data;

			int datatype = *svm.pc++;
			data.type = static_cast<ValueType>(datatype);

			data.as.number = *(double*)svm.pc;
			svm.pc += 8;

			stack_push(data);
			break;
		}
			
		case POP:
			stack_pop();
			break;

		case ADD: {
			value result;
			value right = stack_pop();
			value left = stack_pop();


			if (left.type == right.type && left.type == TYPE_NUMBER) {
				result.type = TYPE_NUMBER;
				result.as.number = left.as.number + right.as.number;
			} else if (left.type == right.type && left.type == TYPE_STRING) {
				result.type = TYPE_STRING;
				*result.as.string = *(left.as.string) + *(right.as.string);
			}
			else {
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

		/*case CMP: {
			int right = stack_pop().i32;
			int left = stack_pop().i32;

			svm_value result;
			if (left < right) {
				result.i32 = -1;
			}
			else if (left > right) {
				result.i32 = 1;
			}
			else {
				result.i32 = 0;
			}
			stack_push(result);
			break;
		}*/

		case PRINT: {
			value data = stack_pop();

			if (data.type == TYPE_NUMBER) {
				std::cout << data.as.number;
			} else if (data.type == TYPE_STRING) {
				std::cout << data.as.string;
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
				std::cout << data.as.string << std::endl;
			}
			else if (data.type == TYPE_BOOLEAN) {
				std::cout << (data.as.boolean != 0) ? "true" : "false" << std::endl;
			}
			else if (data.type == TYPE_OBJECT) {
				std::cout << "[Object at " << data.as.object_ptr << "]" << std::endl;
			}
			else if (data.type == TYPE_NIL) {
				std::cout << "nil" << std::endl;
			}
			break;
		}

		default:
			return -1;
		}
	}
	return -1;
}

