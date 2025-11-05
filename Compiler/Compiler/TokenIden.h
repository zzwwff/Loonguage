#pragma once
#include "Token.h"
#include "SymbolTable.h"
namespace Loonguage {
	class TokenIden :
		public Token
	{
	public:
		SymbolTable<std::string>::Symbol value;									//value of int literal
		std::string getString() const;
		//override
		void dump(std::ostream&) const;
		//constructor
		TokenIden();
		TokenIden(int, std::string, SymbolTable<std::string>&);
		TokenIden(std::istream&, SymbolTable<std::string>&);
	};
};
