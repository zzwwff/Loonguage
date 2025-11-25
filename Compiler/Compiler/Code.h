#pragma once
#include "Label.h"
#include "Register.h"
#include <iostream>
#include <vector>
namespace Loonguage {
	class Code
	{
	public:
		//all label that points at this code
		std::vector<Label> labelAttached;
		enum CodeType {
			AND,
			ANDI,
			OR,
			ORI,
			XOR,
			XORI,
			NOT,
			ADD,
			ADDI,
			SUB,
			MUL,
			DIV,
			SLT,
			B,
			BEQ,
			JR,
			JAL,
			LB,
			LBU,
			LH,
			LHU,
			LW,
			SB,
			SH,
			SW,
			NOP,
			MOVZ,
			MFHI,
			MFLO,
			MTHI,
			MTLO,
			HLT
		};
		CodeType codeType;
		Register::Registers rs;
		Register::Registers rt;
		Register::Registers rd;
		//label as its parameter
		Label label;
		int immediate;
		Code(CodeType c);
		Code(CodeType c, Label);
		Code(CodeType c, Register::Registers, Register::Registers, Label);
		Code(CodeType c, Register::Registers);
		Code(CodeType c, Register::Registers, Register::Registers, int);
		Code(CodeType c, Register::Registers, Register::Registers, Register::Registers);
		void dump(std::ostream&) const;
		void addLabel(Label);
	};

	std::ostream& operator << (std::ostream& cout, const Register::Registers& r)
	{
		if (r == Register::Registers::ins) cout << "%ins ";
		if (r == Register::Registers::rsp) cout << "%rsp ";
		if (r == Register::Registers::rfp) cout << "%rfp ";
		if (r == Register::Registers::rax) cout << "%rax ";
		if (r == Register::Registers::rtm) cout << "%rtm ";
		if (r == Register::Registers::rbx) cout << "%rbx ";
		if (r == Register::Registers::rin) cout << "%rin ";
		if (r == Register::Registers::rot) cout << "%rot ";
		if (r == Register::Registers::rlo) cout << "%rlo ";
		if (r == Register::Registers::rhi) cout << "%rhi ";
		if (r == Register::Registers::rze) cout << "%rze ";
		if (r == Register::Registers::ret) cout << "%ret ";
		return cout;
	}


	std::ostream& operator << (std::ostream& cout, const Label& r)
	{
		cout << r.name << " ";
		return cout;
	}
}

