#ifndef FLEX_BISON_SCANNER_H
#define FLEX_BISON_SCANNER_H

#if !defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer Loon_FlexLexer  // 根据prefix修改

#include <FlexLexer.h>

#endif

#undef YY_DECL
#define YY_DECL LoonScanner::Parser::symbol_type LoonScanner::Scanner::nextToken(\
                                        Loonguage::SymbolTable<std::string>& idenTable,\
                                        Loonguage::SymbolTable<std::string>& strTable)

#include "LoonParser.hpp"

namespace LoonScanner {

    class Scanner : public yyFlexLexer {
    private:
        /* data */
        //Driver& _driver;

    public:
        Scanner() {}

        virtual LoonScanner::Parser::symbol_type nextToken(
            Loonguage::SymbolTable<std::string>& idenTable,
            Loonguage::SymbolTable<std::string>& strTable); // 不需要手动实现这个函数，Flex会生成YY_DECL宏定义的代码来实现这个函数

        virtual ~Scanner() {}
    };
} /* LoonScanner */


#endif //FLEX_BISON_SCANNER_H
