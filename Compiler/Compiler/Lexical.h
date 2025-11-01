#pragma once
#include <cstring>
#include "Tokens.h"
namespace Loonguage {
	class Lexical
	{
	public:
		Tokens tokens;
		SymbolTable<std::string> idenTable;
		//cin of file path
		Lexical(std::string str = "cin");
		void dump(std::string str = "cout") const;
	};
}


