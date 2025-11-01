#include <iostream>
#include <cstring>
#include "lex.yy.c"
#include "Tokens.h"

signed main()
{
	std::string str = lexical();
	Loonguage::Tokens tokens(str);
	tokens.dump(std::cout);




	return 0;
}