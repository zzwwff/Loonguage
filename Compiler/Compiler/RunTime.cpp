#include "RunTime.h"
#include "Compiler.h"
namespace Loonguage {
	//readMem a number in x64 or x32 from memory
	int RunTime::read(int pos, int width, bool sign) const
	{
		std::vector<int> bits(32);
		int res = 0;
		if (config.endian == config.BIG)
		{
            for (int i = 0; i < width && pos + i < memory.size(); i++)
				for (int j = 0; j < 8; j++)
                    bits[8 * i + j] = memory[pos + i][j];
		}
		else
		{
			for (int i = 0; i < width && pos + i < memory.size(); i++)
				for (int j = 0; j < 8; j++)
                    bits[8 * i + j] = memory[pos + i][j];
		}
		//if sign = 1, extend bits[8 * width]
		if (sign)
		{
			for (int i = 8 * width; i < bits.size(); i++)
				bits[i] = bits[8 * width - 1];
		}
		return bit2int(bits);
	}

	//writeMem a number in x64 or x32 into memory
	void RunTime::write(int pos, int dat, int width)
	{
		std::vector<int> bits = int2bit(dat);
		if (config.endian == config.BIG)
		{
			for (int i = 0; i < width && pos + i < memory.size(); i++)
				for (int j = 0; j < 8; j++)
                    memory[pos + i][j] = bits[8 * i + j];
		}
		else
		{
			for (int i = 0; i < width && pos + i < memory.size(); i++)
				for (int j = 0; j < 8; j++)
                    memory[pos + i][j] = bits[8 * i + j];
		}
	}


    int RunTime::readChar(int pos, int from = 0) const
	{
		int val = 0;
		for (int j = 0; j < 8; j++)
			if (from)
			{
				if (pos < memory.size())
					val += memory[pos][j] << j;
			}
			else
			{
				if (pos < inout.size())
					val += inout[pos][j] << j;
			}
		return val;
	}

    void RunTime::writeChar(int pos, int i, int from = 0)
	{
		for (int j = 0; j < 8; j++)
			if (from)
			{
				if (pos < memory.size())
					memory[pos][j] = ((unsigned int)i >> j) & 1;
			}
			else
			{
				if (pos < inout.size())
					inout[pos][j] = ((unsigned int)i >> j) & 1;
			}

	}

	std::vector<int> RunTime::int2bit(int i) const
	{
		bool signal = i < 0;
		if (i < 0) i = -i - 1;
		std::vector<int> vec;
		vec = std::vector<int>(32);
		for (int j = 0; j < 31; j++)
            vec[j] = ((long long)i >> j) & 1;
		if (signal)
			for (auto& n : vec)
                n = 1 - n;
		return vec;
	}

	int RunTime::bit2int(std::vector<int> vec) const
	{
        bool signal = vec[31];
		if (signal)
			for (auto& j : vec)
                j = 1 - j;
		int val = 0;
		for (int j = 0; j < 31; j++)
            val += vec[j] << j;
		if (signal)
			val = -val - 1;
		return val;
	}

	//allocate string constand from bottom of stack
	void RunTime::allocateString(SymbolTable<std::string>& strTable, std::map<Symbol, int> strPosition)
	{
		for (auto& pstr : strTable)
		{
			const std::string& str = pstr.first;
			int pos = strPosition[strTable[str]];
            writeChar(pos, str.size(), 1);
			for (int i = 0; i < str.size(); i++)
			{
                writeChar(pos - 1 - i, str[i], 1);
			}
		}
	}

	//alocate input from bottom of inout
	void RunTime::allocateInput(const std::string& input)
	{
		for (int i = 0, target = regs[Reg::rin]; i < input.size(); i++)
		{
			writeChar(target, input[i]);
            target--;
		}
	}

	std::vector<int> RunTime::getStack()
	{
		std::vector<int> vec;
		for (int i = stackBegin; i > regs[Reg::rsp]; i -= width)
		{
			vec.push_back(read(i, 4, true));
		}
		return vec;
	}

