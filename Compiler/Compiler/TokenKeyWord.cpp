#include "TokenKeyWord.h"
namespace Loonguage {

	std::string TokenKeyWord::keyWordType2String() const
	{
		if (keyWordType == KeyWordType::KeyWordIf)
			return "KeyWordIf";
		else if (keyWordType == KeyWordType::KeyWordWhile)
			return "KeyWordWhile";
		else throw;
	}

	void TokenKeyWord::string2KeyWordType(std::string str)
	{
		if (str == "KeyWordIf")
			keyWordType = KeyWordType::KeyWordIf;
		else if (str == "KeyWordWhile")
			keyWordType = KeyWordType::KeyWordWhile;
		else throw;
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
	TokenKeyWord::TokenKeyWord(std::istream& cin)
	{
		tokenType = TokenType::TokenKeyWord;
		std::string keyWordStr;
		cin >> line >> keyWordStr;
		string2KeyWordType(keyWordStr);
	}
};