#include "TokenInt.h"
namespace Loonguage {
	void TokenInt::dump(std::ostream& cout) const
	{
		cout << "{ \"tokenType\" : \"" << tokenType2String() << "\", \"line\" : \"" << line << "\""
			<< ", \"value\" : \"" << value << "\" }";
	}

	int TokenInt::getValue() const
	{
		return value;
	}



	TokenInt::TokenInt()
	{
	}

	TokenInt::TokenInt(int l, int v) :
		Token(Token::TokenType::TokenInt, l), value(v)
	{

	}

	TokenInt::TokenInt(std::istream& cin)
	{
		tokenType = TokenType::TokenInt;
		cin >> line >> value;
	}
}