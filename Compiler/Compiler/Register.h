#pragma once
namespace Loonguage {
	class Register
	{
	public:
		//you have to always make sure that register list begins with rsp
		//and ends with rot, which will be dependedd by RunTime::RunTime()
		enum Registers {
			rsp, //stack pointer
			rfp, //frame pointer
			rax, //return value
			rtm, //temporary value
			ins, //next instruction
			rbx, //parameter 1
			rlo, //low, or division
			rhi, //high, or remainder
			ret, //return address
            rin, //standard in
			rze, //const zero
            rot  //standard out
		};
	};
}


