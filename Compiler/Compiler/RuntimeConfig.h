#pragma once
#include <string>
namespace Loonguage {
	class RunTimeConfig
	{
	public:
		enum Width {
			x32,
			x64
		};
		enum Endian {
			BIG,
			SMALL
		};
		Width width;
		Endian endian;
		int memorySize;
		int inoutSize;
		std::string stdIn;
	};
}


