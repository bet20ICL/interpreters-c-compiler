%option noyywrap

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{

// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);
#include "parser.tab.hpp"
%}

%%

"auto"			{ return(AUTO); }
"break"			{ return(BREAK); }
"case"			{ return(CASE); }
"char"			{ return(CHAR); }
"const"			{ return(CONST); }
"continue"		{ return(CONTINUE); }
"default"		{ return(DEFAULT); }
"do"			{ return(DO); }
"double"		{ return(DOUBLE); }
"else"			{ return(ELSE); }
"enum"			{ return(ENUM); }
"extern"		{ return(EXTERN); }
"float"			{ return(FLOAT); }
"for"			{ return(FOR); }
"goto"			{ return(GOTO); }
"if"			{ return(IF); }
"int"			{ return(INT); }
"long"			{ return(LONG); }
"register"		{ return(REGISTER); }
"return"		{ return(RETURN); }
"short"			{ return(SHORT); }
"signed"		{ return(SIGNED); }
"sizeof"		{ return(SIZEOF); }
"static"		{ return(STATIC); }
"struct"		{ return(STRUCT); }
"switch"		{ return(SWITCH); }
"typedef"		{ return(TYPEDEF); }
"union"			{ return(UNION); }
"unsigned"		{ return(UNSIGNED); }
"void"			{ return(VOID); }
"volatile"		{ return(VOLATILE); }
"while"			{ return(WHILE); }
 /* Integers */
{D}+                                 { yylval.number = (int) strtod(yytext, 0); return INT_CONST; }
0[xX]{H}+{IS}?		                 { yylval.number = (int) strtod(yytext, 0); return INT_CONST; }
0{D}+{IS}?		                     { yylval.number = (int) strtod(yytext, 0); return INT_CONST; }
{D}+{IS}?		                     { yylval.number = (int) strtod(yytext, 0); return INT_CONST; }
 /* L?'(\\.|[^\\'])+'	                 { count(); return(CONSTANT); } */

 /* Identifier */
{L}({L}|{D})*                        { yylval.string=new std::string(yytext); return IDENTIFIER; }

 /* Assignment */
"+="			                     { return(ADD_ASSIGN); }
"-="			                     { return(SUB_ASSIGN); }
"*="			                     { return(MUL_ASSIGN); }
"/="			                     { return(DIV_ASSIGN); }
"%="			                     { return(MOD_ASSIGN); }
"&="			                     { return(AND_ASSIGN); }
"^="			                     { return(XOR_ASSIGN); }
"|="			                     { return(OR_ASSIGN); }

 /* Symbols */
","                                  { return (','); }
";"                                  { return (';'); }
"{"                                  { return ('{'); }
"}"                                  { return ('}'); }
"("                                  { return ('('); }
")"                                  { return (')'); }
"["		                             { return('['); }
"]"		                             { return(']'); }

 /* Operator Symbols */
"!"                                  { return ('!'); }
"~"                                  { return ('~'); }
"+"                                  { return ('+'); }
"-"                                  { return ('-'); }
"="                                  { return ('='); }
"&"                                  { return ('&'); }
"|"                                  { return ('|'); }
"^"                                  { return ('^'); }
"/"                                  { return ('/'); }
"%"                                  { return ('%'); }
"<"                                  { return ('<'); }
">"                                  { return ('>'); }

"?"                                  { return ('?'); }
":"                                  { return (':'); }

">>"			                     { return(RIGHT_OP); }
"<<"			                     { return(LEFT_OP); }

"++"			                     { return(INC_OP); }
"--"			                     { return(DEC_OP); }

"->"			                     { return(PTR_OP); }

"<="                                 { return(LE_OP); }
">="			                     { return(GE_OP); }
"=="			                     { return(EQ_OP); }
"!="			                     { return(NE_OP); }
"&&"                                 { return(AND_OP); }
"||"                                 { return(OR_OP); }

"*"                                  { return ('*'); }


 /* Whitespace characters*/
[ \t\v\n\f]		                     { ; }
.                                    {fprintf (stderr, "Invalid token\n"); exit(1);}

%%

void yyerror(char const *s)
{
    fprintf (stderr, "Parse Error: (rip) %s\n", s);
    exit(1);
}

 /* void check_type(ident)
{
    return (IDENTIFIER);
} */
