#pragma once

#include <cstdint>
#include <cmath>

#include "svm_instructions.h"
#include "svm_definitions.h"

void reset_vm() {
	svm.sp = svm.stack;
}

void stack_push(svm_value value) {
	*svm.sp++ = value;
}

svm_value stack_pop() {
	return *--svm.sp;
}


// Interpret bytecode
int run(uint8_t *bytecode) {
	reset_vm();
	std::cout << "Virtual machine running.\n" << std::endl;

	// Set initial address for program counter
	svm.pc = bytecode;

	for (;;) {
		uint8_t instruction = *svm.pc++;
		
		switch (instruction) {
		case PROGRAM_SUCCESS:
			return 0;

		case PROGRAM_FAIL:
			return -1;

		case NOP: 
			break;

		case POP:
			stack_pop();
			break;

		case I_PUSH: {
			stack_push(*(svm_value*)svm.pc);
			svm.pc += 4;
			break;
		}

		case I_ADD: {
			svm_value result;
			result.i32 = stack_pop().i32 + stack_pop().i32;
			stack_push(result);
			break;
		}

		case I_SUB: {
			svm_value result;
			result.i32 = stack_pop().i32 - stack_pop().i32;
			stack_push(result);
			break;
		}

		case I_MUL: {
			svm_value result;
			result.i32 = stack_pop().i32 * stack_pop().i32;
			stack_push(result);
			break;
		}

		case I_DIV: {
			svm_value result;
			result.i32 = stack_pop().i32 / stack_pop().i32;
			stack_push(result);
			break;
		}

		case I_REM: {
			svm_value result;
			result.i32 = stack_pop().i32 % stack_pop().i32;
			stack_push(result);
			break;
		}

		case I_CMP: {
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
		}

		case I_PRINT: {
			std::cout << stack_pop().i32;
			break;
		}

		case I2F: {
			svm_value result;
			result.f32 = (float) stack_pop().i32;
			stack_push(result);
			break;
		}

		case F_PUSH: {
			stack_push(*(svm_value*)svm.pc);

			svm.pc += 4;
			break;
		}

		case F_ADD: {
			svm_value result;
			result.f32 = stack_pop().f32 + stack_pop().f32;
			stack_push(result);
			break;
		}

		case F_SUB: {
			svm_value result;
			result.f32 = stack_pop().f32 - stack_pop().f32;
			stack_push(result);
			break;
		}

		case F_MUL: {
			svm_value result;
			result.f32 = stack_pop().f32 * stack_pop().f32;
			stack_push(result);
			break;
		}

		case F_DIV: {
			svm_value result;
			result.f32 = stack_pop().f32 / stack_pop().f32;
			stack_push(result);
			break;
		}

		case F_REM: {
			svm_value result;
			result.f32 = fmod(stack_pop().f32, stack_pop().f32);
			stack_push(result);
			break;
		}

		case F_CMP: {
			float right = stack_pop().f32;
			float left = stack_pop().f32;

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
		}

		case F2I: {
			svm_value result;
			result.i32 = (int)stack_pop().f32;
			stack_push(result);
			break;
		}

		/*case JMP: {
			uint64_t value = stack_pop();
			double doubleValue = *(double*)&value;

			svm.pc = bytecode + (uint64_t)doubleValue;
			break;
		}

		case JMPR: {
			uint64_t value = stack_pop();
			double doubleValue = *(double*)&value;

			stack_push((uint64_t)svm.pc);
			svm.pc = bytecode + (uint64_t)doubleValue;
			break;
		}*/
		
		default:
			return -1;
		}
	}

	return -1;
}

