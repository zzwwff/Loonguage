#include <iostream>
#include <cstring>
#include "lex.yy.c"
#include "Tokens.h"

signed main()
{
	Loonguage::SymbolTable<std::string> idenTable;
	std::string str = lexical();
	Loonguage::Tokens tokens(str, idenTable);
	tokens.dump(std::cout);




	return 0;
}