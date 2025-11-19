#include <iostream>
#include "Compiler.h"
#include <string>
#include <sstream>
signed main()
{
	std::stringstream lexySynOut, semOut;
	Loonguage::Compiler lexical(std::cin, std::cout, std::cout, std::cout, std::cout);
	lexical.parse();
	return 0;

}