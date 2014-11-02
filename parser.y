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
#include <stdlib.h>
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

%type <nAST> AST Program SC Global ID Vector Function Body Block Command Local MVector VExpList
%type <nAST> Attribution Expression  Return FlowControl If While Input Output Call FunctionID ExpList ';' '(' ')' 
%type <VarType> "INT" "FLOAT" "BOOL" "CHAR" "STRING" Type LocalFoo
%type <symbol> TK_IDENTIFICADOR TK_LIT_STRING TK_LIT_CHAR TK_LIT_TRUE TK_LIT_FALSE TK_LIT_FLOAT TK_LIT_INT Boolean Literal Header GlobalID 
%type <argList> List ParaList Parameter LitList 



%%
/* Regras (e ações) da gramática */

AST:	Program {createAST($1); printInstructionList($1->code);}

Program: 	{$$ = NULL;}
			|Global SC Program {$$ = $3;}
			|Function Program {modify($1, 4, $2); 
								if($2 != NULL)
									$1->code = mergeInstructionLists($1->code, $2->code);
								$$ = $1;}	
//			|error SC {yyerrok; yyclearin;}//yyclearin; yyerrok;}

SC:	 	';'
//		|error {}//yyclearin; yyerrok;}

/*{yyerrok;
		 printf("Missing semicolon at line %d",getLineNumber());
		 yyclearin;}
		|*/

Global:	 	Type GlobalID {modifyIdType($2,$1); allocateMemory($2);}

GlobalID:	"ID"  { variableExists($1);
					modifyIdSpec($1, VARIABLE); 
					$$ = $1;}
			| "ID" '[' "litInt" ']' {variableExists($1); modifyIdSpec($1, VECTOR); $1->vectorSize = createVector($3); $$ = $1;}
			| "ID" '[' LitList ']'  {variableExists($1); modifyIdSpec($1, MULTIVECTOR); $1->vectorSize = $3; $$ = $1;}

LitList:	"litInt" ',' "litInt"	{ARG* e1 = createVector($1); expandVector(e1, $3); $$ = e1;}
			|"litInt" ',' LitList	{ARG* e1 = createVector($1); e1->next = $3; $$ = e1;}

ID:		"ID" {DIC* entry = recursiveLookupDIC($1);  specCheck(entry, VARIABLE); $$ = createNodeAST(IKS_AST_IDENTIFICADOR, NULL, entry, entry->idType, NONE,  NULL, NULL, NULL);}
		|"ID" Vector {DIC* entry = recursiveLookupDIC($1); specCheck(entry, VECTOR); nodeAST* id = createNodeAST(IKS_AST_IDENTIFICADOR, NULL, entry, entry->idType, NONE, NULL, NULL, NULL); modify($2, 1, id); modify($2, DATA, entry->idType); modify($2, STABLE, entry); $$ = $2;}
		|"ID" MVector {DIC* entry = recursiveLookupDIC($1); specCheck(entry, MULTIVECTOR); checkMultiIndexer(entry, $2); nodeAST* id = createNodeAST(IKS_AST_IDENTIFICADOR, NULL, entry, entry->idType, NONE, NULL, NULL, NULL); modify($2, 1, id); modify($2, DATA, entry->idType); modify($2, STABLE, entry); $$ = $2;}

Type:	"INT" 		{$$ = INT;}
		|"FLOAT"	{$$ = FLOAT;}
		|"BOOL"		{$$ = BOOL;}
		|"CHAR"		{$$ = CHAR;}
		|"STRING"	{$$ = STRING;}

Vector: '[' Expression ']'	{checkIndexer($2); nodeAST* n = createNodeAST(IKS_AST_VETOR_INDEXADO, NULL, NULL, NONE, NONE, NULL, $2, NULL);
							 n->code = $2->code;
						     $$ = n;}
MVector: '[' VExpList ']'	{nodeAST* n = createNodeAST(IKS_AST_MULTI_VETOR, NULL, NULL, NONE, NONE, NULL, $2, NULL);
							 n->code = $2->code;
						     $$ = n;}

VExpList:	Expression ',' Expression 	{modify($1, NEXT, $3);	 $$ = $1;}
			|Expression ',' VExpList	{modify($1, NEXT, $3);	 $$ = $1;}

Function:	Header Body {nodeAST* n = createNodeAST(IKS_AST_FUNCAO, NULL, $1, $1->idType, NONE, $2);
						 n->code = $2->code;
						 $$ = n;}
		
Header:		Type "ID" {addScope($1);} List { variableExists($2); modifyIdType($2,$1); modifyIdSpec($2, FUNCTION); addFunctionArg($2,$4);/* printf("\nFunction Declared: = %p\n",$2);*/ $$ = $2;}

