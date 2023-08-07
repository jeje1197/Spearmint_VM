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

//bool isEqual(value left, value right) {
//	if (left.type != right.type) { 
//		return false; 
//	}
//	else if (left.type == TYPE_STRING) {
//		return *left.as.string == *right.as.string;
//	}
//	return left.as.uint64 == right.as.uint64;
//}
//
//int cmp(value left, value right) {
//	if (left.type != right.type) {
//		throw "Invalid type operation";
//	}
//	else if (left.type == TYPE_NUMBER) {
//		return left.as.number - right.as.number;
//	}
//	else if (left.type == TYPE_STRING) {
//		return left.as.string->compare(*right.as.string);
//	}
//	else {
//		throw "Invalid type operation";
//	}
//}


// Interpret bytecode
int run(uint8_t *bytecode) {
	reset_vm();
	std::cout << "Process running.\n" << std::endl;

	// Set initial address for program counter
	svm.pc = bytecode;

	for (;;) {
		uint8_t instruction = *svm.pc++;
		
		switch (instruction) {
		case PROGRAM_SUCCESS: return 0;
		case PROGRAM_FAIL: return -1;

		case STORE_GLOBAL: {
			value data = stack_pop();
			value index = stack_pop();

			svm.global[index.integer] = data;
			break;
		}

		case LOAD_GLOBAL: {
			value index = stack_pop();
			stack_push(svm.global[index.integer]);
			break;
		}

		case I_PUSH: {
			value v;
			v.integer = *(int*)svm.pc;
			svm.pc += 4;

			stack_push(v);
			break;
		}

		case I_PRINT: {
			value v = stack_pop();
			std::cout << v.integer << std::endl;
			break;
		}

		/*case PUSH: {
			value data;

			int datatype = *svm.pc++;
			data.type = static_cast<ValueType>(datatype);

			data.as.number = *(double*)svm.pc;
			svm.pc += 8;

			stack_push(data);
			break;
		}*/

		case POP: {
			stack_pop();
			break;
		}

		/*case STORE_GLOBAL: {
			value data = stack_pop();
			int index = (int) stack_pop().as.number;

			stack_push(svm.global[index]);
			break;
		}*/

		/*case LOAD_GLOBAL: {
			int index = (int)stack_pop().as.number;
			stack_push(svm.global[index]);
			break;
		}*/

		/*case CALL: {
			svm.nativeFunctions["test"]();
			break;

		}
	
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

		case GOTO: {
			uint8_t* address = (uint8_t*) stack_pop().as.object_ptr;
			svm.pc = address;
			break;
		}

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
				std::cout << ((data.as.boolean != 0) ? "true" : "false") << std::endl;
			}
			else if (data.type == TYPE_OBJECT) {
				std::cout << "[Object at " << data.as.object_ptr << "]" << std::endl;
			}
			else if (data.type == TYPE_NIL) {
				std::cout << "nil" << std::endl;
			}
			break;
		}*/

		default:
			return -1;
		}
	}
	return -1;
}

