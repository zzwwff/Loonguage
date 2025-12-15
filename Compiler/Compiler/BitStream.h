#pragma once
#include <bitset>
#include <vector>
#include "Register.h"
#include "Code.h"
#include "SymbolTable.h"
#include <iostream>
#include <windows.h>

namespace Loonguage{
	class Compiler;

	class BitStream
	{
		using Symbol = SymbolTable<std::string>::Symbol;
		void setSection(std::bitset<32>&, int, int, int);
		void setRegister(std::bitset<32>&, int, int, Register::Registers);
		void allocateString(std::vector<std::bitset<8>>&, int);
		SymbolTable<std::string> strTable;
		std::map<Symbol, int> strPosition;
		int size;
        std::string configure_serial_port(HANDLE); //for USB configuration
        std::string writeUSBWord(HANDLE, std::bitset<8>);
    public:
        int stringBegin = 0;
        int stringEnd = 0;
		std::vector<Code> codes;
		std::bitset<32> setCode(Code);
		void printTestBench(std::ostream&, std::bitset<32>, int, std::string);
		void generateTestBench(std::ostream&, std::string, int);
		void generateTestBenchString(std::ostream&, std::string);
		void generateMemory(std::vector<std::bitset<8>>&);
		void generateCoe(std::ostream&);
        std::string writeUSB(wchar_t*, int);
		BitStream(Compiler&);
		BitStream(std::istream&, bool&, int);

	};
}


