#include "RunTime.h"

namespace Loonguage {
	//read a number in x64 or x32 from memory
	int RunTime::read(int pos) const
	{
		std::vector<int> bits(width * 8);
		int res = 0;
		if (config.endian == config.BIG)
		{
			for (int i = 0; i < width; i++)
				for (int j = 0; j < 8; j++)
					bits[8 * i + j] = memory[pos - i][j];
		}
		else
		{
			for (int i = 0; i < width; i++)
				for (int j = 0; j < 8; j++)
					bits[8 * i + j] = memory[pos - width + 1 + i][j];
		}
        return bit2int(bits);
	}

	//write a number in x64 or x32 into memory
	void RunTime::write(int pos, int dat)
	{
        std::vector<int> bits = int2bit(dat);
		if (config.endian == config.BIG)
		{
			for (int i = 0; i < width; i++)
				for (int j = 0; j < 8; j++)
					memory[pos - i][j] = bits[8 * i + j];
		}
		else
		{
			for (int i = 0; i < width; i++)
				for (int j = 0; j < 8; j++)
					memory[pos - width + 1 + i][j] = bits[8 * i + j];
		}
	}

	std::vector<int> RunTime::int2bit(int i) const
	{
		bool signal = i < 0;
		if (i < 0) i = -i - 1;
		std::vector<int> vec;
		if (config.width == config.x32)
		{
			vec = std::vector<int>(32);
			for (int j = 0; j < 31; j++)
                vec[31 - j] = ((long long)i >> j) & 1;
		}
		else{
			vec = std::vector<int>(64);
			for (int j = 0; j < 63; j++)
                vec[63 - j] = ((long long)i >> j) & 1;
		}
		if (signal)
			for (auto& n : vec)
                n = ~n;
		return vec;
	}

	int RunTime::bit2int(std::vector<int> vec) const
	{
		bool signal = vec[0];
		if (signal)
			for (auto& j : vec)
                j = ~j;
		int val = 0;
		if (config.width == config.x32)
		{
			for (int j = 0; j < 31; j++)
                val += vec[31 - j] << j;
		}
		else
		{
			for (int j = 0; j < 63; j++)
                val += vec[63 - j] << j;
		}
		if (signal)
			val = -val - 1;
		return val;
	}

	std::vector<int> RunTime::getStack()
	{
		std::vector<int> vec;
		for (int i = stackBegin; i > regs[Reg::rsp]; i -= width)
		{
			vec.push_back(read(i));
		}
		return vec;
	}

    RunTime::RunTime(RunTimeConfig c, std::vector<Code>& co) :
		config(c), Z(0), S(0)
	{
        codes = co;
		//initiate registers
		for (Reg::Registers reg = Reg::rsp; reg <= Reg::rdx; reg = static_cast<Reg::Registers>(reg + 1))
		{
			regs[reg] = 0;
		}
		//initiate memory
		memory = std::vector<std::bitset<8>>(c.memorySize);
		//64 width = 64 bits = 8byte
		//32 width = 32 bits = 4byte
		if (c.width == RunTimeConfig::x64)
			width = 8;
		else width = 4;
		//width * codes.size() from top are reserved for codes, which will not be really used in RunTime simulator
        regs[Reg::ins] = memory.size() - 1;
		regs[Reg::rsp] = regs[Reg::ins] - width * codes.size();
		stackBegin = regs[Reg::rsp];
		//initiate label lists, for easy jump, labels points to memory position, which is %ins - i * width
		for (int i = 0; i < codes.size(); i++)
		{
			for (int j = 0; j < codes[i].labelAttached.size(); j++)
				labels[codes[i].labelAttached[j].name] = regs[Reg::ins] - i * width;
		}
        currentCode = 0;
	}
	