List:	'(' ParaList ')' {$$ = $2;}
		|'(' ')' {$$ = NULL;}

ParaList:	Parameter ',' ParaList {$1->next = $3; $$ = $1;}
		| Parameter {$$ = $1;}

Parameter: 	LocalFoo {$$ = createArg($1);}

Body:	 	'{' Block '}' {removeScope(); $$ = $2;}

Block:	{$$ = NULL;}	/*empty*/
		|Command	{$$ = $1; /*pq não tem next mesmo*/ }
		|Command SC Block	{
								if($1 == NULL) 
								{
									$$ = $3; 
							 	} 
							 	else
							 	{
							 		modify($1, 4, $3); /*set $3 como next do comando, tudo bem ser NULL*/									
									if($3 != NULL) $1->code = mergeInstructionLists($1->code, $3->code);
									$$ = $1;
								} }

Command: Local  {$$ = NULL;}
		| Attribution {$$ = $1;}
		| FlowControl
		| Input 
		| Output 
		| Return  
		| Call { $$ = $1; }  
		| {addScopeNonF();} Body { $$ = createNodeAST(IKS_AST_BLOCO,NULL,NULL, NONE, NONE, $2);}
		| SC

Local:		Type "ID" {variableExists($2); modifyIdType($2,$1); modifyIdSpec($2, VARIABLE); allocateMemory($2); $$ = NULL;}

LocalFoo:		Type "ID" {variableExists($2); modifyIdType($2,$1); modifyIdSpec($2, VARIABLE); $$ = $1;}

Attribution:	ID '=' Expression {nodeAST* n = createNodeAST(IKS_AST_ATRIBUICAO, NULL, NULL, typeCompatibility($1, $3), coerced($1->dataType, $3->dataType), $1, $3);  
									n->local = genRegister(); //same semantics as C 
									ILIST* vDev = vectorDeviation($1, n->local);
									if(vDev == NULL)
									{
										$1->code = createInstructionList(createInstruction(STOREAI, $3->local, ((DIC*)($1->symTable))->baseRegister, ((DIC*)($1->symTable))->deviation));
										n->code = mergeInstructionLists($3->code, $1->code);
									}
									else
									{										
										$1->code = mergeInstructionLists($1->code, vDev); 
										n->code = mergeInstructionLists($1->code, $3->code);
										n->code = mergeInstructionLists(n->code, createInstructionList(createInstruction(STOREA0, $3->local, ((DIC*)($1->symTable))->baseRegister, n->local)));
									}
									
									$$ = n;}

