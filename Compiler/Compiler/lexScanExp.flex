/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cstring>
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[3000]; /* to assemble string constants */
char *string_buf_ptr;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

/*
 *  Add Your own definitions here
 */



%}

%union {
      int i;
    }

/*
 * Define names for regular expressions here.
 */

%x COMMENTT
%x SINGLE_COMMENTT
%x STRING
%x STRING_ERROR
 
BLANK_CHAR [ \f\r\t\v]
BLANK_STRING {BLANK_CHAR}+


DIGIT [0-9]
DIGITS [0-9]+
LOWER_LETTER [a-z]
UPPER_LETTER [A-Z]
LETTER [a-zA-Z]
IDENTIFIER ({LOWER_LETTER})(_|{DIGIT}|{LETTER})*
TYPE_IDENTIFIER ({UPPER_LETTER})(_|{DIGIT}|{LETTER})*

START_COMMENT (*
END_COMMENT *)

NEW_LINE \n

CLASS [cC][Ll][Aa][Ss][Ss]
ELSE [Ee][Ll][Ss][Ee]
FI [Ff][Ii]
IF [Ii][Ff]
IN [Ii][Nn]
INHERITS [Ii][Nn][Hh][Ee][Rr][Ii][Tt][Ss]
LET [Ll][Ee][Tt]
LOOP [Ll][Oo][Oo][Pp]
POOL [Pp][Oo][Oo][Ll]
THEN [Tt][Hh][Ee][Nn]
WHILE [Ww][Hh][Ii][Ll][Ee]
CASE [Cc][Aa][Ss][Ee]
ESAC [Ee][Ss][Aa][Cc]
OF [Oo][Ff]
NEW [Nn][Ee][Ww]
ISVOID [Ii][Ss][Vv][Oo][Ii][Dd]
NOT [Nn][Oo][Tt]
TRUE t[Rr][Uu][Ee]
FALSE f[Aa][Ll][Ss][Ee]
CLASS_CLASSID {CLASS}

LE              <=
DARROW          =>
ASSIGN          [<][-]



%%

 
 /*
  *  The multiple-character operators.
  */
 
<INITIAL>"(*" BEGIN(COMMENTT);
<INITIAL>-- BEGIN(SINGLE_COMMENTT);
<SINGLE_COMMENTT>[^\n]
<SINGLE_COMMENTT>\n {
    curr_lineno++;
    BEGIN(INITIAL);
}
<COMMENTT>{NEW_LINE} { curr_lineno++; }
<COMMENTT>[^*\n]*        /* eat anything that's not a '*' */
<COMMENTT>"*"+[^*)\n]*   /* eat up '*'s not followed by ')'s */
<COMMENTT>"*)"        BEGIN(INITIAL);
<INITIAL>"*)" {
    BEGIN(INITIAL);
    cool_yylval.error_msg = "Unmatched *)";
    return (ERROR);
}	

<INITIAL>\" {
    string_buf_ptr = string_buf;
    BEGIN(STRING);
}

<STRING>\\\n {
    curr_lineno++;
}

<STRING>\n {
    cool_yylval.error_msg = "Unterminated string constant";
    curr_lineno++;
    BEGIN(STRING_ERROR);
    return (ERROR); 
}

<STRING>\\[btnf] {
    if (string_buf_ptr - string_buf >= MAX_STR_CONST)
    {
        cool_yylval.error_msg = "String constant too long";
        BEGIN (STRING_ERROR);
        return (ERROR);
    }
    if (yytext[1] == 'n')
    	*string_buf_ptr = '\n';
    else if (yytext[1] == 'b')
    	*string_buf_ptr = '\b';
    else if (yytext[1] == 't')
    	*string_buf_ptr = '\t';
    else if (yytext[1] == 'f')
    	*string_buf_ptr = '\f';	
    string_buf_ptr++;
    *string_buf_ptr = '\0';
}

<STRING>\\[^btnf] {
    if (string_buf_ptr - string_buf >= MAX_STR_CONST)
    {
        cool_yylval.error_msg = "String constant too long";
        BEGIN (STRING_ERROR);
        return (ERROR);
    }
    *string_buf_ptr = yytext[1];	
    string_buf_ptr++;
    *string_buf_ptr = '\0';
}

<STRING>\0 {
    cool_yylval.error_msg = "String contains null character";
    BEGIN (STRING_ERROR);
    return (ERROR);
}

<STRING>[^\"\n\0] {
    memcpy(string_buf_ptr, yytext, 1025);
    if (string_buf_ptr - string_buf >= MAX_STR_CONST)
    {
        cool_yylval.error_msg = "String constant too long";
        BEGIN (STRING_ERROR);
        return (ERROR);
    }
    string_buf_ptr += 1;
  }

<STRING>\" {
    cool_yylval.symbol = stringtable.add_string(string_buf);
    BEGIN(INITIAL);
    return (STR_CONST);
}

<STRING_ERROR>[^\"\n]

<STRING_ERROR>[\"] BEGIN(INITIAL);

<STRING_ERROR>[\"\n] {
    curr_lineno++;
    BEGIN(INITIAL);
}


<INITIAL>{BLANK_STRING}  { }
<CS_TYPE>{BLANK_STRING}  { }
<*>{NEW_LINE} { curr_lineno++;  }
<INITIAL>{DIGITS} { cool_yylval.symbol = inttable.add_string(yytext);
		return (INT_CONST); }
{DARROW}		{ return (DARROW); }
{ASSIGN}        { return (ASSIGN); }
{CLASS}          { return (CLASS);}
{ELSE} { return (ELSE);}
{FI} { return (FI);}
{IF} { return (IF);}
{IN} { return (IN);}
{INHERITS} { return (INHERITS);}
{LET} { return (LET);}
{LOOP} { return (LOOP);}
{POOL} { return (POOL);}
{THEN} { return (THEN);}
{WHILE} { return (WHILE);}
{CASE} { return (CASE);}
{ESAC} { return (ESAC);}
{OF} { return (OF);}
{NEW} { return (NEW);}
{ISVOID} { return (ISVOID);}
{NOT} { return (NOT);}
{LE} { return (LE);}
{TRUE} { cool_yylval.boolean = 1;
         return (BOOL_CONST);}
{FALSE} { cool_yylval.boolean = 0;
	  return (BOOL_CONST);}
	  
{IDENTIFIER} { cool_yylval.symbol = idtable.add_string(yytext);
			return (OBJECTID); }
			   
{TYPE_IDENTIFIER} { cool_yylval.symbol = idtable.add_string(yytext);
			   return (TYPEID); }
		   
			   
";" { return (int)';';}
":" { return (int)':';}
"," { return (int)',';}
"+" { return (int)'+';}
"-" { return (int)'-';}
"*" { return (int)'*';}
"/" { return (int)'/';}
"~" { return (int)'~';}
"<" { return (int)'<';}
"=" { return (int)'=';}
"(" { return (int)'(';}
")" { return (int)')';}
"{" { return (int)'{';}
"}" { return (int)'}';}
"." { return (int)'.';}
"@" { return (int)'@';}
[^a] { 
	cool_yylval.error_msg = yytext;
	return (ERROR); 
	}


<COMMENTT><<EOF>>   {
    cool_yylval.error_msg = "EOF in comment";	
    BEGIN(INITIAL);
    return (ERROR);
}

<STRING><<EOF>> { 
    cool_yylval.error_msg = "EOF in string constant";
    BEGIN(INITIAL);
    return (ERROR); 
}

 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */


 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */


%%