	//advance a step
    int RunTime::tick()
	{
		//real position of nextInstruction is (size() - 1 - %ins) / width
		int nextInstruction = (memory.size() - 1 - regs[Reg::ins]) / width;
		Code nextCode = codes[nextInstruction];
		if (nextCode.codeType == Code::CALL)
		{
			//PUSH next instruction, which is %ins - width
			write(regs[Reg::rsp], regs[Reg::ins] - width);
			regs[Reg::rsp] -= width;
			//%ins = label
			regs[Reg::ins] = labels[nextCode.label.name];
            Z = S = 0;
		}
		else if (nextCode.codeType == Code::RET)
		{
			//POP next instruction to %ins
			//now both %rsp, %ins, %rbp should be the original (%rbp is manually set)
			regs[Reg::rsp] += width;
			//watch out always use read/write
			int instruction = read(regs[Reg::rsp]);
			regs[Reg::ins] = instruction;
            Z = S = 0;
		}
		//unconditionally jump
		else if (nextCode.codeType == Code::JMP)
		{
			regs[Reg::ins] = labels[nextCode.label.name];
            Z = S = 0;
		}
		//jump when Z, which means ALU returns 0
        else if (nextCode.codeType == Code::JMZ && Z)
		{
            regs[Reg::ins] = labels[nextCode.label.name];
            Z = S = 0;
		}
		else
		{
			//no control shift, %ins points to next instruction
			regs[Reg::ins] -= width;
			if (nextCode.codeType == Code::PUSH)
			{
				write(regs[Reg::rsp], regs[nextCode.r1]);
				regs[Reg::rsp] -= width;
                Z = S = 0;
			}
			else if (nextCode.codeType == Code::POP)
			{
                regs[Reg::rsp] += width;
				regs[nextCode.r1] = read(regs[Reg::rsp]);
                Z = S = 0;
			}
			else if (nextCode.codeType == Code::MOVRI)
			{
				regs[nextCode.r1] = nextCode.immediate;
                Z = S = 0;
            }
			else if (nextCode.codeType == Code::MOVMR)
			{
				int target = regs[nextCode.address.reg] + nextCode.address.delta;
				write(target, regs[nextCode.r1]);
                Z = S = 0;
			}
			else if (nextCode.codeType == Code::MOVRR)
			{
				regs[nextCode.r1] = regs[nextCode.r2];
                Z = S = 0;
			}
			else if (nextCode.codeType == Code::MOVRM)
			{
				int target = regs[nextCode.address.reg] + nextCode.address.delta;
				regs[nextCode.r1] = read(target);
                Z = S = 0;
			}
			else if (nextCode.codeType == Code::LEA)
			{
				int target = regs[nextCode.address.reg] + nextCode.address.delta;
				regs[nextCode.r1] = target;
                Z = S = 0;
			}

			//arithmatic computation, nothing interesting
			//just remember to set Z
			else if (nextCode.codeType == Code::ADD)
			{
				 int i1 = regs[nextCode.r1];
				 int i2 = regs[nextCode.r2];
				if (config.width == RunTimeConfig::x32)
					i1 = ( short)(( short)i1 + ( short)i2);
				else
					i1 = i1 + i2;
				regs[nextCode.r1] = i1;
				Z = (i1 == 0); S = (i1 < 0);
				
			}
			else if (nextCode.codeType == Code::SUB)
			{
				 int i1 = regs[nextCode.r1];
				 int i2 = regs[nextCode.r2];
				if (config.width == RunTimeConfig::x32)
					i1 = ( short)(( short)i1 - ( short)i2);
				else
                    i1 = i1 - i2;
				regs[nextCode.r1] = i1;
				Z = (i1 == 0); S = (i1 < 0);
			}

			else if (nextCode.codeType == Code::MUL)
			{
				 int i1 = regs[nextCode.r1];
				 int i2 = regs[nextCode.r2];
				if (config.width == RunTimeConfig::x32)
					i1 = ( short)(( short)i1 * ( short)i2);
				else
                    i1 = i1 * i2;
				regs[nextCode.r1] = i1;
				Z = (i1 == 0); S = (i1 < 0);
			}

			else if (nextCode.codeType == Code::DIV)
			{
				 int i1 = regs[nextCode.r1];
				 int i2 = regs[nextCode.r2];
				if (config.width == RunTimeConfig::x32)
					i1 = ( short)(( short)i1 / ( short)i2);
				else
                    i1 = i1 / i2;
				regs[nextCode.r1] = i1;
				Z = (i1 == 0); S = (i1 < 0);
			}

			else if (nextCode.codeType == Code::AND)
			{
				 int i1 = regs[nextCode.r1];
				 int i2 = regs[nextCode.r2];
				if (config.width == RunTimeConfig::x32)
					i1 = ( short)(( short)i1 & ( short)i2);
				else
                    i1 = i1 & i2;
				regs[nextCode.r1] = i1;
				Z = (i1 == 0); S = (i1 < 0);
			}

			else if (nextCode.codeType == Code::OR)
			{
				 int i1 = regs[nextCode.r1];
				 int i2 = regs[nextCode.r2];
				if (config.width == RunTimeConfig::x32)
					i1 = ( short)(( short)i1 | ( short)i2);
				else
                    i1 = i1 | i2;
				regs[nextCode.r1] = i1;
				Z = (i1 == 0); S = (i1 < 0);
			}

			else if (nextCode.codeType == Code::XOR)
			{
				 int i1 = regs[nextCode.r1];
				 int i2 = regs[nextCode.r2];
				if (config.width == RunTimeConfig::x32)
					i1 = ( short)(( short)i1 ^ ( short)i2);
				else
                    i1 = i1 ^ i2;
				regs[nextCode.r1] = i1;
				Z = (i1 == 0); S = (i1 < 0);
			}
			else if (nextCode.codeType == Code::LES)
			{
				int i1 = regs[nextCode.r1];
				int i2 = regs[nextCode.r2];
				if (config.width == RunTimeConfig::x32)
					i1 = (short)((short)i1 < (short)i2);
				else
					i1 = i1 < i2;
				regs[nextCode.r1] = i1;
				Z = (i1 == 0); S = (i1 < 0);
			}
			else if (nextCode.codeType == Code::LES)
			{
				int i1 = regs[nextCode.r1];
				int i2 = regs[nextCode.r2];
				if (config.width == RunTimeConfig::x32)
					i1 = (short)((short)i1 == (short)i2);
				else
					i1 = i1 == i2;
				regs[nextCode.r1] = i1;
				Z = (i1 == 0); S = (i1 < 0);
				}

			else if (nextCode.codeType == Code::REV)
			{

				int i1 = regs[nextCode.r1];
				if (i1)
					regs[nextCode.r1] = 0u;
				else regs[nextCode.r2] = 1u;
				Z = (i1 == 0); S = (i1 < 0);
			}
			else if (nextCode.codeType == Code::NOP)
			{
            }
            else if (nextCode.codeType == Code::HLT)
                return 1;
		}
        currentCode = (memory.size() - 1 - regs[Reg::ins]) / width;;
        return 0;
	}
}
