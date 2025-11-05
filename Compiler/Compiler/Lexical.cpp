#include "Lexical.h"

namespace Loonguage {
	Lexical::Lexical():
		scanner(), 
		parser(scanner, idenTable, strTable, &program, errs),
		program(NULL)
	{
		scanner.switch_streams(std::cin, std::cout);
	}
	void Lexical::parse()
	{
		parser.parse();
		if (errs.size())
		{
			std::cout << "Compiling halted due to error(s) in lexical and semantic analysis." << std::endl;
			errs.dump(std::cout);
		}
		else 
			program->dump(std::cout, 0);

	}
	void Lexical::dump() const
	{
		
	}

};

