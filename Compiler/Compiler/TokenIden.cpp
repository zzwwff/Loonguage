#include "TokenIden.h"
#include "SymbolTable.cpp"
namespace Loonguage {
	void TokenIden::dump(std::ostream&) const
	{
#ifdef REAL_NAME
		std::cout << "{ \"tokenType\" : \"" << tokenType2String() << "\", \"line\" : \"" << line << "\""
			<< ", \"value\" : \"" << value.getId() << "\", \"realName\" : \"" << value.getString() << "\" }";
#else // REAL_NAME
		std::cout << "{ \"tokenType\" : \"" << tokenType2String() << "\", \"line\" : \"" << line << "\""
			<< ", \"value\" : \"" << value.getId() << "\" }";
#endif
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