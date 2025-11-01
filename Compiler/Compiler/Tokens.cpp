#include "Tokens.h"
#include <sstream>
namespace Loonguage {
	Tokens::Tokens(std::string& str, SymbolTable<std::string>& table)
	{
		load(str, table);
	}
	void Tokens::load(std::string& str, SymbolTable<std::string>& table)
	{
		std::stringstream stream(str);
		while (stream.peek() != EOF)
		{
			std::string type;
			stream >> type;
			if (type == "TokenKeyWord")
				push_back(new TokenKeyWord(stream));
			else if (type == "TokenInt")
				push_back(new TokenInt(stream));
			else if (type == "TokenSymbol")
				push_back(new TokenSymbol(stream));
			else if (type == "TokenIden")
				push_back(new TokenIden(stream, table));
			else throw;
		}
	}
	void Tokens::dump(std::ostream& cout) const
	{
		for (const auto& token : *this)
		{
			token->dump(cout);
			cout << std::endl;
		}
	}
};