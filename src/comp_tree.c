#include "comp_tree.h"
#include "gv.h"
#include "iks_ast.h"
#include "main.h"
#include "comp_dict.h"
#include "iloc.h"
#include "generators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

    void createAST(nodeAST* c1)
    {
        myAST = calloc(1, sizeof(nodeAST));
        myAST->type = IKS_AST_PROGRAMA;
        myAST->dataType = NONE;
        myAST->coersion = NONE;
        myAST->next = NULL;
        myAST->symTable = NULL;
        myAST->c1 = c1;

		//gv_declare(IKS_AST_PROGRAMA, (void*)myAST, NULL);	

		if(myAST->c1 != NULL)
			//gv_connect(myAST,myAST->c1);
        myAST->c2 = NULL;
        myAST->c3 = NULL;

		//gv_declare(IKS_AST_PROGRAMA, (void*)myAST, NULL);		
    }

	nodeAST* createNodeAST(int type, nodeAST* next, DIC* symTable, int dataType, int coersion, ...)
    {
		char* temp = NULL;
        nodeAST* node = calloc(1, sizeof(nodeAST));
        node->type = type;
        node->dataType = dataType;
        node->coersion = coersion;
        node->next = next;
        node->symTable = symTable;
        node->c1 = NULL;
        node->c2 = NULL;
        node->c3 = NULL;
        node->t = -1;
        node->f = -1;

        va_list arg;       
		va_start (arg, coersion);

		if(type == IKS_AST_PROGRAMA
		 ||type == IKS_AST_FUNCAO 
		 ||type == IKS_AST_INPUT 
		 ||type == IKS_AST_OUTPUT 
		 ||type == IKS_AST_ARIM_INVERSAO
		 ||type == IKS_AST_LOGICO_COMP_NEGACAO
		 ||type == IKS_AST_RETURN
		 ||type == IKS_AST_BLOCO) //1 Child
		{
			node->c1 = va_arg(arg,nodeAST*);
		}
		else if(type == IKS_AST_IF_ELSE) //3 Childs
		{
			node->c1 = va_arg(arg,nodeAST*);
			node->c2 = va_arg(arg,nodeAST*);
			node->c3 = va_arg(arg,nodeAST*);
		}
		else //2 Childs
		{
			node->c1 = va_arg(arg,nodeAST*);
			node->c2 = va_arg(arg,nodeAST*);
		}
		//printf("c1:%p        c2:%p            c3:%p\n",node->c1,node->c2,node->c3);
		
		va_end(arg);
/**********GV uses only *********************
		if(type == IKS_AST_IDENTIFICADOR || type == IKS_AST_FUNCAO)
		{
			//printf("type:%d        node:%p            symTable:%p\n",type, (void*)node, symTable->token->description.string);
			//gv_declare(type, (void*)node, (char*)symTable->token->description.string);
		}
		else if(type == IKS_AST_LITERAL)
		{
			if(symTable->token->token == IKS_SIMBOLO_LITERAL_STRING)
				gv_declare(type, (void*)node, (char*)(symTable->token->description.string));
			else if(symTable->token->token == IKS_SIMBOLO_LITERAL_FLOAT)
			{
				temp = (char*)calloc(32, sizeof(char));
				sprintf(temp,"%.2f",(float)symTable->token->description.floating);
				gv_declare(type, (void*)node, temp);
				free(temp);
			}
			else if(symTable->token->token == IKS_SIMBOLO_LITERAL_BOOL)
			{
				
				if((int)(symTable->token->description.integer) == 0)
				{
					temp = strdup("true");
					gv_declare(type, (void*)node, temp);
					free(temp);
				}
				else if((int)(symTable->token->description.integer) == 1)
				{
					temp = strdup("false");
					gv_declare(type, (void*)node, temp);
					free(temp);
				}
			}
			else if(symTable->token->token == IKS_SIMBOLO_LITERAL_INT)
			{
				temp = (char*)calloc(32, sizeof(char));
				sprintf(temp,"%d",(int)(symTable->token->description.integer));
				gv_declare(type, (void*)node, temp);
				free(temp);
			}
			else if(symTable->token->token == IKS_SIMBOLO_LITERAL_CHAR)
			{
				temp = (char*)calloc(2, sizeof(char));
				temp[1] = '\0';
				temp[0] = (char)(symTable->token->description.character);
				gv_declare(type, (void*)node, temp);
				free(temp);
			}
		}
		else
		{
			gv_declare(type, (void*)node, NULL);
		}

		if(node->next != NULL)
			//gv_connect(node,node->next);
		if(node->c1 != NULL)
		{
			//printf("Chamado de createAST, c1\n");
			//gv_connect(node,node->c1);
		}
		if(node->c2 != NULL)
		{
			//printf("Chamado de createAST, c2\n");
			//gv_connect(node,node->c2);
		}
		if(node->c3 != NULL)
		{
			//printf("Chamado de createAST, c3\n");
			//gv_connect(node,node->c3);
		}

*/
        
		return node;
    }

    void    trimNodeAST(nodeAST* node)//tudo ligado ao nodo, inclusive next
    {
        if (node != NULL) //faz sentido dar free em null?
        {
		    if (node->c1 != NULL)
		    {
		        destroyNodeAST(node->c1);
		    }
		    if (node->c2 != NULL)
		    {
		        destroyNodeAST(node->c2);
		    }
		    if (node->c3 != NULL)
		    {
		        destroyNodeAST(node->c3);
		    }
		    if (node->next != NULL)
		    {
		        destroyNodeAST(node->next);
		    }
        //ignora node->symTable já que a tabela ainda tem a referencia
       	 	free(node);
		}
    }

    nodeAST*    destroyNodeAST(nodeAST* node)//só o nodo, retorna next
    {
        nodeAST* next;
        if (node != NULL) //faz sentido dar free em null?
        {
		    if (node->c1 != NULL)
		    {
		        destroyNodeAST(node->c1);
		    }
		    if (node->c2 != NULL)
		    {
		        destroyNodeAST(node->c2);
		    }
		    if (node->c3 != NULL)
		    {
		        destroyNodeAST(node->c3);
		    }		        
 			// = calloc(1, sizeof(nodeAST));//??
        	next = node->next;        
		    free(node);
		    return next;
		}
		return NULL;
    }

    void    modify(nodeAST* node, int index, ...)
    {
        if (node != NULL)
		{	
			va_list arg;        
			va_start (arg, index);
			//printf("Modify node:%p\n\n", node);
			switch (index)
			{
				case 0:
					node->type = va_arg(arg,int);
					break;
				case 1:
					if(node->c1 != NULL){trimNodeAST(node->c1);}
					node->c1 = va_arg(arg,nodeAST*);
	/*				if(node->c1 != NULL)
					{
						//printf("Chamado de modify, c1\n");
						//gv_connect(node,node->c1);
					}*/
					break;
				case 2:
					if(node->c2 != NULL){trimNodeAST(node->c2);}
					node->c2 = va_arg(arg,nodeAST*);
	/*				if(node->c2 != NULL)
					{
						//printf("Chamado de modify, c2\n");
						//gv_connect(node,node->c2);
					}*/
					break;
				case 3:
					if(node->c3 != NULL){trimNodeAST(node->c3);}
					node->c3 = va_arg(arg,nodeAST*);
	/*				if(node->c3 != NULL)
					{
						//printf("Chamado de modify, c3\n");
						//gv_connect(node,node->c3);
					}*/
					break;
				case 4:
					if(node->next != NULL)
					{
						//printf("%p: %d, %p, %p, %p, %p\n",node, node->type, node->next, node->c1, node->c2, node->c3);
						trimNodeAST(node->next);	
					}
					node->next = va_arg(arg,nodeAST*);
					
	/*				if(node->next != NULL)
					{
						//printf("Chamado de modify, next\n");
						//gv_connect(node,node->next);
					}*/
					break;
				case 5:
					node->dataType = va_arg(arg,int);
					break;
				case 6:
					node->coersion = va_arg(arg,int);
					break;
				case 7:
					node->symTable = va_arg(arg,DIC*);

			}

			va_end(arg);
		}
    }

