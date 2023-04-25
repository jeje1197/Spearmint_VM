#pragma once

/*
	The instruction set for the Spearmint Virtual Machine.


	Number Types: Only doubles (64-bit floating point numbers)
*/
typedef enum {
	PROGRAM_SUCCESS,
	PROGRAM_FAIL,

	NOP,
	POP,

	I_PUSH,
	I_ADD,
	I_SUB,
	I_MUL,
	I_DIV,
	I_REM,
	I_CMP,
	I_PRINT,
	I2F,

	F_PUSH,
	F_ADD,
	F_SUB,
	F_MUL,
	F_DIV,
	F_REM,
	F_CMP,
	F_PRINT,
	F2I,

	BZ,
	BLTZ,
	BGTZ,
	BLEZ,
	BGEZ,

	JMP,
	JMPR
} opcode;