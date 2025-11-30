#pragma once
#include <bitset>
#include <vector>
#include "Register.h"
#include "Code.h"
#include "SymbolTable.h"
namespace Loonguage{
	class Compiler;

	class BitStream
	{
		using Symbol = SymbolTable<std::string>::Symbol;
		void setSection(std::bitset<32>&, int, int, int);
		void setRegister(std::bitset<32>&, int, int, Register::Registers);
		void allocateString(std::vector<std::bitset<8>>&);
		SymbolTable<std::string> strTable;
		std::map<Symbol, int> strPosition;
    public:
        int codeBegin;
		std::vector<Code> codes;
		std::bitset<32> setCode(Code);
		void printTestBench(std::ostream&, std::bitset<32>, int, std::string);
		void generateTestBench(std::ostream&, std::string, int);
		void generateTestBenchString(std::ostream&, std::string);
		void generateMemory(std::vector<std::bitset<8>>&);
		BitStream(Compiler&);
		BitStream(std::istream&, bool&);
	};
}


