#pragma once
#include "Token.h"
namespace Loonguage {
    class TokenKeyWord :
        public Token
    {
    public:
        enum KeyWordType {
            KeyWordIf,
            KeyWordWhile
        };

        KeyWordType keyWordType;                        //key word
    public:
        void dump(std::ostream&) const;                 //override 
        std::string keyWordType2String() const;			//get key word type in string
        void string2KeyWordType(std::string);       	//load key word type from string

        TokenKeyWord();
        TokenKeyWord(int, KeyWordType);                 //constructor
        TokenKeyWord(std::istream&);                     //constructor
    };

}