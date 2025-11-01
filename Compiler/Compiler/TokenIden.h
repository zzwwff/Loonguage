#pragma once
#include "Token.h"
#include "SymbolTable.h"
namespace Loonguage {
	class TokenIden :
		public Token
	{
		SymbolTable<std::string>::Symbol value;									//value of int literal
	public:
		//override
		void dump(std::ostream&) const;
		//constructor
		TokenIden(int, std::string, SymbolTable<std::string>&);
		TokenIden(std::istream&, SymbolTable<std::string>&);
	};
};
