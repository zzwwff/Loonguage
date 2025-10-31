#include "TokenInt.h"
namespace Loonguage {
	void TokenInt::dump(std::ostream& cout) const
	{
		cout << "{ \"tokenType\" : \"" << tokenType2String() << "\", \"line\" : \"" << line << "\""
			<< ", \"value\" : \"" << value << "\" }";
	}

	TokenInt::TokenInt(int l, int v) :
		Token(Token::TokenType::TokenInt, l), value(v)
	{

	}
}