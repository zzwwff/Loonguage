#pragma once
#include <vector>
#include <map>
#include "Code.h"
#include "Register.h"
#include "RuntimeConfig.h"
#include <array>
#include <bitset>
namespace Loonguage {
	class RunTime
	{
		using Reg = Register;

		int width;

        int readMem(int) const;
        void writeMem(int, int);
		int readChar(int) const;
		void writeChar(int, int);
        std::vector<int> int2bit(int) const;
        int bit2int(std::vector<int>) const;
	public:
		//start pointer of stack and stack data, used for stack data display
		int stackBegin;
		std::vector<int> getStack();
		//index of next instruction to be executed, used for codeOut
        int currentCode;
		//value of all registers
		std::map<Register::Registers, int> regs;
		//a byte unit
		std::vector<std::bitset<8>> memory;
		//a byte unit of inout space
		//IN from top, OUT from bottom
		std::vector<std::bitset<8>> inout;
		//instructions
		std::vector<Code> codes;
		std::map<std::string, int> labels;
		RunTimeConfig config;
        RunTime(RunTimeConfig, std::vector<Code>&);
		//2 status signs
		bool Z;
		bool S;
		//advance a step
        int tick();
		std::string stdOut() const;
	};


}
