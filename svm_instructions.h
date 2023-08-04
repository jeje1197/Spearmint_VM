#pragma once

/*
	The instruction set for the Spearmint Virtual Machine.


	Number Types: Only doubles (64-bit floating point numbers)
	Strings Types: Characters are represented by size 1 strings
*/

typedef enum {
	PROGRAM_SUCCESS,
	PROGRAM_FAIL,

	PUSH,
	POP,

	ADD,
	SUB,
	MUL,
	DIV,
	MOD,


	CMP,

	PRINT,
	PRINTLN
} opcode;