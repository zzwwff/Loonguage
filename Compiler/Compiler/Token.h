#pragma once
#include <iostream>
#include <cstring>
namespace Loonguage {

	class Token
	{
	protected:
		enum TokenType {
			//members of TokenType should be correspondent to that in Token::print() and string2TokenType(std::string)
			TokenKeyWord,
			TokenInt,
			TokenIden,
			TokenSymbol,
			TokenNoType
		};

	public:
		TokenType tokenType;									//type
		int line;												//line number

		std::string tokenType2String() const;					//get type in string
		void string2TokenType(const std::string&);				//get type in string

		virtual void dump(std::ostream& cout) const; 			//dump in JSON
		Token(TokenType t, int i);								//constructor
		Token();												//default constructor
	};

};