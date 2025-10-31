#pragma once
#include <iostream>
#include <cstring>
namespace Loonguage {

	class Token
	{
	protected:
		enum TokenType {
			//members of TokenType should be correspondent to that in Token::print()
			TokenKeyWord,
			TokenInt,
			TokenIden,
			TokenSymbol
		};

	public:
		TokenType tokenType;							//type
		int line;										//line number

		std::string tokenType2String() const;			//get type in string
		void dump(std::ostream& cout) const; 			//dump in JSON
		Token(TokenType t, int i);						//constructor
	};

};