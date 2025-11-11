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

	Code::Code(CodeType c, Register::Registers r, unsigned int i):
		codeType(c), r1(r), immediate(i)
	{
	}

	Code::Code(CodeType c, Register::Registers a, Address aa):
		codeType(c), r1(a), address(aa)
	{
	}

	Code::Code(CodeType c, Address a, Register::Registers rrr):
		codeType(c), address(a), r2(rrr)
	{
	}

	Code::Code(CodeType c, Register::Registers rr, Register::Registers rrr):
		codeType(c), r1(rr), r2(rrr)
	{
	}
	void Code::addLabel(Label l)
	{
		labelAttached.push_back(l);
	}
}

