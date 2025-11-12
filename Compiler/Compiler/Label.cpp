#include "Label.h"
namespace Loonguage {
	std::string LabelAllocator::addName(std::string s)
	{
		int i = m[s];
		m[s]++;
		if (i)
			s += std::string("@") + std::to_string(i);
		return s;
	}

	Label::Label(std::string n):
		name(n)
	{
	}

}
