#pragma once
#include "Label.h"
#include "Register.h"
#include "Address.h"
#include <iostream>
#include <vector>
namespace Loonguage {
	class Code
	{
	public:
		//all label that points at this code
		std::vector<Label> labelAttached;
		//it should begin with PUSH and end with NOP
		enum CodeType {
			PUSH,
			POP,
			CALL,
			RET,
			MOVRI,
			MOVRM,
			MOVMR,
			MOVRR,
			LEA,
			ADD,
			SUB,
			MUL,
			DIV,
			AND,
			OR,
			XOR,
			LES,
			EQU,
			REV,
			NOP,
            HLT,
			JMP,
			JMZ
		};
		CodeType codeType;
		Register::Registers r1;
		Register::Registers r2;
		//label as its parameter
		Label label;
		Address address;
		int immediate;
		Code(CodeType c, Register::Registers);
		Code(CodeType c, Label);
		Code(CodeType c);
		Code(CodeType c, Register::Registers, int);
		Code(CodeType c, Register::Registers, Address);
		Code(CodeType c, Address, Register::Registers);
		Code(CodeType c, Register::Registers, Register::Registers);
		void dumpReg(std::ostream&, Register::Registers) const;
		void dumpAddress(std::ostream&, Address) const;	
		void dump(std::ostream&) const;
		void addLabel(Label);
	};
}

