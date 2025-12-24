#include "TokenIden.h"
#include "SymbolTable.cpp"
namespace Loonguage {
	std::string TokenIden::getString() const
	{
#ifdef REAL_NAME
		return value.getString();
#else // REAL_NAME
		return value.getId();
#endif
	}
	void TokenIden::dump(std::ostream& cout) const
	{
#ifdef REAL_NAME
		cout << "{ \"tokenType\" : \"" << tokenType2String() << "\", \"line\" : \"" << line << "\""
			<< ", \"value\" : \"" << value.getId() << "\", \"realName\" : \"" << value.getString() << "\" }";
#else // REAL_NAME
		cout << "{ \"tokenType\" : \"" << tokenType2String() << "\", \"line\" : \"" << line << "\""
			<< ", \"value\" : \"" << value.getId() << "\" }";
#endif
	}

	TokenIden::TokenIden()
	{
	}

	TokenIden::TokenIden(int l, std::string str, SymbolTable<std::string>& table):
		Token(Token::TokenType::TokenIden, l), value(table.addSymbol(str))
	{
	}

	TokenIden::TokenIden(std::istream& cin, SymbolTable<std::string>& table)
	{
		tokenType = TokenType::TokenInt;
		std::string str;
		cin >> line >> str;
		value = table.addSymbol(str);
	}

};