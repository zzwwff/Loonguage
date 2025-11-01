#include "TokenSymbol.h"
namespace Loonguage {
	void TokenSymbol::dump(std::ostream& cout) const
	{
		cout << "{ \"tokenType\" : \"" << tokenType2String() << "\", \"line\" : " << line << "\""
			<< ", \"symbol\" : \"" << symbol << "\" }";
	}


	TokenSymbol::TokenSymbol(int l, char ch) :
		Token(TokenType::TokenSymbol, l), symbol(ch)
	{

	}
	TokenSymbol::TokenSymbol(std::istream& cin)
	{
		tokenType = TokenType::TokenSymbol;
		cin >> line >> symbol;
	}
};