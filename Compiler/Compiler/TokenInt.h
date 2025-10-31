#pragma once
#include "Token.h"
namespace Loonguage {

	class TokenInt :
		public Token
	{	
		int value;									//value of int literal
	public:
		void dump(std::ostream& cout) const;		//override
		TokenInt(int, int);							//constructor
	};
}


