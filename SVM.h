#pragma once

#include <stdio.h>
#include <cstdint>

#define STACK_MAX 256

struct {
	/* Program counter */
	uint8_t * pc;

	/* Fixed size stack */
	uint32_t stack[STACK_MAX];
	uint32_t* sp;

	/* A single register containing the result */
	uint32_t result;
} svm;

typedef enum {
	OP_PUSHI,
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_POP_RES,
	OP_DONE,

	OP_PRINT,
	OP_PRINTL
} opcode;

typedef enum interpret_result {
	SUCCESS,
	ERROR_DIVISION_BY_ZERO,
	ERROR_UNKNOWN_OPCODE
} interpret_result;

void reset_vm() {
	std::cout << "Virtual machine resetting." << std::endl;
	svm.sp = svm.stack;
}

void stack_push(uint32_t value) {
	*svm.sp = value;
	svm.sp++;
}

uint32_t stack_pop() {
	svm.sp--;
	return *svm.sp;
}

interpret_result run(uint8_t *bytecode) {
	reset_vm();
	std::cout << "Virtual machine running." << std::endl;

	// Set initial address for program counter
	svm.pc = bytecode;

	for (;;) {
		// Fetch instruction
		uint32_t instruction = *svm.pc++;

		switch (instruction) {
		case OP_PUSHI: {
			uint32_t immediate = *svm.pc++;
			stack_push(immediate);
			break;
		}
			

		case OP_ADD: {
			uint32_t arg_right = stack_pop();
			uint32_t arg_left = stack_pop();

			uint32_t res = arg_left + arg_right;
			stack_push(res);
			break;
		}

		case OP_SUB: {
			uint32_t arg_right = stack_pop();
			uint32_t arg_left = stack_pop();

			uint32_t res = arg_left - arg_right;
			stack_push(res);
			break;
		}
			
		case OP_MUL: {
			uint32_t arg_right = stack_pop();
			uint32_t arg_left = stack_pop();

			uint32_t res = arg_left * arg_right;
			stack_push(res);
			break;
		}
			

		case OP_DIV: {
			uint32_t arg_right = stack_pop();
			if (arg_right == 0) {
				return ERROR_DIVISION_BY_ZERO;
			}

			uint32_t arg_left = stack_pop();
			uint32_t res = arg_left / arg_right;
			stack_push(res);
			break;
		}

		case OP_POP_RES: {
			uint32_t res = stack_pop();
			svm.result = res;
			break;
		}

		case OP_DONE: {
			return SUCCESS;
		}
			
		case OP_PRINT: {
			uint32_t num = stack_pop();
			std::cout << num;
			break;
		}
			
		case OP_PRINTL: {
			uint32_t num = stack_pop();
			std::cout << num << std::endl;
			break;
		}

		default:
			return ERROR_UNKNOWN_OPCODE;
		}
	}

	return SUCCESS;
}

