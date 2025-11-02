%{

/*
 * 本yacc的生成文件是yacc.tab.c和yacc.tab.h
 * yacc文件由3段组成，用2个%%行把这3段隔开。
 *
 * 第1段是声明段，包括：
 * 1-C代码部分：include头文件、函数、类型等声明，这些声明会原样拷到生成的.c文件中。
 * 2-记号声明，如%token
 * 3-类型声明，如%type
 *
 * 第2段是规则段，是yacc文件的主体，包括每个产生式是如何匹配的，以及匹配后要执行的C代码动作。
 *
 * 第3段是C函数定义段，如yyerror()的定义，这些C代码会原样拷到生成的.c文件中。该段内容可以为空
 */

/* 第1段：声明段 */
#include "lexicalConfig.h"	// lex和yacc要共用的头文件，里面包含了一些头文件，重定义了YYSTYPE
#include "stdio.h"
#include "lex.yy.c"
/*
 * 为了能够在C++程序里面调用C函数，必须把每一个需要使用的C函数，其声明都包括在extern "C"{}块里面，
 * 这样C++链接时才能成功链接它们。extern "C"用来在C++环境下设置C链接类型。
 */
   //lex.l中也有类似的这段extern "C"，可以把它们合并成一段，放到共同的头文件main.h中
void yyerror(const char *s) {} ;
extern int yylex(void);	//该函数是在lex.yy.c里定义的，yyparse()里要调用该函数，为了能编译和链接，必须用extern加以声明


%}

%union {
      char yytext[200];
      char errorMsg[200];
    }

/*
 * lex里要return的记号的声明
 * 用token后加一对<member>来定义记号，旨在用于简化书写方式。
 * 假定某个产生式中第1个终结符是记号OPERATOR，则引用OPERATOR属性的方式：
 * 1-如果记号OPERATOR是以普通方式定义的，如%token OPERATOR，则在动作中要写$1.m_cOp，以指明使用YYSTYPE的哪个成员
 * 2-用%token<m_cOp>OPERATOR方式定义后，只需要写$1，yacc会自动替换为$1.m_cOp
 * 另外用<>定义记号后，非终结符如file, tokenlist，必须用%type<member>来定义(否则会报错)，
 * 以指明它们的属性对应YYSTYPE中哪个成员，这时对该非终结符的引用，如$$，会自动替换为$$.member
 */

%token<errorMsg>		ERROR
%token<yytext>		INT
%token<yytext>		IDEN
%token      		WHILE 261
%token      		IF 262

%type<i>            program


%%

//生成式
program:
IDEN IDEN '=' INT ';'
{ printf("hello world\n"); }

%%




int parses()//程序主函数，这个函数也可以放到其它.c, .cpp文件里
{
    printf("Enter expression: \n");
    yyparse();
    return 0;
}
