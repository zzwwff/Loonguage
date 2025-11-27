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
			cout << label.name << ":" << std::endl << std::endl;
		if (codeType == ADD) cout << "add " << rd << rs << rt << std::endl;
		if (codeType == ADDI) cout << "addi" << rt << rs << immediate << std::endl;
		if (codeType == OR) cout << "or " << rd << rs << rt << std::endl;
		if (codeType == ORI) cout << "ori" << rt << rs << immediate << std::endl;
		if (codeType == NOT) cout << "not " << rs << rt << std::endl;
		if (codeType == XOR) cout << "xor " << rd << rs << rt << std::endl;
		if (codeType == XORI) cout << "xori" << rt << rs << immediate << std::endl;
		if (codeType == AND) cout << "and " << rd << rs << rt << std::endl;
		if (codeType == ANDI) cout << "andi" << rt << rs << immediate << std::endl;
		if (codeType == SUB) cout << "sub " << rd << rs << rt << std::endl;
		if (codeType == MUL) cout << "mul " << rd << rs << rt << std::endl;
		if (codeType == SUB) cout << "sub " << rd << rs << rt << std::endl;
		if (codeType == DIV) cout << "div " << rs << rt << std::endl;
		if (codeType == SLT) cout << "slt " << rd << rs << rt << std::endl;
		
		if (codeType == B) cout << "b " << label;
		if (codeType == BEQ) cout << "beq " << rs << rt << label;
		if (codeType == JR) cout << "jr " << rs;
		if (codeType == JAL) cout << "jal " << label;

		if (codeType == LB) cout << "lb " << rt << immediate << "(" << rs << ")" << std::endl;
		if (codeType == LBU) cout << "lbu " << rt << immediate << "(" << rs << ")" << std::endl;
		if (codeType == LH) cout << "lh " << rt << immediate << "(" << rs << ")" << std::endl;
		if (codeType == LHU) cout << "lhu " << rt << immediate << "(" << rs << ")" << std::endl;
		if (codeType == LW) cout << "lw " << rt << immediate << "(" << rs << ")" << std::endl;
		if (codeType == SB) cout << "sb " << rt << immediate << "(" << rs << ")" << std::endl;
		if (codeType == SH) cout << "sh " << rt << immediate << "(" << rs << ")" << std::endl;
		if (codeType == SW) cout << "sw " << rt << immediate << "(" << rs << ")" << std::endl;
		
		if (codeType == NOP) cout << "nop " << std::endl;

		if (codeType == MOVZ) cout << "movz  " << rd << rs << rt << std::endl;
		if (codeType == MFHI) cout << "mfhi " << rd << std::endl;
		if (codeType == MFLO) cout << "mflo " << rd << std::endl;
		if (codeType == MTHI) cout << "mthi " << rs << std::endl;
		if (codeType == MTLO) cout << "mtlo " << rs << std::endl;	

		if (codeType == HLT) cout << "hlt " << std::endl;

		cout << std::endl;
	}


	void Code::addLabel(Label l)
	{
		labelAttached.push_back(l);
	}
}

