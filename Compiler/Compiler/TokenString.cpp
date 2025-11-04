#include "TokenString.h"
namespace Loonguage {
	void TokenString::dump(std::ostream& cout) const
	{
#ifdef REAL_NAME
		cout << "{ \"tokenType\" : \"" << tokenType2String() << "\", \"line\" : \"" << line << "\""
			<< ", \"value\" : \"" << value.getId() << "\", \"realName\" : \"" << value.getString() << "\" }";
#else // REAL_NAME
		cout << "{ \"tokenType\" : \"" << tokenType2String() << "\", \"line\" : \"" << line << "\""
			<< ", \"value\" : \"" << value.getId() << "\" }";
#endif
	}

	TokenString::TokenString()
	{
	}

	TokenString::TokenString(int l, std::string str, SymbolTable<std::string>& table) :
		Token(Token::TokenType::TokenString, l), value(table.addSymbol(str))
	{
	}

	TokenString::TokenString(std::istream& cin, SymbolTable<std::string>& table)
	{
		tokenType = TokenType::TokenString;
		std::string str;
		cin >> line >> str;
		value = table.addSymbol(str);
	}
}