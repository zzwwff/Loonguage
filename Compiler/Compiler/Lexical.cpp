#include "Lexical.h"
#include "lex.yy.c"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
namespace Loonguage {
	Lexical::Lexical(std::string str)
	{
		std::string res;
		while (lexical(str.c_str()))
			res += std::string(output);
		tokens.load(res, idenTable);
	}
	void Lexical::dump(std::string str) const
	{
		if (str == "cout")
			tokens.dump(std::cout);
		else
		{
			std::ofstream outfile;
			outfile.open(str);
			tokens.dump(outfile);
			outfile.close();
		}
	}

};

