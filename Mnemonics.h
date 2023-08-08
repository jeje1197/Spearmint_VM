#include <string>
#include <cstdint>
#include <unordered_map>

using std::string;
using std::unordered_map;

unordered_map<string, uint8_t> mnemonics = {
	{"PROGRAM_SUCCESS", 0},
	{"PROGRAM_FAIL", 1},

	{"STORE_GLOBAL", 2},
	{"LOAD_GLOBAL", 3},

	{"PUSH", 4},
	{"POP", 5},

	{"ADD", 6},
	{"SUB", 7},
	{"MUL", 8},
	{"DIV", 9},
	{"MOD", 10},

	{"EQ", 11},
	{"NEQ", 12},
	{"CMP", 13},

	{"PRINT", 14},
	{"PRINTLN", 15},

	{"CALL", 16}
};