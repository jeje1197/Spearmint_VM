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
	PUSH_NIL,
	POP,

	STORE_GLOBAL,
	LOAD_GLOBAL,

	CALL,

	ADD,
	SUB,
	MUL,
	DIV,
	MOD,

	EQ,
	NEQ,
	CMP,

	GOTO,

	LT,
	LTE,
	GT,
	GTE,

	

	PRINT,
	PRINTLN
} opcode;