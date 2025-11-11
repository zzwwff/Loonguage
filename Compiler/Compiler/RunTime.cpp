#include "RunTime.h"

namespace Loonguage {
	//read a number in x64 or x32 from memory
	unsigned int RunTime::read(unsigned int pos) const
	{
		//watch out res has to be unsigned int
		unsigned int res = 0;
		if (config.endian == config.BIG)
		{
			for (int i = pos; i > pos - width; i--)
				res = (res << 8) + memory[i];
		}
		else
		{
			for (int i = pos - width + 1; i <= pos; i++)
				res = (res << 8) + memory[i];
		}
		return res;
	}

	//write a number in x64 or x32 into memory
	void RunTime::write(unsigned int pos, unsigned int dat)
	{
		if (config.endian == config.BIG)
		{
			for (int i = pos - width + 1; i <= pos; i++)
			{
				memory[i] = dat & 255;
				dat >>= 8;
			}
		}
		else
		{
			for (int i = pos; i > pos - width; i--)
			{
				memory[i] = dat & 255;
				dat >>= 8;
			}
		}
	}

	RunTime::RunTime(RunTimeConfig c, std::vector<Code>&& co) :
		config(c), Z(0)
	{
		codes = std::move(co);
		//initiate registers
		for (Reg::Registers reg = Reg::rsp; reg <= Reg::rdx; reg = static_cast<Reg::Registers>(reg + 1))
		{
			regs[reg] = 0;
		}
		//initiate memory
		memory = std::vector<char>(c.memorySize);
		//64 width = 64 bits = 8byte
		//32 width = 32 bits = 4byte
		if (c.width == RunTimeConfig::x64)
			width = 8;
		else width = 4;
		//width * codes.size() from top are reserved for codes, which will not be really used in RunTime simulator
		regs[Reg::ins] = codes.size() - 1;
		regs[Reg::rsp] = regs[Reg::ins] - width * codes.size();
		//initiate label lists, for easy jump, labels points to memory position, which is %ins - i * width
		for (int i = 0; i < codes.size(); i++)
		{
			for (int j = 0; j < codes[i].labelAttached.size(); j++)
				labels[codes[i].labelAttached[j].name] = regs[Reg::ins] - i * width;
		}
	}
	
