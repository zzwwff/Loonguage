#include <iostream>
#include "Compiler.h"

signed main()
{
	Loonguage::Compiler lexical(std::cin, std::cout, std::cout, std::cout, std::cout);

	lexical.parse();
	return 0;
}