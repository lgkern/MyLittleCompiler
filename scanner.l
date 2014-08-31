/*
  Grupo MLC - Lucas e Helena
*/
ALPHA	[A-Za-z]
DIGIT	[0-9]
INTEGER {-?{DIGIT}+}

%{
#include "parser.h" //arquivo automaticamente gerado pelo bison
#include <stdlib.h>
#include "symbtable.h"
#include "main.h"

int numLines = 1;
%}			
%x IN_COMMENT


%%
<INITIAL>{
"/*"					BEGIN(IN_COMMENT);
}

<IN_COMMENT>{
"*/"					BEGIN(INITIAL);
[^*\n]+					// Eat comment in chunks
"*"						// Eat the lone star
\n						++numLines;
}


"//".*					{ }
"int"					return  TK_PR_INT;
"float"					return  TK_PR_FLOAT;
"bool"					return  TK_PR_BOOL;
"char"					return  TK_PR_CHAR;
"string"				return  TK_PR_STRING;
"if"					return  TK_PR_IF;
"then"					return  TK_PR_THEN;
"else"					return  TK_PR_ELSE;
"while"					return  TK_PR_WHILE;
"do"					return  TK_PR_DO;
"input"					return  TK_PR_INPUT;
"output"				return  TK_PR_OUTPUT;
"return"				return  TK_PR_RETURN;

","						return	',';
";"						return	';';
":"						return	':';
"("						return	'(';
")"						return	')';
"["						return	'[';
"]"						return	']';
"{"						return	'{';
"}"						return	'}';
"+"						return	'+';
"-"/[ \t\n\r]					return	'-';
"*"						return	'*';
"/"						return	'/';
"<"						return	'<';
">"						return	'>';
"="						return	'=';
"!"						return	'!';
"&"						return	'&';
"$"						return	'$';

"<="					return	TK_OC_LE;
">="					return	TK_OC_GE;
"=="					return	TK_OC_EQ;
"!="					return	TK_OC_NE;
"&&"					return	TK_OC_AND;
"||"					return	TK_OC_OR;

"false"                    {yylval.symbol = addSymbol(createToken(IKS_SIMBOLO_LITERAL_BOOL, yytext), numLines);    return    TK_LIT_FALSE;}        
"true"                    {yylval.symbol = addSymbol(createToken(IKS_SIMBOLO_LITERAL_BOOL, yytext), numLines);        return    TK_LIT_TRUE;}


({ALPHA}|_)({ALPHA}|{DIGIT}|_)*    {yylval.symbol = addSymbol(createToken(IKS_SIMBOLO_IDENTIFICADOR, yytext), numLines); return    TK_IDENTIFICADOR;}                

-?{DIGIT}+                {yylval.symbol = addSymbol(createToken(IKS_SIMBOLO_LITERAL_INT, yytext), numLines);        return    TK_LIT_INT;}
-?{DIGIT}+"."{DIGIT}+    {yylval.symbol = addSymbol(createToken(IKS_SIMBOLO_LITERAL_FLOAT, yytext), numLines);     return    TK_LIT_FLOAT;}
"\'"."\'"                {yylval.symbol = addSymbol(createToken(IKS_SIMBOLO_LITERAL_CHAR, yytext), numLines);     return    TK_LIT_CHAR;}

\"(\\.|[^\\"])*\"        {yylval.symbol = addSymbol(createToken(IKS_SIMBOLO_LITERAL_STRING, yytext), numLines); return    TK_LIT_STRING;}

					
\n						{++numLines;}
[ \t]					{ }					
.						{return TOKEN_ERRO;}
			
%%
