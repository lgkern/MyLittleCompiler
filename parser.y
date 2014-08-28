/*
  Grupo MLC - Lucas e Helena
*/
%{
#include <stdio.h>
%}

%union {
   int ival;
   char *text;
   float fval;
}

/* Declaração dos tokens da linguagem */
%token TK_PR_INT	"INT"
%token TK_PR_FLOAT	"FLOAT"
%token TK_PR_BOOL	"BOOL"
%token TK_PR_CHAR	"CHAR"
%token TK_PR_STRING	"STRING"
%token TK_PR_IF		"IF"
%token TK_PR_THEN	"THEN"
%token TK_PR_ELSE	"ELSE"
%token TK_PR_WHILE	"WHILE"
%token TK_PR_DO		"DO"
%token TK_PR_INPUT	"INPUT"
%token TK_PR_OUTPUT	"OUTPUT"
%token TK_PR_RETURN	"RETURN"
%token TK_OC_LE		"<="
%token TK_OC_GE		">="
%token TK_OC_EQ		"=="
%token TK_OC_NE		"!="
%token TK_OC_AND	"&&"
%token TK_OC_OR		"||"
%token TK_LIT_INT	"litInt"
%token TK_LIT_FLOAT	"litFloat"
%token TK_LIT_FALSE	"false"
%token TK_LIT_TRUE	"true"
%token TK_LIT_CHAR	"litChar"
%token TK_LIT_STRING	"litString"
%token TK_IDENTIFICADOR	"ID"
%token TOKEN_ERRO	"ERRO"



%%
/* Regras (e ações) da gramática */

Program: 	/*empty*/
		|DeclStart Function 
		|DeclStart Global 

DeclStart:	Program Type "ID"

SC:	 	';'
		/*| "Error : Expected ;" */

Global:	 	Vector SC

Type:		"INT"
		|"FLOAT"
		|"BOOL"
		|"CHAR"
		|"STRING"

Vector: 	/*empty*/
		|'[' "litInt" ']'

Function:	Header Body Program
		
Header:		List

List:		'(' ParaList ')'

ParaList:	Parameter ',' ParaList
		| Parameter

Parameter: 	Local

Body:	 	'{' Block '}'

Block:		/*empty*/
		|Block Command

		

Command:	Local SC 
		| Attribution SC
		| FlowControl SC
		| Input SC
		| Output SC
		| Return SC 
		| Call SC 
		| Body
		| SC

Local:		Type "ID"

ID:		"ID" Vector

Attribution:	ID '=' Expression

Expression:	Literal
		| Expression OP Expression
		| UnaryOP Expression
		| '(' Expression ')'
		| Call

Literal:	"ID" Vector
		| Boolean
		| "litInteger"
		| "litFloat"

Boolean:	"false"
		|"true"

OP: 		'+'
		| '-'
		| '*'
		| '/'
		| '>'
		| '<'
		| "=="
		| ">="
		| "<="
		| "&&"
		| "||"

UnaryOP: 	'-'
		|'!'

Return: 	"RETURN" Expression

FlowControl:	If
		| While

If:		"IF" '(' Expression ')' "THEN" Body Else

Else:		/*empty*/
		|"ELSE" Body
		

While:	 	"WHILE" '(' Expression ')'  "DO" Body
		| "DO" Body "WHILE" '(' Expression ')' SC

Input:		"INPUT"  ID

Output:		"OUTPUT" ExpList

Call:		"ID" '(' ExpList ')'	

ExpList:	Expression ',' ExpList
		| Expression




%%
