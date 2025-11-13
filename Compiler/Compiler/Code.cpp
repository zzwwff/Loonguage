#include "Code.h"

namespace Loonguage {
	Code::Code(CodeType c, Register::Registers r):
		codeType(c), r1(r)
	{
	}

	Code::Code(CodeType c, Label r):
		codeType(c), label(r)
	{
	}

	Code::Code(CodeType c):
		codeType(c)
	{
	}

	Code::Code(CodeType c, Register::Registers r,  int i):
		codeType(c), r1(r), immediate(i)
	{
	}

	Code::Code(CodeType c, Register::Registers a, Address aa):
		codeType(c), r1(a), address(aa)
	{
	}

	Code::Code(CodeType c, Address a, Register::Registers rrr):
		codeType(c), address(a), r1(rrr)
	{
	}

	Code::Code(CodeType c, Register::Registers rr, Register::Registers rrr):
		codeType(c), r1(rr), r2(rrr)
	{
	}

	void Code::dumpReg(std::ostream& cout, Register::Registers r) const
	{
		if (r == Register::Registers::ins) cout << "%ins ";
		if (r == Register::Registers::rsp) cout << "%rsp ";
		if (r == Register::Registers::rfp) cout << "%rfp ";
		if (r == Register::Registers::rax) cout << "%rax ";
		if (r == Register::Registers::rtm) cout << "%rtm ";
		if (r == Register::Registers::rbx) cout << "%rbx ";
		if (r == Register::Registers::rcx) cout << "%rcx ";
		if (r == Register::Registers::rdx) cout << "%rdx ";

	}

	void Code::dumpAddress(std::ostream& cout, Address a) const
	{
		dumpReg(cout, a.reg);
		cout << "(" << a.delta << ") ";
	}

	void Code::dump(std::ostream& cout) const
	{
		for (auto label : labelAttached)
			cout << label.name << ":" << std::endl;
		if (codeType == PUSH) cout << "PUSH ", dumpReg(cout, r1);
		if (codeType == POP) cout << "POP ", dumpReg(cout, r1);
		if (codeType == CALL) cout << "CALL " << label.name;
		if (codeType == RET) cout << "RET ";
		if (codeType == MOVRI) cout << "MOVRI ", dumpReg(cout, r1), cout << immediate;
		if (codeType == MOVRM) cout << "MOVRM ", dumpReg(cout, r1), dumpAddress(cout, address);
		if (codeType == MOVMR)
			cout << "MOVMR ", dumpAddress(cout, address), dumpReg(cout, r1);
		if (codeType == MOVRR) cout << "MOVRR ", dumpReg(cout, r1), dumpReg(cout, r2);
		if (codeType == LEA) cout << "LEA ", dumpReg(cout, r1), dumpAddress(cout, address);
		if (codeType == ADD) cout << "ADD ", dumpReg(cout, r1), dumpReg(cout, r2);
		if (codeType == SUB) cout << "SUB ", dumpReg(cout, r1), dumpReg(cout, r2);
		if (codeType == MUL) cout << "MUL ", dumpReg(cout, r1), dumpReg(cout, r2);
		if (codeType == DIV) cout << "DIV ", dumpReg(cout, r1), dumpReg(cout, r2);
		if (codeType == AND) cout << "AND ", dumpReg(cout, r1), dumpReg(cout, r2);
		if (codeType == OR) cout << "OR ", dumpReg(cout, r1), dumpReg(cout, r2);
		if (codeType == XOR) cout << "XOR ", dumpReg(cout, r1), dumpReg(cout, r2);
		if (codeType == LES) cout << "LES ", dumpReg(cout, r1), dumpReg(cout, r2);
		if (codeType == EQU) cout << "EQU ", dumpReg(cout, r1), dumpReg(cout, r2);
		if (codeType == REV) cout << "REV ", dumpReg(cout, r1);
		if (codeType == NOP) cout << "NOP ";
		if (codeType == JMP) cout << "JMP " << label.name;
		if (codeType == JMZ) cout << "JMZ " << label.name;
        if (codeType == HLT) cout << "HLT ";
		cout << std::endl;
	}

	void Code::addLabel(Label l)
	{
		labelAttached.push_back(l);
	}
}

