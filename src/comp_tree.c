#include "comp_tree.h"
#include "gv.h"
#include "iks_ast.h"
#include "main.h"
#include "symt.h"
#include <stdlib.h>
#include <stdio.h>

    nodeAST* createNodeAST(int type, nodeAST* next, void* symTable, ...)
    {
		char* temp = (char*)calloc(32, sizeof(char));
        nodeAST* node = calloc(1, sizeof(nodeAST));
        node->type = type;
        node->next = next;
        node->symTable = symTable;
        node->c1 = NULL;
        node->c2 = NULL;
        node->c3 = NULL;
		if(type == IKS_AST_IDENTIFICADOR || type == IKS_AST_FUNCAO)
			gv_declare(type, (void*)node, (char*)(((DIC*)symTable)->token->description.string));
		else if(type == IKS_AST_LITERAL)
		{
			if(((DIC*)symTable)->token->token == IKS_SIMBOLO_LITERAL_STRING)
				gv_declare(type, (void*)node, (char*)(((DIC*)symTable)->token->description.string));
			else if(((DIC*)symTable)->token->token == IKS_SIMBOLO_LITERAL_FLOAT)
			{
				sprintf(temp,"%f",(float)(((DIC*)symTable)->token->description.floating));
				gv_declare(type, (void*)node, temp);
			}
			else if(((DIC*)symTable)->token->token == IKS_SIMBOLO_LITERAL_BOOL)
			{
				if((int)(((DIC*)symTable)->token->description.integer) == 0)
					temp = "true";
				else if((int)(((DIC*)symTable)->token->description.integer) == 1)
					temp = "false";
				gv_declare(type, (void*)node, temp);
			}
			else if(((DIC*)symTable)->token->token == IKS_SIMBOLO_LITERAL_INT)
			{
				sprintf(temp,"%d",(int)(((DIC*)symTable)->token->description.integer));
				gv_declare(type, (void*)node, temp);
			}
			else if(((DIC*)symTable)->token->token == IKS_SIMBOLO_LITERAL_CHAR)
			{
				free(temp);
				temp = (char*)calloc(2, sizeof(char));
				temp[1] = '\0';
				temp[0] = (char)(((DIC*)symTable)->token->description.character);
				gv_declare(type, (void*)node, temp);
			}
		}
		else
			gv_declare(type, (void*)node, NULL);
        // va_list arg;
        // va_start (arg, next);//NodeAST type

		gv_connect((void*)node,(void*)next);
    }

    void insertNodeASTChild(nodeAST* parent, nodeAST* child, int index)
    {
        switch (index)
        {
            case 1:
                if (parent->c1 != NULL)
                {
                    trimNodeAST(parent->c1);
                }
                parent->c1 = child;
				gv_connect((void*)parent,(void*)child);
                break;

            case 2:
                if (parent->c2 != NULL)
                {
                    trimNodeAST(parent->c2);
                }
                parent->c2 = child;
				gv_connect((void*)parent,(void*)child);
                break;

            case 3:
                if (parent->c3 != NULL)
                {
                    trimNodeAST(parent->c3);
                }
                parent->c3 = child;
				gv_connect((void*)parent,(void*)child);
                break;

            default:
                free(child);//hue
        }
        return;
    }

    void    trimNodeAST(nodeAST* node)//tudo ligado ao nodo, inclusive next
    {
        if (node == NULL) //faz sentido dar free em null?
        {
            return;
        }
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

        return;
    }

    nodeAST*    destroyNodeAST(nodeAST* node)//só o nodo, retorna next
    {
        if (node == NULL) //faz sentido dar free em null?
        {
            return;
        }
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
        
        nodeAST* next = calloc(1, sizeof(nodeAST));//??
        next = node->next;
        
        free(node);

        return next;
    }

    void    modify(nodeAST* node, int index, ...)
    {
        if (node == NULL)
        {
            return;
        }
        
        return;//much done, very ready
    }



