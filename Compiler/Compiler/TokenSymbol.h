#pragma once
#include "Token.h"
namespace Loonguage {

	class TokenSymbol :
		public Token
	{
		char symbol;								//symbol, while '#' stands for '='
	public:
		void dump(std::ostream& cout) const;		//override
		TokenSymbol(int l, char ch);				//constructor
	};
};


