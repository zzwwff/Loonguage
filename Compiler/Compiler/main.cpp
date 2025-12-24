#include <iostream>
#include "Compiler.h"
#include <string>
#include <sstream>
signed main()
{
	std::stringstream lexySynOut, semOut;
	Loonguage::Compiler lexical(std::cin, std::cout, std::cout, std::cout, std::cout);
	lexical.parse(16384);
	for (int i = 31; i >= 0; i--)
		std::cout << "%data" << i;
	return 0;

}