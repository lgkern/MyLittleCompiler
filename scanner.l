/*
  Coloque aqui o identificador do grupo e dos seus membros
*/
ALPHA	[A-Za-z]
DIGIT	[0-9]
INTEGER {-?{DIGIT}+}

%{
#include "parser.h" //arquivo automaticamente gerado pelo bison
char *p;
int numLines = 1;
%}			
%x IN_COMMENT


%%
<INITIAL>{
"/*"			BEGIN(IN_COMMENT);
}

<IN_COMMENT>{
"*/"			BEGIN(INITIAL);
[^*\n]+			// Eat comment in chunks
"*"				// Eat the lone star
\n				++numLines;
}

"int"			return  TK_PR_INT;
"float"			return  TK_PR_FLOAT;
"bool"			return  TK_PR_BOOL;
"char"			return  TK_PR_CHAR;
"string"		return  TK_PR_STRING;
"if"			return  TK_PR_IF;
"then"			return  TK_PR_THEN;
"else"			return  TK_PR_ELSE;
"while"			return  TK_PR_WHILE;
"do"			return  TK_PR_DO;
"input"			return  TK_PR_INPUT;
"output"		return  TK_PR_OUTPUT;
"return"		return  TK_PR_RETURN;

","				return	',';
";"				return	';';
":"				return	':';
"("				return	'(';
")"				return	')';
"["				return	'[';
"]"				return	']';
"{"				return	'{';
"}"				return	'}';
"+"				return	'+';
"-"/[ \t\n\r]	return	'-';
"*"				return	'*';
"/"				return	'/';
"<"				return	'<';
">"				return	'>';
"="				return	'=';
"!"				return	'!';
"&"				return	'&';
"$"				return	'$';

"<="				return	TK_OC_LE;
">="				return	TK_OC_GE;
"=="				return	TK_OC_EQ;
"!="				return	TK_OC_NE;
"&&"				return	TK_OC_AND;
"||"				return	TK_OC_OR;

"false"					{
							return	TK_LIT_FALSE;
						}
					
"true"					{
							return	TK_LIT_TRUE;
						}

({ALPHA}|_)({ALPHA}|{DIGIT}|_)*		{
											p=(char *)calloc(strlen(yytext)+1,sizeof(char));
											strcpy(p,yytext);
											yylval.text=p;
											return	TK_IDENTIFICADOR;
										}

-?{DIGIT}+				{
							yylval.ival=atoi(yytext);
							return	TK_LIT_INT;
						}

-?{DIGIT}+"."{DIGIT}+	{
							yylval.fval = atof(yytext);
							return	TK_LIT_FLOAT;
						}


"\'"."\'"				{
							p=(char *)calloc(1,sizeof(char));
							*p = yytext[1];
							yylval.text=p;
							return	TK_LIT_CHAR;
						}
"\"".*"\""				{
							p=(char *)calloc(strlen(yytext)+1,sizeof(char));
							strcpy(p,yytext);
							p++;
							p[strlen(p)-1] = '\0';						
							yylval.text=p;
							return	TK_LIT_STRING;
						}
					
\n						{++numLines;}
[ \t]					{ }					
.						{return TOKEN_ERRO;}
			
%%
