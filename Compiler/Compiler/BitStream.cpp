#include "BitStream.h"
#include "Compiler.h"
#include <map>
namespace Loonguage {
	void BitStream::setSection(std::bitset<32>& bit, int l, int r, int v)
	{
		for (int i = 0; i < l - r + 1; i++)
			bit[r + i] = ((unsigned long long)v >> i) & 1;
	}

	void BitStream::setRegister(std::bitset<32>& bit, int l, int r, Register::Registers reg)
	{
		//$ret and $rze are fixed
		if (reg == Register::ret)
			setSection(bit, l, r, 0b11111);
		if (reg == Register::rze)
			setSection(bit, l, r, 0b00000);
		//$ins, $rhi and $rlo are not general registers
		if (reg == Register::rsp)
			setSection(bit, l, r, 0b00001);
		if (reg == Register::rfp)
			setSection(bit, l, r, 0b00010);
		if (reg == Register::rax)
			setSection(bit, l, r, 0b00011);
		if (reg == Register::rtm)
			setSection(bit, l, r, 0b00100);
		if (reg == Register::rbx)
			setSection(bit, l, r, 0b00110);
		if (reg == Register::rcx)
			setSection(bit, l, r, 0b00111);
		if (reg == Register::rdx)
			setSection(bit, l, r, 0b01000);
		if (reg == Register::rin)
			setSection(bit, l, r, 0b01001);
		if (reg == Register::rot)
			setSection(bit, l, r, 0b01010);
	}

	BitStream::BitStream(Compiler& compiler):
        codes(compiler.codes), codeBegin(compiler.codeBegin)
	{
	}

	//signal means wheather input is valid
	BitStream::BitStream(std::istream& cin, bool& signal)
	{
		codeBegin = 0;
		std::string str;
		while (std::getline(cin, str))
		{
			codes.push_back(Code(str, signal));
		}
	}

