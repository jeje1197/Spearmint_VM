#pragma once

/*
	The instruction set for the Spearmint Virtual Machine.


	Number Types: Only doubles (64-bit floating point numbers)
	Strings Types: Characters are represented by size 1 strings
*/

typedef enum {
	PROGRAM_SUCCESS,
	PROGRAM_FAIL,

	STORE_GLOBAL,
	LOAD_GLOBAL,

	I_PUSH,
	POP,

	//BPUSH,

	//ADD,
	//SUB,
	//MUL,
	//DIV,
	//MOD,

	I_PRINT,
} opcode;