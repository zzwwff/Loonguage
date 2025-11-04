#include "Lexical.h"

namespace Loonguage {
	Lexical::Lexical():
		scanner(), 
		parser(scanner, idenTable, strTable)
	{
		scanner.switch_streams(std::cin, std::cout);
	}
	void Lexical::parse()
	{
		parser.parse();

	}
	void Lexical::dump() const
	{
		
	}

};

