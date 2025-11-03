#include <iostream>
#include "LoonParser.hpp"
#include "LoonScanner.h"


signed main()
{


	LoonScanner::Scanner scanner;
	scanner.switch_streams(std::cin, std::cout);
	LoonScanner::Parser parser(scanner);
	parser.parse();
	return 0;
}