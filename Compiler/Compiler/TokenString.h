#pragma once
#include "Token.h"
#include "SymbolTable.h"
namespace Loonguage {
	class TokenString :
		public Token
	{
	public:
		SymbolTable<std::string>::Symbol value;									//value of int literal
		//override
		void dump(std::ostream&) const;
		//constructor
		std::string getValue() const;
		TokenString();
		TokenString(int, std::string, SymbolTable<std::string>&);
		TokenString(std::istream&, SymbolTable<std::string>&);
	};
}


