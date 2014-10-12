/*
  Grupo MLC - Lucas e Helena
*/
%{
#include <stdio.h>
#include "iks_ast.h"
#include "comp_tree.h"
#include "comp_dict.h"
#include "semantics.h"
#include "main.h"
%}

%union {
   DIC* symbol;
   nodeAST* nAST;
   int VarType;
   ARG* argList;
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

%right "THEN" "ELSE"
%right "||"
%right "&&"
%left '>' '<' "==" "!=" "<=" ">="
%left '-' '+'
%left '*' '/'
%right '!'
%nonassoc '(' ')'

%right "INT" "FLOAT" "BOOL" "CHAR" "STRING"

%error-verbose

%type <nAST> AST Program SC Global ID Vector Function Body Block Command Local 
%type <nAST> Attribution Expression  Return FlowControl If While Input Output Call FunctionID ExpList ';' '(' ')'
%type <VarType> "INT" "FLOAT" "BOOL" "CHAR" "STRING" Type LocalFoo
%type <symbol> TK_IDENTIFICADOR TK_LIT_STRING TK_LIT_CHAR TK_LIT_TRUE TK_LIT_FALSE TK_LIT_FLOAT TK_LIT_INT Boolean Literal Header GlobalID 
%type <argList> List ParaList Parameter



%%
/* Regras (e ações) da gramática */

AST:	Program {createAST($1);}

Program: 	{$$ = NULL;}
			|Global SC Program {$$ = $3;}
			|Function Program {modify($1, 4, $2); $$ = $1;}	
//			|error SC {yyerrok; yyclearin;}//yyclearin; yyerrok;}

SC:	 	';'
//		|error {}//yyclearin; yyerrok;}

/*{yyerrok;
		 printf("Missing semicolon at line %d",getLineNumber());
		 yyclearin;}
		|*/

Global:	 	Type GlobalID {modifyIdType($2,$1); }

GlobalID:	"ID"  { variableExists($1);
					modifyIdSpec($1, VARIABLE); 
					$$ = $1;
					}
			| "ID" '[' Literal ']'  {variableExists($1); modifyIdSpec($1, VECTOR); $$ = $1;}

ID:		"ID" {DIC* entry = recursiveLookupDIC($1); specCheck(entry, VARIABLE); $$ = createNodeAST(IKS_AST_IDENTIFICADOR, NULL, $1, entry->idType,  NULL, NULL, NULL);}
		|"ID" Vector {DIC* entry = recursiveLookupDIC($1); specCheck(entry, VECTOR); nodeAST* id = createNodeAST(IKS_AST_IDENTIFICADOR, NULL, $1, entry->idType, NULL, NULL, NULL); modify($2, 1, id); $$ = $2;}

Type:	"INT" 		{$$ = INT;}
		|"FLOAT"	{$$ = FLOAT;}
		|"BOOL"		{$$ = BOOL;}
		|"CHAR"		{$$ = CHAR;}
		|"STRING"	{$$ = STRING;}

Vector: '[' Expression ']'	{$$ = createNodeAST(IKS_AST_VETOR_INDEXADO, NULL, NULL,NONE, NULL, $2, NULL);}

Function:	Header Body {$$ = createNodeAST(IKS_AST_FUNCAO, NULL, $1, $1->idType, $2);}
		
Header:		Type "ID" {addScope($1);} List { variableExists($2); modifyIdType($2,$1); modifyIdSpec($2, FUNCTION); addFunctionArg($2,$4);/* printf("\nFunction Declared: = %p\n",$2);*/ $$ = $2;}

List:	'(' ParaList ')' {$$ = $2;}
		|'(' ')' {$$ = NULL;}

ParaList:	Parameter ',' ParaList {$1->next = $3; $$ = $1;}
		| Parameter {$$ = $1;}

Parameter: 	LocalFoo {$$ = createArg($1);}

Body:	 	'{' Block '}' {removeScope(); $$ = $2;}

Block:	{$$ = NULL;}	/*empty*/
		|Command	{$$ = $1; /*pq não tem next mesmo*/ }
		|Command SC Block	{if($1 == NULL) { $$ = $3; } else {modify($1, 4, $3); /*set $3 como next do comando*/ $$ = $1;} }

Command: 	Local  
		| Attribution 
		| FlowControl
		| Input 
		| Output 
		| Return  
		| Call { $$ = $1; }  
		| Body { $$ = createNodeAST(IKS_AST_BLOCO,NULL,NULL, NONE,$1);}
		| SC

Local:		Type "ID" {variableExists($2); modifyIdType($2,$1); modifyIdSpec($2, VARIABLE);}

LocalFoo:		Type "ID" {variableExists($2); modifyIdType($2,$1); modifyIdSpec($2, VARIABLE); $$ = $1;}

Attribution:	ID '=' Expression {$$ = createNodeAST(IKS_AST_ATRIBUICAO, NULL, NULL, typeCompatibility($1, $3), $1, $3); }

Expression:	ID
		| Literal {$$=createNodeAST(IKS_AST_LITERAL, NULL, $1, $1->idType, NULL, NULL, NULL); }
		| Expression '+' Expression {$$=createNodeAST(IKS_AST_ARIM_SOMA, NULL, NULL, typeCompatibility($1, $3), $1, $3); }
		| Expression '-' Expression {$$=createNodeAST(IKS_AST_ARIM_SUBTRACAO, NULL, NULL, typeCompatibility($1, $3), $1, $3); }
		| Expression '*' Expression {$$=createNodeAST(IKS_AST_ARIM_MULTIPLICACAO, NULL, NULL, typeCompatibility($1, $3), $1, $3); }
		| Expression '/' Expression {$$=createNodeAST(IKS_AST_ARIM_DIVISAO, NULL, NULL, typeCompatibility($1, $3), $1, $3); }
		| Expression '>' Expression {$$=createNodeAST(IKS_AST_LOGICO_COMP_G, NULL, NULL, typeCompatibility($1, $3), $1, $3); }
		| Expression '<' Expression {$$=createNodeAST(IKS_AST_LOGICO_COMP_L, NULL, NULL, typeCompatibility($1, $3), $1, $3); }
		| Expression "==" Expression {$$=createNodeAST(IKS_AST_LOGICO_COMP_IGUAL, NULL, NULL, typeCompatibility($1, $3), $1, $3); }
		| Expression "!=" Expression {$$=createNodeAST(IKS_AST_LOGICO_COMP_DIF, NULL, NULL, typeCompatibility($1, $3), $1, $3); }
		| Expression ">=" Expression {$$=createNodeAST(IKS_AST_LOGICO_COMP_GE, NULL, NULL, typeCompatibility($1, $3), $1, $3); }
		| Expression "<=" Expression {$$=createNodeAST(IKS_AST_LOGICO_COMP_LE, NULL, NULL, typeCompatibility($1, $3), $1, $3); }
		| Expression "&&" Expression {$$=createNodeAST(IKS_AST_LOGICO_E, NULL, NULL, typeCompatibility($1, $3), $1, $3); }
		| Expression "||" Expression {$$=createNodeAST(IKS_AST_LOGICO_OU, NULL, NULL, typeCompatibility($1, $3), $1, $3); }
		| '-' Expression {$$=createNodeAST(IKS_AST_ARIM_INVERSAO, NULL, NULL, $2->dataType, $2); }
		| '!' Expression {$$=createNodeAST(IKS_AST_LOGICO_COMP_NEGACAO, NULL, NULL, $2->dataType, $2); }
		| '(' Expression ')' {$$ = $2;}
		| Call

Literal: Boolean		{modifyIdType($1,BOOL); $$ = $1;}
		|"litInt"		{modifyIdType($1,INT); $$ = $1;}
		|"litFloat"		{modifyIdType($1,FLOAT); $$ = $1;}
		|"litChar"		{modifyIdType($1,CHAR); $$ = $1;}
		|"litString"	{modifyIdType($1,STRING); $$ = $1;}

Boolean:	"false"
			|"true"

Return: 	"RETURN" Expression {returnValidation($2); $$ = createNodeAST(IKS_AST_RETURN, NULL, NULL, $2->dataType, $2); }

FlowControl:	If
		| While

If:		"IF" '(' Expression ')' "THEN" Command {$$ = createNodeAST(IKS_AST_IF_ELSE, NULL, NULL, NONE, $3, $6, NULL); }
		|"IF" '(' Expression ')' "THEN" Command "ELSE" Command	{$$ = createNodeAST(IKS_AST_IF_ELSE, NULL, NULL, NONE, $3, $6, $8); }

While:	 "WHILE" '(' Expression ')'  "DO" Command {$$ = createNodeAST(IKS_AST_WHILE_DO, NULL, NULL, NONE, $3, $6); }
		| "DO" Command "WHILE" '(' Expression ')' SC {$$ = createNodeAST(IKS_AST_DO_WHILE, NULL, NULL, NONE, $2, $5); }

Input:		"INPUT"  ID	{$$ = createNodeAST(IKS_AST_INPUT, NULL, NULL, NONE, $2); }

Output:		"OUTPUT" ExpList {outputValidation($2); $$ = createNodeAST(IKS_AST_OUTPUT, NULL, NULL, NONE, $2); }

Call:	FunctionID '(' ExpList ')' {functionCompatibility($1, $3); $$ = createNodeAST(IKS_AST_CHAMADA_DE_FUNCAO, NULL, NULL, $1->dataType, $1, $3);}
		|FunctionID '(' ')'	{functionCompatibility($1, NULL); $$ = createNodeAST(IKS_AST_CHAMADA_DE_FUNCAO, NULL, NULL, $1->dataType, $1, NULL);}

FunctionID: "ID" {DIC* entry = recursiveLookupDIC($1); specCheck(entry,FUNCTION);
				  $$ = createNodeAST(IKS_AST_IDENTIFICADOR, NULL, $1, entry->idType, NULL, NULL, NULL);}

ExpList:	Expression ',' ExpList {modify($1, 4, $3); $$ = $1;}
		| Expression { $$ = $1; }




%%
