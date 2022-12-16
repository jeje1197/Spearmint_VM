#pragma once

#include <cstdint>

#define STACK_MAX 256
#define HEAP_MAX 100000

struct {
	/* Program counter: 8-bit */
	uint8_t* pc;

	/* Fixed size heap */
	uint8_t heap[HEAP_MAX];

	/* Fixed size stack */
	uint64_t stack[STACK_MAX];
	uint64_t* sp;

	uint8_t* fp;

	/* A single register containing the result */
	uint64_t result;
} svm;

typedef enum {
	// Core Operations
	OP_PUSHI,
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_POP_RES,
	OP_DONE,

	// Extra Operations
	OP_PUSHBOOL,
	OP_PUSHCHAR,
	OP_PUSHINT,
	OP_PUSHFLOAT,
	OP_PUSHSTRING,

	OP_PRINT,
	OP_PRINTL,
	OP_PRINTBOOL,
	OP_PRINTCHAR,
	OP_PRINTINT,
	OP_PRINTFLOAT,
	OP_PRINTLONG,
	OP_PRINTSTR,

	OP_ALLOC,
	OP_DEALLOC,

	OP_STORESTR,
	OP_PUSHLONG

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

/* Stack helpers */

void stack_push(uint64_t value) {
	*svm.sp = value;
	svm.sp++;
}

uint64_t stack_pop() {
	svm.sp--;
	return *svm.sp;
}

// Converts integer to array of bytes
void intToByteArr(int num, uint8_t* byteArray) {
	byteArray[0] = (num >> 24) & 0xFF;
	byteArray[1] = (num >> 16) & 0xFF;
	byteArray[2] = (num >> 8) & 0xFF;
	byteArray[3] = num & 0xFF;
}

// Converts array of bytes to int
int byteArrToInt(uint8_t* byteArray) {
	int num = 0;
	num = (num << 0) | byteArray[0];
	num = (num << 8) | byteArray[1];
	num = (num << 16) | byteArray[2];
	num = (num << 24) | byteArray[3];
	return num;
}

// Converts long to array of bytes
void longToByteArr(uint64_t num, uint8_t* byteArray) {
	byteArray[0] = (num >> 56) & 0xFF;
	byteArray[1] = (num >> 48) & 0xFF;
	byteArray[2] = (num >> 40) & 0xFF;
	byteArray[3] = (num >> 32) & 0xFF;
	byteArray[4] = (num >> 24) & 0xFF;
	byteArray[5] = (num >> 16) & 0xFF;
	byteArray[6] = (num >> 8) & 0xFF;
	byteArray[7] = num & 0xFF;
}

// Converts array of bytes to long
uint64_t byteArrToLong(uint8_t* byteArray) {
	uint64_t num = 0;
	num = (num << 0) | byteArray[0];
	num = (num << 8) | byteArray[1];
	num = (num << 16) | byteArray[2];
	num = (num << 24) | byteArray[3];
	num = (num << 32) | byteArray[4];
	num = (num << 40) | byteArray[5];
	num = (num << 48) | byteArray[6];
	num = (num << 56) | byteArray[7];
	return num;
}

/* Heap helpers (Dynamic memory functions) */
// Searches for a free contiguous memory block (of size 'bytesNeeded')
// If found, returns memory address to free location.
// If no block found, throws an out of memory error
uint8_t* heap_allocate(int bytesNeeded) {
	for (int i = 0; i < HEAP_MAX; i++) {
		uint8_t* blockAddress = (svm.heap + i);
		int bytesAvailable = 0;
		while (svm.heap[i] == 0) {
			bytesAvailable++;
			i++;

			if (bytesAvailable == bytesNeeded) {
				std::cout << "Allocated: " << bytesNeeded << "bytes at address:" <<
					(uint64_t)blockAddress << std::endl;
				return blockAddress;
			}
		}
	}

	throw "Out of memory error.";
	return nullptr;
}

// Deallocates contiguous block of memory (of size 'bytes') at specified 'address'
void heap_deallocate(uint8_t* address, int bytes) {
	for (int i = 0; i < bytes; i++) {
		address[i] = '\0';
	}
}


/****************************************************/
// Interpret bytecode
interpret_result run(uint8_t *bytecode) {
	reset_vm();
	std::cout << "Virtual machine running." << std::endl;

	// Set initial address for program counter
	svm.pc = bytecode;

	for (;;) {
		// Fetch instruction
		uint8_t instruction = *svm.pc++;
		

		switch (instruction) {
		case OP_PUSHI: {
			uint64_t immediate = *svm.pc++;
			stack_push(immediate);
			break;
		}

		case OP_ADD: {
			uint64_t arg_right = stack_pop();
			uint64_t arg_left = stack_pop();

			uint64_t res = arg_left + arg_right;
			stack_push(res);
			break;
		}

		case OP_SUB: {
			uint64_t arg_right = stack_pop();
			uint64_t arg_left = stack_pop();

			uint64_t res = arg_left - arg_right;
			stack_push(res);
			break;
		}
			
		case OP_MUL: {
			uint64_t arg_right = stack_pop();
			uint64_t arg_left = stack_pop();

			uint64_t res = arg_left * arg_right;
			stack_push(res);
			break;
		}

		case OP_DIV: {
			uint64_t arg_right = stack_pop();
			if (arg_right == 0) {
				return ERROR_DIVISION_BY_ZERO;
			}

			uint64_t arg_left = stack_pop();
			uint64_t res = arg_left / arg_right;
			stack_push(res);
			break;
		}

		case OP_POP_RES: {
			uint64_t res = stack_pop();
			svm.result = res;
			break;
		}

		case OP_DONE: {
			return SUCCESS;
		}


		/* Extra */
		case OP_PUSHBOOL: {
			uint64_t byte = *svm.pc++;
			stack_push(byte);
			break;
		}

		case OP_PUSHCHAR: {
			uint64_t byte = *svm.pc++;
			stack_push(byte);
			break;
		}

		case OP_PUSHINT: {
			stack_push(byteArrToInt(svm.pc));
			svm.pc += 4;
			break;
		}

		case OP_PUSHLONG: {
			stack_push(byteArrToLong(svm.pc));
			svm.pc += 8;
			break;
		}

			
		case OP_PRINT: {
			uint64_t num = stack_pop();
			std::cout << num;
			break;
		}
			
		case OP_PRINTL: {
			std::cout << std::endl;
			break;
		}

		case OP_PRINTCHAR: {
			char c = (char) stack_pop();
			std::cout << c;
			break;
		}

		case OP_PRINTINT: {
			int num = (int) stack_pop();
			std::cout << num;
			break;
		}

		case OP_PRINTLONG: {
			uint64_t num = (uint64_t) stack_pop();
			std::cout << num;
			break;
		}

		case OP_PRINTSTR: {
			uint8_t* address = (uint8_t*) stack_pop();

			int strLen = byteArrToInt(address);
			for (int i = 0; i < strLen; i++) {
				std::cout << (char) address[4 + i];
			}
			break;
		}

		case OP_ALLOC: {
			// Read next int as amount of space to allocate
			int bytesNeeded = stack_pop();

			// Allocate space and store address on stack
			uint8_t* newAddress = heap_allocate(bytesNeeded);
			stack_push((uint64_t) newAddress);
			break;
		}

		case OP_DEALLOC: {
			break;
		}

		case OP_STORESTR: {
			// Read string length from top of stack
			int strlen = stack_pop();

			// Read address from top of stack
			uint8_t* address = (uint8_t*) stack_pop();

			// Store int (4 bytes) at address
			intToByteArr(strlen, address);

			//std::cout << "sstr len: " << strlen << std::endl;
			// Store String at address
			for (int i = 0; i < strlen; i++) {
				address[4 + i] = *svm.pc++;
			}

			// Push address to stack
			stack_push((uint64_t) address);
			break;
		}

		default:
			std::cout << "Exited on pc: " << (uint8_t) instruction << std::endl;
			return ERROR_UNKNOWN_OPCODE;
		}
	}

	return SUCCESS;
}

