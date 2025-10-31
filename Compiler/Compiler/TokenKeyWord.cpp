#include "TokenKeyWord.h"
namespace Loonguage {

	std::string TokenKeyWord::keyWordType2String() const
	{
		if (keyWordType == KeyWordType::KeyWordIf)
			return "KeyWordIf";
		if (keyWordType == KeyWordType::KeyWordWhile)
			return "KeyWordWhile";
		throw;
	}

	void TokenKeyWord::dump(std::ostream& cout) const
	{
		cout << "{ \"tokenType\" : \"" << tokenType2String() << "\", \"line\" : " <<
			line << "\", \"KeyWordType\" : \"" << keyWordType2String() << "\" }";
	}

	TokenKeyWord::TokenKeyWord(int i, KeyWordType t2) :
		Token(TokenType::TokenKeyWord, i), keyWordType(t2)
	{

	}
};