Expression:	ID {$1->local = genRegister(); 
				$1-> code = createInstructionList(createInstruction(LOADAI,((DIC*)($1->symTable))->baseRegister, ((DIC*)($1->symTable))->deviation, $1->local));	
				$$ = $1;}
		| Literal {		
						nodeAST* n = createNodeAST(IKS_AST_LITERAL, NULL, $1, $1->idType, NONE, NULL, NULL, NULL); 
						n->local = genRegister();
					//	printf("description = %d",$1->token->description.integer);
						n->code = createInstructionList(createInstruction(LOADI,$1->token->description, n->local, $1->idType));
						$$ = n;}
		| Expression '+' Expression {nodeAST* n = createNodeAST(IKS_AST_ARIM_SOMA, NULL, NULL, typeCompatibility($1, $3), coerced($1->dataType, $3->dataType), $1, $3); 
									n->local = genRegister();
									n->code = mergeInstructionLists($1->code, $3->code);
									addInstruction(n->code, createInstruction(ADD, $1->local, $3->local, n->local));
									$$ = n;}
		| Expression '-' Expression {nodeAST* n =createNodeAST(IKS_AST_ARIM_SUBTRACAO, NULL, NULL, typeCompatibility($1, $3), coerced($1->dataType, $3->dataType), $1, $3); 
									n->local = genRegister();
									n->code = mergeInstructionLists($1->code, $3->code);
									addInstruction(n->code, createInstruction(SUB, $1->local, $3->local, n->local));
									$$ = n;}
		| Expression '*' Expression {nodeAST* n =createNodeAST(IKS_AST_ARIM_MULTIPLICACAO, NULL, NULL, typeCompatibility($1, $3), coerced($1->dataType, $3->dataType), $1, $3); 
									n->local = genRegister();
									n->code = mergeInstructionLists($1->code, $3->code);
									addInstruction(n->code, createInstruction(MULT, $1->local, $3->local, n->local));
									$$ = n;}
		| Expression '/' Expression {nodeAST* n =createNodeAST(IKS_AST_ARIM_DIVISAO, NULL, NULL, typeCompatibility($1, $3), coerced($1->dataType, $3->dataType), $1, $3); 
									n->local = genRegister();
									n->code = mergeInstructionLists($1->code, $3->code);
									addInstruction(n->code, createInstruction(DIV, $1->local, $3->local, n->local));
									$$ = n;}
		| Expression '>' Expression {nodeAST* n =createNodeAST(IKS_AST_LOGICO_COMP_G, NULL, NULL, typeCompatibility($1, $3), coerced($1->dataType, $3->dataType), $1, $3); 
									n->local = genRegister();
									n->code = mergeInstructionLists($1->code, $3->code);
									addInstruction(n->code, createInstruction(CMP_GT, $1->local, $3->local, n->local));
									$$ = n;}
		| Expression '<' Expression {nodeAST* n =createNodeAST(IKS_AST_LOGICO_COMP_L, NULL, NULL, typeCompatibility($1, $3), coerced($1->dataType, $3->dataType), $1, $3); 
									n->local = genRegister();
									n->code = mergeInstructionLists($1->code, $3->code);
									addInstruction(n->code, createInstruction(CMP_LT, $1->local, $3->local, n->local));
									$$ = n;}
		| Expression "==" Expression {nodeAST* n =createNodeAST(IKS_AST_LOGICO_COMP_IGUAL, NULL, NULL, typeCompatibility($1, $3), coerced($1->dataType, $3->dataType), $1, $3); 
									n->local = genRegister();
									n->code = mergeInstructionLists($1->code, $3->code);
									addInstruction(n->code, createInstruction(CMP_EQ, $1->local, $3->local, n->local));
									$$ = n;}
		| Expression "!=" Expression {nodeAST* n =createNodeAST(IKS_AST_LOGICO_COMP_DIF, NULL, NULL, typeCompatibility($1, $3), coerced($1->dataType, $3->dataType), $1, $3); 
									n->local = genRegister();
									n->code = mergeInstructionLists($1->code, $3->code);
									addInstruction(n->code, createInstruction(CMP_NE, $1->local, $3->local, n->local));
									$$ = n;}
		| Expression ">=" Expression {nodeAST* n =createNodeAST(IKS_AST_LOGICO_COMP_GE, NULL, NULL, typeCompatibility($1, $3), coerced($1->dataType, $3->dataType), $1, $3); 
									n->local = genRegister();
									n->code = mergeInstructionLists($1->code, $3->code);
									addInstruction(n->code, createInstruction(CMP_GE, $1->local, $3->local, n->local));
									$$ = n;}
		| Expression "<=" Expression {nodeAST* n =createNodeAST(IKS_AST_LOGICO_COMP_LE, NULL, NULL, typeCompatibility($1, $3), coerced($1->dataType, $3->dataType), $1, $3); 
									n->local = genRegister();
									n->code = mergeInstructionLists($1->code, $3->code);
									addInstruction(n->code, createInstruction(CMP_LE, $1->local, $3->local, n->local));
									$$ = n;}
		| Expression "&&" Expression {nodeAST* n =createNodeAST(IKS_AST_LOGICO_E, NULL, NULL, typeCompatibility($1, $3), coerced($1->dataType, $3->dataType), $1, $3); 
									n->local = genRegister();
									n->code = mergeInstructionLists($1->code, $3->code);
									addInstruction(n->code, createInstruction(AND, $1->local, $3->local, n->local));
									$$ = n;}
		| Expression "||" Expression {nodeAST* n =createNodeAST(IKS_AST_LOGICO_OU, NULL, NULL, typeCompatibility($1, $3), coerced($1->dataType, $3->dataType), $1, $3); 
									n->local = genRegister();
									n->code = mergeInstructionLists($1->code, $3->code);
									addInstruction(n->code, createInstruction(OR, $1->local, $3->local, n->local));
									$$ = n;}
		| '-' Expression {$$=createNodeAST(IKS_AST_ARIM_INVERSAO, NULL, NULL, $2->dataType, NONE, $2); }
		| '!' Expression {$$=createNodeAST(IKS_AST_LOGICO_COMP_NEGACAO, NULL, NULL, $2->dataType, NONE, $2); }
		| '(' Expression ')' {$$ = $2;}
		| Call

Literal: Boolean		{modifyIdType($1,BOOL); $$ = $1;}
		|"litInt"		{modifyIdType($1,INT); $$ = $1;}
		|"litFloat"		{modifyIdType($1,FLOAT); $$ = $1;}
		|"litChar"		{modifyIdType($1,CHAR); $$ = $1;}
		|"litString"	{modifyIdType($1,STRING); $$ = $1;}

Boolean:	"false" {$$ = $1;}
			|"true" {$$ = $1;}

