#pragma once

#include <cstdint>
#include <cmath>

#include "svm_instructions.h"


#define STACK_MAX 256
#define HEAP_MAX 100000

struct {
	/* Program counter: 8-bit */
	uint8_t* pc;

	/* Fixed size heap */
	uint8_t heap[HEAP_MAX];

	/* Fixed size stack */
	uint64_t stack[STACK_MAX];

	/* Stack pointer */
	uint64_t* sp;
} svm;

/* Functions */
void reset_vm() {
	svm.sp = svm.stack;
}

void stack_push(uint64_t value) {
	*svm.sp++ = value;
}

uint64_t stack_pop() {
	return *--svm.sp;
}

/****************************************************/
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

		case POP:
			stack_pop();
			break;

		case B_PUSH: {
			uint64_t value = *svm.pc++;
			stack_push(value);
			break;
		}
			
		case D_PUSH: {
			uint64_t value = *(uint64_t*) svm.pc;
			svm.pc += 8;
			
			stack_push(value);
			break;
		}

		case D_ADD: {
			uint64_t right = stack_pop();
			uint64_t left = stack_pop();

			double rightValue = *(double*) &right;
			double leftValue = *(double*) &left;

			double result = leftValue + rightValue;

			stack_push(*(uint64_t*) &result);
			break;
		}

		case D_SUB: {
			uint64_t right = stack_pop();
			uint64_t left = stack_pop();

			double rightValue = *(double*)&right;
			double leftValue = *(double*)&left;

			double result = leftValue - rightValue;

			stack_push(*(uint64_t*)&result);
			break;
		}

		case D_MUL: {
			uint64_t right = stack_pop();
			uint64_t left = stack_pop();

			double rightValue = *(double*)&right;
			double leftValue = *(double*)&left;

			double result = leftValue * rightValue;

			stack_push(*(uint64_t*)&result);
			break;
		}

		case D_DIV: {
			uint64_t right = stack_pop();
			uint64_t left = stack_pop();

			double rightValue = *(double*)&right;
			double leftValue = *(double*)&left;

			double result = leftValue / rightValue;

			stack_push(*(uint64_t*)&result);
			break;
		}

		case D_REM: {
			uint64_t right = stack_pop();
			uint64_t left = stack_pop();

			double rightValue = *(double*)&right;
			double leftValue = *(double*)&left;

			double result = fmod(leftValue, rightValue);

			stack_push(*(uint64_t*)&result);
			break;
		}

		case D_CMP: {
			uint64_t right = stack_pop();
			uint64_t left = stack_pop();

			double rightValue = *(double*)&right;
			double leftValue = *(double*)&left;

			double result = 0;
			if (leftValue > rightValue) {
				result = 1;
			}
			else if (leftValue < rightValue) {
				result = -1;
			}

			stack_push(*(uint64_t*)&result);
			break;
		}

		case B_PRINT: {
			std::cout << (int) stack_pop();
			break;
		}

		case D_PRINT: {
			uint64_t value = stack_pop();
			std::cout << *(double*) &value;
			break;
		}
		
		default:
			return -1;
		}
	}

	return -1;
}

