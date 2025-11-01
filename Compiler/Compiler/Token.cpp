#include "Token.h"
namespace Loonguage {

	std::string Token::tokenType2String() const
	{
		if (tokenType == TokenType::TokenIden)
			return "TokenIden";
		if (tokenType == TokenType::TokenInt)
			return "TokenInt";
		if (tokenType == TokenType::TokenKeyWord)
			return "TokenKeyWord";
		if (tokenType == TokenType::TokenSymbol)
			return "TokenSymbol";
		throw;
	}

	void Token::string2TokenType(const std::string& str)
	{
		if (str == "TokenIden")
			tokenType = TokenType::TokenIden;
		if (str == "TokenInt")
			tokenType = TokenType::TokenInt;
		if (str == "TokenKeyWord")
			tokenType = TokenType::TokenKeyWord;
		if (str == "TokenSymbol")
			tokenType = TokenType::TokenSymbol;
		throw;
	}

	void Token::dump(std::ostream& cout) const
	{
		cout << "{ \"tokenType\" : \"" << tokenType2String() << "\", \"line\" : " << line << "\" }";
	}


	Token::Token(TokenType t, int i) :
		tokenType(t), line(i)
	{

	}

	Token::Token():
		tokenType(TokenType::TokenNoType), line(0)
	{
	}

};