Return: 	"RETURN" Expression {returnValidation($2); $$ = createNodeAST(IKS_AST_RETURN, NULL, NULL, $2->dataType, NONE, $2); }

FlowControl:	If
		| While

If:		"IF" '(' Expression ')' "THEN" Command {nodeAST* n = createNodeAST(IKS_AST_IF_ELSE, NULL, NULL, NONE, NONE, $3, $6, NULL); 
							n->t = genLabel();
							n->f = genLabel();
							addInstruction($3->code, createInstruction(CBR, $3->local, n->t, n->f));
							ILIST* comm = createInstructionList(createInstruction(NOP));
							comm = mergeInstructionLists(comm, $6->code);
							addInstructionLabel(comm->instruction, n->t);
							INST* next = createInstruction(NOP);
							addInstructionLabel(next, n->f);
							n->code = mergeInstructionLists($3->code, comm);
							addInstruction(n->code, next);
							$$ = n;}
		|"IF" '(' Expression ')' "THEN" Command "ELSE" Command	{nodeAST* n = createNodeAST(IKS_AST_IF_ELSE, NULL, NULL, NONE, NONE, $3, $6, $8); 
							n->t = genLabel();
							n->f = genLabel();
							addInstruction($3->code, createInstruction(CBR, $3->local, n->t, n->f));
							ILIST* commtrue = createInstructionList(createInstruction(NOP));
							commtrue = mergeInstructionLists(commtrue, $3->code);
							ILIST* commfalse = createInstructionList(createInstruction(NOP));
							commfalse = mergeInstructionLists(commfalse, $6->code);
							addInstructionLabel(commtrue->instruction, n->t);
							addInstructionLabel(commfalse->instruction, n->f);
							n->code = mergeInstructionLists($3->code, commtrue);
							n->code = mergeInstructionLists(n->code, commfalse);
							$$ = n;}

While:	 "WHILE" '(' Expression ')'  "DO" Command {nodeAST* n = createNodeAST(IKS_AST_WHILE_DO, NULL, NULL, NONE, NONE, $3, $6); 
							n->t = genLabel();
							n->f = genLabel();
							addInstruction($3->code, createInstruction(CBR, $3->local, n->t, n->f));
							INST* next = createInstruction(NOP);
							INST* begin = createInstruction(NOP);
							ILIST* comm = mergeInstructionLists(createInstructionList(createInstruction(NOP)), $6->code);
							addInstructionLabel(begin, genLabel());
							addInstruction(comm, createInstruction(JUMPI, begin->instLabel));
							addInstructionLabel(comm->instruction, n->t);
							addInstructionLabel(next, n->f);
							n->code = mergeInstructionLists(createInstructionList(begin), $3->code);
							n->code = mergeInstructionLists(n->code, comm);
							addInstruction(n->code, next);
							$$ = n;}
		| "DO" Command "WHILE" '(' Expression ')' SC {nodeAST* n = createNodeAST(IKS_AST_DO_WHILE, NULL, NULL, NONE, NONE, $2, $5); 
							n->t = genLabel();
							n->f = genLabel();
							addInstruction($5->code, createInstruction(CBR, $5->local, n->t, n->f));
							INST* next = createInstruction(NOP);
							INST* begin = createInstruction(NOP);
							addInstructionLabel(begin, n->t);
							addInstructionLabel(next, n->f);
							n->code = mergeInstructionLists(createInstructionList(begin), $2->code);
							n->code = mergeInstructionLists(n->code, $5->code);
							addInstruction(n->code, next);
							$$ = n;}

Input:		"INPUT"  ID	{$$ = createNodeAST(IKS_AST_INPUT, NULL, NULL, NONE, NONE, $2); }

Output:		"OUTPUT" ExpList {outputValidation($2); $$ = createNodeAST(IKS_AST_OUTPUT, NULL, NULL, NONE, NONE, $2); }

Call:	FunctionID '(' ExpList ')' {functionCompatibility($1, $3); $$ = createNodeAST(IKS_AST_CHAMADA_DE_FUNCAO, NULL, NULL, $1->dataType, NONE, $1, $3);}
		|FunctionID '(' ')'	{functionCompatibility($1, NULL); $$ = createNodeAST(IKS_AST_CHAMADA_DE_FUNCAO, NULL, NULL, $1->dataType, NONE, $1, NULL);}

FunctionID: "ID" {DIC* entry = recursiveLookupDIC($1); specCheck(entry,FUNCTION);
				  $$ = createNodeAST(IKS_AST_IDENTIFICADOR, NULL, $1, entry->idType, NONE, NULL, NULL, NULL);}

ExpList:	Expression ',' ExpList {modify($1, 4, $3); $$ = $1;}
		| Expression { $$ = $1; }




%%
