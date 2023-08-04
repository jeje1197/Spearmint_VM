#pragma once

#include <cstdint>
#include <string>

#define STACK_MAX 256
#define HEAP_MAX 100000

using std::string;

enum ValueType{
	TYPE_NUMBER = 0,
	TYPE_STRING = 1,
	TYPE_BOOLEAN = 2,
	TYPE_OBJECT = 3,
	TYPE_NIL = 4
};

typedef struct Value {
	ValueType type;

	union {
		uint64_t uint64;
		double number;
		string* string;
		void* object_ptr;
		bool boolean;
	} as;
} value;


struct {
	uint8_t* pc;

	value stack[STACK_MAX];

	value* sp;
} svm;

