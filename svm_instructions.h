#pragma once

/*
	The instruction set for the Spearmint Virtual Machine.


	Number Types: Only doubles (64-bit floating point numbers)
*/
typedef enum {
	PROGRAM_SUCCESS,
	PROGRAM_FAIL,

	POP,

	B_PUSH,

	D_PUSH,
	D_ADD,
	D_SUB,
	D_MUL,
	D_DIV,
	D_REM,
	D_CMP,

	B_PRINT,
	D_PRINT,



} opcode;