    RunTime::RunTime(RunTimeConfig c, Compiler& compiler, const std::string& input = "") :
		config(c), stringBegin(compiler.stringBegin)
	{
        codes = compiler.codes;
		//initiate registers
		for (Reg::Registers reg = Reg::rsp; reg <= Reg::rot; reg = static_cast<Reg::Registers>(reg + 1))
		{
			regs[reg] = 0;
		}
		//initiate memory
		memory = std::vector<std::bitset<8>>(c.memorySize);
		//initiate inout
		inout = std::vector<std::bitset<8>>(c.inoutSize);
		regs[Reg::rot] = 0;
		regs[Reg::rin] = inout.size() - 1;
		int rin = regs[Reg::rin];
		for (auto ch : config.stdIn)
		{
			write(rin, ch, 4);
			rin--;
		}
		//64 width = 64 bits = 8 bytes
		//32 width = 32 bits = 4 bytes
		width = 4;
		//0 ~ stringBegin - 1 are reserved for strings
        regs[Reg::ins] = 0;
        regs[Reg::rsp] = config.memorySize - width;
		stackBegin = regs[Reg::rsp];
		regs[Reg::rfp] = regs[Reg::rsp];
		//initiate label lists, for easy jump, labels points to memory position, which is $ins + i * width
		for (int i = 0; i < codes.size(); i++)
		{
			for (int j = 0; j < codes[i].labelAttached.size(); j++)
                labels[codes[i].labelAttached[j].name] = regs[Reg::ins] + i * width;
		}
        currentCode = 0;
		allocateString(compiler.strTable, compiler.strPosition);
		allocateInput(input);
	}
	
