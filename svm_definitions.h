#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>
#include <unordered_map>

#include "NativeFunctions.h"

#define GLOBAL_MAX 256
#define STACK_MAX 256
#define HEAP_MAX 100000

using std::string;
using std::unordered_set;
using std::unordered_map;

enum ValueType {
	TYPE_NUMBER = 0,
	TYPE_STRING = 1,
	TYPE_BOOLEAN = 2,
	TYPE_OBJECT = 3,
	TYPE_NIL = 4
};

typedef struct Value {
	uint8_t type;	// Runtime Type

	union {			// Runtime Data
		double number;
		string* string;
		void* object_ptr;
		bool boolean;
	} as;
} value;

typedef void(*NativeFunctionPtr)();

struct {
	uint8_t* pc;

	value global[GLOBAL_MAX];
	unordered_set<string*> stringPool;
	value stack[STACK_MAX];

	value* sp;

	unordered_map<string, NativeFunctionPtr> nativeFunctions = {
		{"test", (NativeFunctionPtr) &test::testCall}
	};

} svm;

