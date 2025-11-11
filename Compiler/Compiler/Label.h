#pragma once
#include <string>
#include <map>
namespace Loonguage {
	class Label
	{
	public:
		std::string name;
		Label(std::string);
	};

	class LabelAllocator {
	public:
		std::map<std::string, int> m;
		std::string addName(std::string);
	};

}