	//advance a step
    int RunTime::tick()
	{
		//real position of nextInstruction is ($ins - stringBegin) / width
        int nextInstruction = (regs[Reg::ins] - 0) / width;
		Code nextCode = codes[nextInstruction];
		if (nextCode.codeType == Code::B)
		{
			//%ins = label
			regs[Reg::ins] = labels[nextCode.label.name];
		}
		else if (nextCode.codeType == Code::BEQ)
		{
			if (regs[nextCode.rs] == regs[nextCode.rt])
			{
				//%ins = label
				regs[Reg::ins] = labels[nextCode.label.name];
			}
            else regs[Reg::ins] += width;
		}	
		else if (nextCode.codeType == Code::JR)
		{
			regs[Reg::ins] = regs[nextCode.rs];
		}
		else if (nextCode.codeType == Code::JAL)
		{
			//%ret points to next instruction
            regs[Reg::ret] = regs[Reg::ins] + width;
			//%ins = label
			regs[Reg::ins] = labels[nextCode.label.name];
		}
		else
		{
			//no control shift, %ins points to next instruction
            regs[Reg::ins] += width;
			
			if (nextCode.codeType == Code::AND)
			{
				regs[nextCode.rd] = regs[nextCode.rs] & regs[nextCode.rt];
			}
			else if (nextCode.codeType == Code::ANDI)
			{
				regs[nextCode.rt] = regs[nextCode.rs] & nextCode.immediate;
			}
			else if (nextCode.codeType == Code::OR)
			{
				regs[nextCode.rd] = regs[nextCode.rs] | regs[nextCode.rt];
			}
			else if (nextCode.codeType == Code::ORI)
			{
				regs[nextCode.rt] = regs[nextCode.rs] | nextCode.immediate;
			}			
			else if (nextCode.codeType == Code::XOR)
			{
				regs[nextCode.rd] = regs[nextCode.rs] ^ regs[nextCode.rt];
			}
			else if (nextCode.codeType == Code::NOT)
			{
				regs[nextCode.rt] = ~(regs[nextCode.rs]);
			}
			else if (nextCode.codeType == Code::XORI)
			{
				regs[nextCode.rt] = regs[nextCode.rs] ^ nextCode.immediate;
			}
			else if (nextCode.codeType == Code::ADD)
			{
				regs[nextCode.rd] = regs[nextCode.rs] + regs[nextCode.rt];
			}
			else if (nextCode.codeType == Code::ADDI)
			{
				regs[nextCode.rt] = regs[nextCode.rs] + nextCode.immediate;
			}
			else if (nextCode.codeType == Code::SUB)
			{
				regs[nextCode.rd] = regs[nextCode.rs] - regs[nextCode.rt];
			}
			else if (nextCode.codeType == Code::MUL)
			{
				regs[nextCode.rd] = regs[nextCode.rs] * regs[nextCode.rt];
			}
			else if (nextCode.codeType == Code::DIV)
			{
				regs[Reg::rlo] = regs[nextCode.rs] / regs[nextCode.rt];
				regs[Reg::rhi] = regs[nextCode.rs] % regs[nextCode.rt];
			}
			else if (nextCode.codeType == Code::SLT)
			{
				regs[nextCode.rd] = regs[nextCode.rs] < regs[nextCode.rt];
			}
			else if (nextCode.codeType == Code::LB)
			{
				int target = regs[nextCode.rs] + nextCode.immediate;
				regs[nextCode.rt] = read(target, 1, true);
			}
			else if (nextCode.codeType == Code::LBU)
			{
				int target = regs[nextCode.rs] + nextCode.immediate;
				regs[nextCode.rt] = read(target, 1, false);
			}
			else if (nextCode.codeType == Code::LH)
			{
				int target = regs[nextCode.rs] + nextCode.immediate;
				regs[nextCode.rt] = read(target, 2, true);
			}
			else if (nextCode.codeType == Code::LHU)
			{
				int target = regs[nextCode.rs] + nextCode.immediate;
				regs[nextCode.rt] = read(target, 2, false);
			}
			else if (nextCode.codeType == Code::LW)
			{
				int target = regs[nextCode.rs] + nextCode.immediate;
				regs[nextCode.rt] = read(target, 4, true);
			}
			else if (nextCode.codeType == Code::SB)
			{
				int target = regs[nextCode.rs] + nextCode.immediate;
				write(target, regs[nextCode.rt], 1);
			}
			else if (nextCode.codeType == Code::SH)
			{
				int target = regs[nextCode.rs] + nextCode.immediate;
				write(target, regs[nextCode.rt], 2);
			}
			else if (nextCode.codeType == Code::SW)
			{
				int target = regs[nextCode.rs] + nextCode.immediate;
				write(target, regs[nextCode.rt], 4);
			}
			else if (nextCode.codeType == Code::NOP)
			{
				
			}
			else if (nextCode.codeType == Code::MOVZ)
			{
				if (regs[nextCode.rt] == 0)
					regs[nextCode.rd] = regs[nextCode.rs];
			}
			else if (nextCode.codeType == Code::MFHI)
			{
				regs[nextCode.rd] = regs[Reg::rhi];
			}
			else if (nextCode.codeType == Code::MFLO)
			{
				regs[nextCode.rd] = regs[Reg::rlo];
			}
			else if (nextCode.codeType == Code::MTHI)
			{
				regs[Reg::rhi] = regs[nextCode.rs];
			}
			else if (nextCode.codeType == Code::MTLO)
			{
				regs[Reg::rlo] = regs[nextCode.rs];
			}
			else if (nextCode.codeType == Code::HLT)
			{
				return 1;
			}
			else if (nextCode.codeType == Code::STDIN)
			{
				int val = regs[nextCode.rs];
				writeChar(regs[Reg::rot], val);
				regs[Reg::rot]++;
			}
			else if (nextCode.codeType == Code::STDOUT)
			{
				int val = readChar(regs[Reg::rin]);
				regs[nextCode.rs] = val;
				regs[Reg::rin]--;
			}
		}
		//set index of current code, so current code will be highlighted in QT
        currentCode = (regs[Reg::ins] - 0) / width;;
        return 0;
	}

	std::string RunTime::stdOut() const
	{
		std::string str;
		for (int rot = 0; rot < regs.at(Reg::rot); rot++)
			str.push_back(readChar(rot));
		return str;
	}

}