	//advance a step
	void RunTime::tick()
	{
		//real position of nextInstruction is (size() - 1 - %ins) / width
		unsigned int nextInstruction = (memory.size() - 1 - regs[Reg::ins]) / width;
		Code nextCode = codes[nextInstruction];
		if (nextCode.codeType == Code::CALL)
		{
			//PUSH next instruction, which is %ins - width
			write(regs[Reg::rsp], regs[Reg::ins] - width);
			regs[Reg::rsp] -= width;
			//%ins = label
			regs[Reg::ins] = labels[nextCode.label.name];
		}
		else if (nextCode.codeType == Code::RET)
		{
			//POP next instruction to %ins
			//now both %rsp, %ins, %rbp should be the original (%rbp is manually set)
			regs[Reg::rsp] += width;
			//watch out always use read/write
			unsigned int instruction = read(regs[Reg::rsp]);
			regs[Reg::ins] = instruction;
		}
		//unconditionally jump
		else if (nextCode.codeType == Code::JMP)
		{
			regs[Reg::ins] = labels[nextCode.label.name];
		}
		//jump when Z, which means ALU returns 0
		else if (nextCode.codeType == Code::JMZ && Z)
		{
			regs[Reg::ins] = labels[nextCode.label.name];
		}
		else
		{
			//no control shift, %ins points to next instruction
			regs[Reg::ins] -= width;
			if (nextCode.codeType == Code::PUSH)
			{
				write(regs[Reg::rsp], regs[nextCode.r1]);
				regs[Reg::rsp] -= width;
			}
			else if (nextCode.codeType == Code::POP)
			{
				regs[nextCode.r1] = read(regs[Reg::rsp]);
				regs[Reg::rsp] += width;
			}
			else if (nextCode.codeType == Code::MOVRI)
			{
				regs[nextCode.r1] = nextCode.immediate;
			}
			else if (nextCode.codeType == Code::MOVMR)
			{
				unsigned int target = regs[nextCode.address.reg] + nextCode.address.delta;
				write(target, regs[nextCode.r1]);
			}
			else if (nextCode.codeType == Code::MOVRR)
			{
				regs[nextCode.r1] = regs[nextCode.r2];
			}
			else if (nextCode.codeType == Code::MOVRM)
			{
				unsigned int target = regs[nextCode.address.reg] + nextCode.address.delta;
				regs[nextCode.r1] = read(target);
			}
			else if (nextCode.codeType == Code::LEA)
			{
				unsigned int target = regs[nextCode.address.reg] + nextCode.address.delta;
				regs[nextCode.r1] = target;
			}
			//arithmatic computation, nothing interesting
			//just remember to set Z
			else if (nextCode.codeType == Code::ADD)
			{
				unsigned int i1 = regs[nextCode.r1];
				unsigned int i2 = regs[nextCode.r2];
				if (config.width == RunTimeConfig::x32)
					i1 = (unsigned short)((unsigned short)i1 + (unsigned short)i2);
				else
					i1 = i1 + i2;
				regs[nextCode.r1] = i1;
				Z = (i1 == 0);
			}
			else if (nextCode.codeType == Code::SUB)
			{
				unsigned int i1 = regs[nextCode.r1];
				unsigned int i2 = regs[nextCode.r2];
				if (config.width == RunTimeConfig::x32)
					i1 = (unsigned short)((unsigned short)i1 - (unsigned short)i2);
				else
					i1 = i1 + i2;
				regs[nextCode.r1] = i1;
				Z = (i1 == 0);
			}

			else if (nextCode.codeType == Code::MUL)
			{
				unsigned int i1 = regs[nextCode.r1];
				unsigned int i2 = regs[nextCode.r2];
				if (config.width == RunTimeConfig::x32)
					i1 = (unsigned short)((unsigned short)i1 * (unsigned short)i2);
				else
					i1 = i1 + i2;
				regs[nextCode.r1] = i1;
				Z = (i1 == 0);
			}

			else if (nextCode.codeType == Code::DIV)
			{
				unsigned int i1 = regs[nextCode.r1];
				unsigned int i2 = regs[nextCode.r2];
				if (config.width == RunTimeConfig::x32)
					i1 = (unsigned short)((unsigned short)i1 / (unsigned short)i2);
				else
					i1 = i1 + i2;
				regs[nextCode.r1] = i1;
				Z = (i1 == 0);
			}

			else if (nextCode.codeType == Code::AND)
			{
				unsigned int i1 = regs[nextCode.r1];
				unsigned int i2 = regs[nextCode.r2];
				if (config.width == RunTimeConfig::x32)
					i1 = (unsigned short)((unsigned short)i1 & (unsigned short)i2);
				else
					i1 = i1 + i2;
				regs[nextCode.r1] = i1;
				Z = (i1 == 0);
			}

			else if (nextCode.codeType == Code::OR)
			{
				unsigned int i1 = regs[nextCode.r1];
				unsigned int i2 = regs[nextCode.r2];
				if (config.width == RunTimeConfig::x32)
					i1 = (unsigned short)((unsigned short)i1 | (unsigned short)i2);
				else
					i1 = i1 + i2;
				regs[nextCode.r1] = i1;
				Z = (i1 == 0);
			}

			else if (nextCode.codeType == Code::XOR)
			{
				unsigned int i1 = regs[nextCode.r1];
				unsigned int i2 = regs[nextCode.r2];
				if (config.width == RunTimeConfig::x32)
					i1 = (unsigned short)((unsigned short)i1 ^ (unsigned short)i2);
				else
					i1 = i1 + i2;
				regs[nextCode.r1] = i1;
				Z = (i1 == 0);
				}
			else if (nextCode.codeType == Code::NOT)
			{
				unsigned int i1 = regs[nextCode.r1];
				if (i1)
					regs[nextCode.r1] = 0u;
				else regs[nextCode.r2] = 1u;
				Z = (i1 == 0);
			}
			else if (nextCode.codeType == Code::NOP)
			{

				}
		}
	}
}