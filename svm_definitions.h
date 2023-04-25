#pragma once

#include <cstdint>

#define STACK_MAX 256
#define HEAP_MAX 100000

typedef union {
	int i32;
	float f32;
} svm_value;

struct {
	uint8_t* pc;

	uint8_t heap[HEAP_MAX];

	svm_value stack[STACK_MAX];

	svm_value* sp;

	svm_value static_vars[10];

	svm_value* sv;
} svm;

