/*
  Coloque aqui o identificador do grupo e dos seus membros
*/
ALPHA	[A-Za-z]
DIGIT	[0-9]
IDTERM	[ |\t]
INTEGER [-?{DIGIT}+]

%{
#include "parser.h" //arquivo automaticamente gerado pelo bison
char *p;
int numLines = 0;
%}			

%%
intIDTERM		return  TK_PR_INT;
floatIDTERM		return  TK_PR_FLOAT;
boolIDTERM		return  TK_PR_BOOL;
charIDTERM		return  TK_PR_CHAR;
stringIDTERM	return  TK_PR_STRING;
ifIDTERM		return  TK_PR_IF;
thenIDTERM		return  TK_PR_THEN;
elseIDTERM		return  TK_PR_ELSE;
whileIDTERM		return  TK_PR_WHILE;
doIDTERM		return  TK_PR_DO;
inputIDTERM		return  TK_PR_INPUT;
outputIDTERM	return  TK_PR_OUTPUT;
returnIDTERM	return  TK_PR_RETURN;

,				return	',';
;				return	';';
:				return	':';
(				return	'(';
)				return	')';
\[				return	'[';
\]				return	']';
\{				return	'{';
\}				return	'}';
\+				return	'+';
-				return	'-';
\*				return	'*';
/				return	'/';
<				return	'<';
>				return	'>';
=				return	'=';
!				return	'!';
&				return	'&';
$				return	'$';

<=				return	TK_PR_LE;
>=				return	TK_PR_GE;
==				return	TK_PR_EQ;
!=				return	TK_PR_NE;
&&				return	TK_PR_AND;
\|\|			return	TK_PR_OR;


{ALPHA_}{ALPHADIGIT_}*IDTERM		{
										p=(char *)calloc(strlen(yytext)+1,sizeof(char));
										strcpy(p,yytext);
										yylval.text=p;
										return	TK_IDENTIFICADOR
									}

INTEGER				{
						yylval.ival=atoi(yytext);
						return	TK_LIT_INT;
					}
INTEGER.{DIGIT}+	{
						p=(char *)calloc(strlen(yytext)+1,sizeof(char));
						strcpy(p,yytext);
						yylval.text=p;
						return	TK_LIT_FLOAT;
					}
false				{
						return	TK_LIT_FALSE;
					}
					
true				{
						return	TK_LIT_TRUE;
					}
'.'					{
						p=(char *)calloc(sizeof(char));
						*p = yytext[1];
						yylval.text=p;
						return	TK_LIT_CHAR;
					}
".*"				{
						p=(char *)calloc(strlen(yytext)+1,sizeof(char));
						strcpy(p,yytext);
						p++;
						p[strlen(p)-1] = '\0';						
						yylval.text=p;
						return	TK_LIT_STRING;
					}
					
\n					++numLines;
					
.					return TOKEN_ERRO;					
%%
