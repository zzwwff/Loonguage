#pragma once
#include "Token.h"
#include "TokenKeyWord.h"
#include "TokenInt.h"
#include "TokenSymbol.h"
#include "TokenIden.h"
#include "SymbolTable.h"

#include <vector>
#include <cstring>
namespace Loonguage {
	class Tokens :
		public std::vector<Token*>
	{
	public:
		Tokens() {};
		Tokens(std::string&, SymbolTable<std::string>&);
		void load(std::string&, SymbolTable<std::string>&);
		void dump(std::ostream&) const;					//dump in JSON
	};
};


