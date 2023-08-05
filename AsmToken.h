#pragma once

#include <string>

using std::string;

enum AsmTokenType {
	ASM_INSTRUCTION,
	ASM_IDENTIFIER,
	
	ASM_NUMBER, ASM_STRING, ASM_BOOLEAN,
};

typedef struct {
	AsmTokenType type;
	union {
		double value;
		string* string;
		bool boolean;
	} value;
} AsmToken;