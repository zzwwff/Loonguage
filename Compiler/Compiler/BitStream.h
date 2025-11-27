#pragma once
#include <bitset>
#include <vector>
#include "Register.h"
#include "Code.h"
namespace Loonguage{
	class Compiler;

	class BitStream
	{
		void setSection(std::bitset<32>&, int, int, int);
		void setRegister(std::bitset<32>&, int, int, Register::Registers);
    public:
        int codeBegin;
		std::vector<std::bitset<8>> memory;
		std::vector<Code> codes;
		std::vector<std::bitset<8>> bits;
		std::bitset<32> setCode(Code);
		void generateTestBench(std::ostream&, std::string, int);
		BitStream(Compiler&);
		BitStream(std::istream&, bool&);
	};
}


