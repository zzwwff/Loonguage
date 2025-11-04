#pragma once
#include "Token.h"
namespace Loonguage {

	class TokenSymbol :
		public Token
	{
		char symbol;								//symbol, while '#' stands for '='
	public:
		void dump(std::ostream&) const;				//override

		TokenSymbol();
		TokenSymbol(int l, char ch);				//constructor
		TokenSymbol(std::istream&);					//constructor
	};
};


