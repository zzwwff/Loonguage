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
        int read(int) const;
        void write(int, int);
        std::vector<int> int2bit(int) const;
        int bit2int(std::vector<int>) const;
	public:
        int currentCode;
		//value of all registers
		std::map<Register::Registers, int> regs;
		//a byte unit
		std::vector<std::bitset<8>> memory;
		//instructions
		std::vector<Code> codes;
		std::map<std::string, int> labels;
		RunTimeConfig config;
        RunTime(RunTimeConfig, std::vector<Code>&);
		bool Z;
		bool S;
		//advance a step
        int tick();
	};


}
