#pragma once
#include "Token.h"
namespace Loonguage {

	class TokenInt :
		public Token
	{	
		int value;									//value of int literal
	public:
		//override
		void dump(std::ostream&) const;
		//constructor
		TokenInt(int, int);
		TokenInt(std::istream&);

	};
}


