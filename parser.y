/*
  Grupo MLC - Lucas e Helena
*/
%{
#include <stdio.h>
#include "iks_ast.h"
#include "comp_tree.h"
%}

%union {
   void* symbol;
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
%left '+'
%left '-'
%left '!'
%left '*'
%left '/'
%left '>'
%left '<'
%left "<=" ">=" "==" "!=" "&&" "||"
%right "INT" "FLOAT" "BOOL" "CHAR" "STRING" "THEN" "ELSE"

%error-verbose

%type <symbol> AST Program SC Global ID Type Vector Function Header List ParaList Parameter Body Block Command
%type <symbol> Local Attribution Expression Literal Boolean Return FlowControl If While Input Output Call FunctionID ExpList
%type <symbol> TK_IDENTIFICADOR TK_LIT_STRING TK_LIT_CHAR TK_LIT_TRUE TK_LIT_FALSE TK_LIT_FLOAT TK_LIT_INT
%type <symbol> "INT" "FLOAT" "BOOL" "CHAR" "STRING" ';' '(' ')'


%%
/* Regras (e ações) da gramática */

AST:	Program {createAST($1);}

Program: 	{$$ = NULL;}
			|Global SC Program 
			|Function Program {$$ = createNodeAST(IKS_AST_FUNCAO, $2, yylval.symbol, $1); }	
//			|error SC {yyerrok; yyclearin;}//yyclearin; yyerrok;}

SC:	 	';'
//		|error {}//yyclearin; yyerrok;}

/*{yyerrok;
		 printf("Missing semicolon at line %d",getLineNumber());
		 yyclearin;}
		|*/

Global:	 	Type ID

ID:		"ID" {$$ = createNodeAST(IKS_AST_IDENTIFICADOR, NULL, yylval.symbol);}
		|"ID" Vector {nodeAST* id = createNodeAST(IKS_AST_IDENTIFICADOR, NULL, yylval.symbol); modify($2, 1, id); $$ = $2;}

Type:	"INT"
		|"FLOAT"
		|"BOOL"
		|"CHAR"
		|"STRING"

Vector: '[' Expression ']'	{$$ = createNodeAST(IKS_AST_VETOR_INDEXADO, NULL, NULL, $2);/*lembrando que esse filhote é o segundo e não o primeiro*/ }

Function:	Header Body {$$ = $2;}
		
Header:		Type "ID" List

List:	'(' ParaList ')'
		|'(' ')'

ParaList:	Parameter ',' ParaList
		| Parameter

Parameter: 	Local

Body:	 	'{' Block '}' {$$ = $2;}

Block:	{$$ = NULL;}	/*empty*/
		|Command	{$$ = $1; /*pq não tem next mesmo*/ }
		|Command SC Block	{modify($1, 4, $3); /*set $3 como next do comando*/ $$ = $1; }

Command: Local  
		| Attribution 
		| FlowControl
		| Input 
		| Output 
		| Return  
		| Call  
		| Body
		| SC

Local:		Type "ID"

Attribution:	ID '=' Expression {$$ = createNodeAST(IKS_AST_ATRIBUICAO, NULL, NULL, $1, $3); }

Expression:	Literal {if($1 != NULL){$$=$1;} else $$=createNodeAST(IKS_AST_LITERAL, NULL, yylval.symbol); }
		| Expression '+' Expression {$$=createNodeAST(IKS_AST_ARIM_SOMA, NULL, NULL, $1, $3); }
		| Expression '-' Expression {$$=createNodeAST(IKS_AST_ARIM_SUBTRACAO, NULL, NULL, $1, $3); }
		| Expression '*' Expression {$$=createNodeAST(IKS_AST_ARIM_MULTIPLICACAO, NULL, NULL, $1, $3); }
		| Expression '/' Expression {$$=createNodeAST(IKS_AST_ARIM_DIVISAO, NULL, NULL, $1, $3); }
		| Expression '>' Expression {$$=createNodeAST(IKS_AST_LOGICO_COMP_G, NULL, NULL, $1, $3); }
		| Expression '<' Expression {$$=createNodeAST(IKS_AST_LOGICO_COMP_L, NULL, NULL, $1, $3); }
		| Expression "==" Expression {$$=createNodeAST(IKS_AST_LOGICO_COMP_IGUAL, NULL, NULL, $1, $3); }
		| Expression "!=" Expression {$$=createNodeAST(IKS_AST_LOGICO_COMP_DIF, NULL, NULL, $1, $3); }
		| Expression ">=" Expression {$$=createNodeAST(IKS_AST_LOGICO_COMP_GE, NULL, NULL, $1, $3); }
		| Expression "<=" Expression {$$=createNodeAST(IKS_AST_LOGICO_COMP_LE, NULL, NULL, $1, $3); }
		| Expression "&&" Expression {$$=createNodeAST(IKS_AST_LOGICO_E, NULL, NULL, $1, $3); }
		| Expression "||" Expression {$$=createNodeAST(IKS_AST_LOGICO_OU, NULL, NULL, $1, $3); }
		| '-' Expression {$$=createNodeAST(IKS_AST_ARIM_INVERSAO, NULL, NULL, $2); }
		| '!' Expression {$$=createNodeAST(IKS_AST_LOGICO_COMP_NEGACAO, NULL, NULL, $2); }
		| '(' Expression ')'
		| Call

Literal: ID
		|Boolean
		|"litInt"
		|"litFloat"
		|"litChar"
		|"litString"

Boolean:	"false"
			|"true"

Return: 	"RETURN" Expression {$$ = createNodeAST(IKS_AST_RETURN, NULL, NULL, $2); }

FlowControl:	If
		| While

If:		"IF" '(' Expression ')' "THEN" Command {$$ = createNodeAST(IKS_AST_IF_ELSE, NULL, NULL, $3, $6); }
		|"IF" '(' Expression ')' "THEN" Command "ELSE" Command	{$$ = createNodeAST(IKS_AST_IF_ELSE, NULL, NULL, $3, $6, $8); }

While:	 "WHILE" '(' Expression ')'  "DO" Command {$$ = createNodeAST(IKS_AST_WHILE_DO, NULL, NULL, $3, $6); }
		| "DO" Command "WHILE" '(' Expression ')' SC {$$ = createNodeAST(IKS_AST_DO_WHILE, NULL, NULL, $2, $5); }

Input:		"INPUT"  ID	{$$ = createNodeAST(IKS_AST_INPUT, NULL, NULL, $2); }

Output:		"OUTPUT" ExpList {$$ = createNodeAST(IKS_AST_OUTPUT, NULL, NULL, $2); }

Call:	FunctionID '(' ExpList ')' {$$ = createNodeAST(IKS_AST_CHAMADA_DE_FUNCAO, NULL, NULL, $3);}
		|FunctionID '(' ')'	{$$ = createNodeAST(IKS_AST_CHAMADA_DE_FUNCAO, NULL, NULL);}

FunctionID: "ID" {$$ = createNodeAST(IKS_AST_IDENTIFICADOR, NULL, yylval.symbol);}

ExpList:	Expression ',' ExpList {modify($1, 4, $3); $$ = $1;}
		| Expression




%%
