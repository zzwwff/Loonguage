#pragma once
#include <vector>
#include <map>
#include "Code.h"
#include "Register.h"
#include "RuntimeConfig.h"
namespace Loonguage {
	class RunTime
	{
		using Reg = Register;
		int width;
		unsigned int read(unsigned int) const;
		void write(unsigned int, unsigned int);
	public:
		//value of all registers
		std::map<Register::Registers, unsigned int> regs;
		//a byte unit
		std::vector<char> memory;
		//instructions
		std::vector<Code> codes;
		std::map<std::string, unsigned int> labels;
		RunTimeConfig config;
		RunTime(RunTimeConfig, std::vector<Code>&&);
		bool Z;
		//advance a step
		void tick();
	};


}
