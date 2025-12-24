#pragma once
#include "Register.h"
namespace Loonguage {
	class Address
	{

	public:
		Register::Registers reg;
		int delta;
		Address(Register::Registers, int);
		Address() = default;
	};

}

