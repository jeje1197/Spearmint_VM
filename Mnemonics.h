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
	{"COPY", 6},

	{"ADD", 7},
	{"SUB", 8},
	{"MUL", 9},
	{"DIV", 10},
	{"MOD", 11},

	{"EQ", 12},
	{"NEQ", 13},
	{"CMP", 14},

	{"PRINT", 15},
	{"PRINTLN", 16},

	{"JUMP", 17},
	{"JEZ", 18},
	{"JLTZ", 19},
	{"JGTZ", 20},

	{"CALL", 21},
	{"BENCHMARK", 22}
};