#pragma once

#include <iostream>
#include <chrono>

// ...

using namespace std::chrono;

namespace test {
	int benchmarkCpp = 0;
	void testCall(int a) {
		std::cout << "This code was called from C." << std::endl;
	}

	void loop(int a) {
		int i = 0;
		while (i < 10000) {
			std::cout << i << std::endl;
			i = i + 1;
		}
	}
}
