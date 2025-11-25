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


	void Code::dump(std::ostream& cout) const
	{
		for (auto label : labelAttached)
			cout << label.name << ":" << std::endl << std::endl;
		if (codeType == ADD) cout << "ADD " << rs << rt << rd << std::endl;
		if (codeType == ADDI) cout << "ADDI" << rs << rt << immediate << std::endl;
		if (codeType == OR) cout << "OR " << rs << rt << rd << std::endl;
		if (codeType == ORI) cout << "ORI" << rs << rt << immediate << std::endl;
		if (codeType == NOT) cout << "NOT " << rs << rt << std::endl;
		if (codeType == XOR) cout << "XOR " << rs << rt << rd << std::endl;
		if (codeType == XORI) cout << "XORI" << rs << rt << immediate << std::endl;
		if (codeType == AND) cout << "AND " << rs << rt << rd << std::endl;
		if (codeType == ANDI) cout << "ANDI" << rs << rt << immediate << std::endl;
		if (codeType == SUB) cout << "SUB " << rs << rt << rd << std::endl;
		if (codeType == MUL) cout << "MUL " << rs << rt << rd << std::endl;
		if (codeType == SUB) cout << "MUL " << rs << rt << rd << std::endl;
		if (codeType == DIV) cout << "MUL " << rs << rt << rd << std::endl;
		if (codeType == SLT) cout << "SLT " << rs << rt << rd << std::endl;
		
		if (codeType == B) cout << "B " << label;
		if (codeType == BEQ) cout << "BEQ " << rs << rt << label;
		if (codeType == JR) cout << "JR " << rs;
		if (codeType == JAL) cout << "JAL " << label;

		if (codeType == LB) cout << "LB" << rs << rt << immediate << std::endl;
		if (codeType == LBU) cout << "LBU" << rs << rt << immediate << std::endl;
		if (codeType == LH) cout << "LH" << rs << rt << immediate << std::endl;
		if (codeType == LHU) cout << "LHU" << rs << rt << immediate << std::endl;
		if (codeType == LW) cout << "LW" << rs << rt << immediate << std::endl;
		if (codeType == SB) cout << "SB" << rs << rt << immediate << std::endl;
		if (codeType == SH) cout << "SH" << rs << rt << immediate << std::endl;
		if (codeType == SW) cout << "SW" << rs << rt << immediate << std::endl;
		
		if (codeType == NOP) cout << "NOP" << std::endl;

		if (codeType == MOVZ) cout << "MOVZ " << rs << rt << rd << std::endl;
		if (codeType == MFHI) cout << "MFHI" << rd << std::endl;
		if (codeType == MFLO) cout << "MFlo" << rd << std::endl;
		if (codeType == MTHI) cout << "MTHI" << rs << std::endl;
		if (codeType == MTLO) cout << "MTlo" << rs << std::endl;	

		if (codeType == HLT) cout << "HLT" << std::endl;

		cout << std::endl;
	}


	void Code::addLabel(Label l)
	{
		labelAttached.push_back(l);
	}
}

