#include "Code.h"

namespace Loonguage {
	//specifically for beq
	Code::Code(CodeType c, Register::Registers r1, Register::Registers r2, Label l) :
		codeType(c), rs(r1), rt(r2), label(l)
	{
	}

	//specifically for b
	Code::Code(CodeType c, Label r) :
		codeType(c), label(r)
	{
	}

	Code::Code(CodeType c) :
		codeType(c)
	{
	}

	Code::Code(CodeType c, Register::Registers r1, Register::Registers r2, int i) :
		codeType(c), rs(r1), rt(r2), immediate(i)
	{
	}

	Code::Code(CodeType c, Register::Registers r1, Register::Registers r2, Register::Registers r3) :
		codeType(c), rs(r1), rt(r2), rd(r3)
	{
	}

	Code::Code(CodeType c, Register::Registers r1) :
		codeType(c)
	{
		if (c == Code::MFHI || c == Code::MFLO)
			rd = r1;
		else rs = r1;
	}

	Code::Code(CodeType c, Register::Registers r1, Register::Registers r2):
		codeType(c), rs(r1), rt(r2)
	{
	}


	std::ostream& operator << (std::ostream& cout, const Label& r)
	{
		cout << r.name << " ";
		return cout;
	}


	std::ostream& operator << (std::ostream& cout, const Register::Registers& r)
	{
		if (r == Register::Registers::ins) cout << "$ins ";
		if (r == Register::Registers::rsp) cout << "$rsp ";
		if (r == Register::Registers::rfp) cout << "$rfp ";
		if (r == Register::Registers::rax) cout << "$rax ";
		if (r == Register::Registers::rtm) cout << "$rtm ";
		if (r == Register::Registers::rbx) cout << "$rbx ";
		if (r == Register::Registers::rcx) cout << "$rcx ";
		if (r == Register::Registers::rdx) cout << "$rdx ";

		if (r == Register::Registers::rin) cout << "$rin ";
		if (r == Register::Registers::rot) cout << "$rot ";
		if (r == Register::Registers::rlo) cout << "$rlo ";
		if (r == Register::Registers::rhi) cout << "$rhi ";
		if (r == Register::Registers::rze) cout << "$rze ";
		if (r == Register::Registers::ret) cout << "$ret ";
		return cout;
	}



	void Code::dump(std::ostream& cout) const
	{
		for (auto label : labelAttached)
			cout << label.name << ":" << std::endl;
		if (codeType == ADD) cout << "add " << rd << rs << rt;
        if (codeType == ADDI) cout << "addi " << rt << rs << immediate;
		if (codeType == OR) cout << "or " << rd << rs << rt;
        if (codeType == ORI) cout << "ori " << rt << rs << immediate;
		if (codeType == NOT) cout << "not " << rs << rt;
		if (codeType == XOR) cout << "xor " << rd << rs << rt;
        if (codeType == XORI) cout << "xori " << rt << rs << immediate;
		if (codeType == AND) cout << "and " << rd << rs << rt;
        if (codeType == ANDI) cout << "andi " << rt << rs << immediate;
		if (codeType == SUB) cout << "sub " << rd << rs << rt;
		if (codeType == MUL) cout << "mul " << rd << rs << rt;
		if (codeType == DIV) cout << "div " << rs << rt;
		if (codeType == SLT) cout << "slt " << rd << rs << rt;
		
		if (codeType == B) cout << "b " << label;
		if (codeType == BEQ) cout << "beq " << rs << rt << label;
		if (codeType == JR) cout << "jr " << rs;
		if (codeType == JAL) cout << "jal " << label;

		if (codeType == LB) cout << "lb " << rt << immediate << "(" << rs << ")";
		if (codeType == LBU) cout << "lbu " << rt << immediate << "(" << rs << ")";
		if (codeType == LH) cout << "lh " << rt << immediate << "(" << rs << ")";
		if (codeType == LHU) cout << "lhu " << rt << immediate << "(" << rs << ")";
        if (codeType == LW)
            cout << "lw " << rt << immediate << "(" << rs << ")";
		if (codeType == SB) cout << "sb " << rt << immediate << "(" << rs << ")";
		if (codeType == SH) cout << "sh " << rt << immediate << "(" << rs << ")";
        if (codeType == SW)
            cout << "sw " << rt << immediate << "(" << rs << ")";
		
		if (codeType == NOP) cout << "nop ";

		if (codeType == MOVZ) cout << "movz  " << rd << rs << rt;
		if (codeType == MFHI) cout << "mfhi " << rd;
		if (codeType == MFLO) cout << "mflo " << rd;
		if (codeType == MTHI) cout << "mthi " << rs;
		if (codeType == MTLO) cout << "mtlo " << rs;	

        if (codeType == OUT) cout << "out " << rs;

		if (codeType == HLT) cout << "hlt ";

		cout;
	}


	void Code::addLabel(Label l)
	{
		labelAttached.push_back(l);
	}
}