ILIST*  vectorDeviation(nodeAST* n, int reg)
{
	if(n->type == IKS_AST_VETOR_INDEXADO)
	{
		int tReg = genRegister();
		DIC* sTabEntry = (DIC*)n->symTable;
		nodeAST* exp = n->c2;
		ILIST* newList = createInstructionList(createInstruction(MULTI, exp->local, memory(sTabEntry->idType), reg, INT));
		newList = mergeInstructionLists(newList, createInstructionList(createInstruction(LOADAI, sTabEntry->baseRegister, sTabEntry->deviation, tReg, INT)));
		newList = mergeInstructionLists(newList, createInstructionList(createInstruction(ADDI, reg, tReg, reg)));
		return newList;
	}
	else if(n->type == IKS_AST_MULTI_VETOR)
	{
		int tReg = genRegister();
		DIC* sTabEntry = (DIC*)n->symTable;
		nodeAST* exp = n->c2;
		ARG* dimensions = sTabEntry->vectorSize;
		ILIST* newList = createInstructionList(createInstruction(LOADAI, sTabEntry->baseRegister, sTabEntry->deviation, reg, INT));
		
		while(dimensions->next != NULL)
		{
			newList = mergeInstructionLists(newList, createInstructionList(createInstruction(MULTI, exp->local, memory(sTabEntry->idType), tReg, INT)));
			newList = mergeInstructionLists(newList, createInstructionList(createInstruction(MULTI, tReg, dimensions->next->type, tReg, INT)));
			newList = mergeInstructionLists(newList, createInstructionList(createInstruction(ADD, tReg, reg, reg)));
			dimensions = dimensions->next;
			exp = exp->next;
		}
		newList = mergeInstructionLists(newList, createInstructionList(createInstruction(MULTI, exp->local, memory(sTabEntry->idType), tReg, INT)));
		newList = mergeInstructionLists(newList, createInstructionList(createInstruction(ADD, tReg, reg, reg)));
		return newList;
	}
	return NULL;
}