	std::bitset<32> BitStream::setCode(Code code)
	{
		std::bitset<32> res;
		if (code.codeType == Code::AND)
		{
			setSection(res, 31, 26, 0b000000);
			setSection(res, 10, 0, 0b00000100100);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setRegister(res, 15, 11, code.rd);
		}
		if (code.codeType == Code::ANDI)
		{
			setSection(res, 31, 26, 0b001100);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setSection(res, 15, 0, code.immediate);
		}
		if (code.codeType == Code::OR)
		{
			setSection(res, 31, 26, 0b000000);
			setSection(res, 10, 0, 0b00000100101);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setRegister(res, 15, 11, code.rd);
		}
		if (code.codeType == Code::ORI)
		{
			setSection(res, 31, 26, 0b001101);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setSection(res, 15, 0, code.immediate);
		}
		if (code.codeType == Code::XOR)
		{
			setSection(res, 31, 26, 0b000000);
			setSection(res, 10, 0, 0b00000100110);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setRegister(res, 15, 11, code.rd);
		}
		if (code.codeType == Code::XORI)
		{
			setSection(res, 31, 26, 0b001110);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setSection(res, 15, 0, code.immediate);
		}
		if (code.codeType == Code::NOT)
		{
			setSection(res, 31, 26, 0b000000);
			setSection(res, 15, 0, 0b0000000000100111);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
		}
		if (code.codeType == Code::ADD)
		{
			setSection(res, 31, 26, 0b000000);
			setSection(res, 10, 0, 0b00000100000);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setRegister(res, 15, 11, code.rd);
		}
		if (code.codeType == Code::ADDI)
		{
			setSection(res, 31, 26, 0b001000);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setSection(res, 15, 0, code.immediate);
		}
		if (code.codeType == Code::SUB)
		{
			setSection(res, 31, 26, 0b000000);
			setSection(res, 10, 0, 0b00000100010);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setRegister(res, 15, 11, code.rd);
		}
		if (code.codeType == Code::MUL)
		{
			setSection(res, 31, 26, 0b011100);
			setSection(res, 10, 0, 0b00000000010);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setRegister(res, 15, 11, code.rd);
		}
		if (code.codeType == Code::DIV)
		{
			setSection(res, 31, 26, 0b000000);
			setSection(res, 15, 0, 0b0000000000011010);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
		}
		if (code.codeType == Code::SLT)
		{
			setSection(res, 31, 26, 0b000000);
			setSection(res, 10, 0, 0b00000101010);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setRegister(res, 15, 11, code.rd);
		}
		if (code.codeType == Code::B)
		{
			setSection(res, 31, 16, 0b0001000000000000);
		}
		if (code.codeType == Code::BEQ)
		{
			setSection(res, 31, 26, 0b000100);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
		}
		if (code.codeType == Code::JR)
		{
			setSection(res, 31, 26, 0b000000);
			setSection(res, 20, 0, 0b000000000000000001000);
			setRegister(res, 25, 21, code.rs);
		}
		if (code.codeType == Code::JAL)
		{
			setSection(res, 31, 26, 0b000011);
		}
		if (code.codeType == Code::LB)
		{
			setSection(res, 31, 26, 0b100000);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setSection(res, 15, 0, code.immediate);
		}
		if (code.codeType == Code::LBU)
		{
			setSection(res, 31, 26, 0b100100);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setSection(res, 15, 0, code.immediate);
		}
		if (code.codeType == Code::LH)
		{
			setSection(res, 31, 26, 0b100001);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setSection(res, 15, 0, code.immediate);

		}
		if (code.codeType == Code::LHU)
		{
			setSection(res, 31, 26, 0b100101);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setSection(res, 15, 0, code.immediate);
		}
		if (code.codeType == Code::LW)
		{
			setSection(res, 31, 26, 0b100011);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setSection(res, 15, 0, code.immediate);
		}
		if (code.codeType == Code::SB)
		{
			setSection(res, 31, 26, 0b101000);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setSection(res, 15, 0, code.immediate);
		}
		if (code.codeType == Code::SH)
		{
			setSection(res, 31, 26, 0b101001);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setSection(res, 15, 0, code.immediate);
		}
		if (code.codeType == Code::SW)
		{
			setSection(res, 31, 26, 0b101011);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setSection(res, 15, 0, code.immediate);
		}
		if (code.codeType == Code::NOP)
		{
			setSection(res, 31, 0, 0b00000000000000000000000000000000);
		}
		if (code.codeType == Code::MOVZ)
		{
			setSection(res, 31, 26, 0b000000);
			setSection(res, 10, 0, 0b00000001010);
			setRegister(res, 25, 21, code.rs);
			setRegister(res, 20, 16, code.rt);
			setRegister(res, 15, 11, code.rd);
		}
		if (code.codeType == Code::MFHI)
		{
			setSection(res, 31, 16, 0b0000000000000000);
			setSection(res, 10, 0, 0b00000010000);
			setRegister(res, 15, 11, code.rd);
		}
		if (code.codeType == Code::MFLO)
		{
			setSection(res, 31, 16, 0b0000000000000000);
			setSection(res, 10, 0, 0b00000010010);
			setRegister(res, 15, 11, code.rd);
		}
		if (code.codeType == Code::MTHI)
		{
			setSection(res, 31, 26, 0b000000);
			setSection(res, 20, 0, 0b000000000000000010001);
			setRegister(res, 25, 21, code.rs);
		}
		if (code.codeType == Code::MTLO)
		{
			setSection(res, 31, 26, 0b000000);
			setSection(res, 20, 0, 0b000000000000000010011);
			setRegister(res, 25, 21, code.rs);
		}
		if (code.codeType == Code::HLT)
		{
			setSection(res, 31, 0, 0b00000100000000000000000000000000);
		}
		return res;
	}

	void BitStream::generateTestBench(std::ostream& cout, std::string pattern, int i)
	{
		std::bitset<32> bits = setCode(codes[i]);
		std::map<std::string, int> m;
		m["addr00"] = codeBegin + i * 4;
		m["addr01"] = codeBegin + i * 4 + 1;
		m["addr02"] = codeBegin + i * 4 + 2;
		m["addr03"] = codeBegin + i * 4 + 3;
		for (int j = 0; j < 32; j++)
		{
			if (j < 10)
                m[std::string("data0") + std::to_string(j)] = bits[j];
			else
                m[std::string("data") + std::to_string(j)] = bits[j];
		}
		for (int j = 0; j < pattern.size(); j++)
		{
			if (pattern[j] != '%')
				cout << pattern[j];
			else
			{
				std::string str;
				for (int k = 1; k <= 6 && j + k < pattern.size(); k++)
					str.push_back(pattern[j + k]);
				cout << m[str];
				j += 6;
			}
		}

	}
}
