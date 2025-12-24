#pragma once
#include <string>
namespace Loonguage {
	class RunTimeConfig
	{
	public:

		enum Endian {
			BIG,
			SMALL
		};
		Endian endian;
		int memorySize;
		int inoutSize;
		std::string stdIn;
	};
}


