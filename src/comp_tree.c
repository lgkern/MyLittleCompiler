#include "comp_tree.h"
#include <stdlib.h>
#include <stdio.h>

    void createAST(nodeAST* c1)
    {
        myAST = calloc(1, sizeof(nodeAST));
        myAST->type = IKS_AST_PROGRAMA;
        myAST->next = NULL;
        myAST->symTable = NULL;
        myAST->c1 = c1;
        myAST->c2 = NULL;
        myAST->c3 = NULL;
		return;
    }

	nodeAST* createNodeAST(int type, nodeAST* next, void* symTable, ...)
    {
        nodeAST* node = calloc(1, sizeof(nodeAST));
        node->type = type;
        node->next = next;
        node->symTable = symTable;
        node->c1 = NULL;
        node->c2 = NULL;
        node->c3 = NULL;

        va_list arg;
        nodeAST* child = va_start (arg, next);
		if(type == IKS_AST_VETOR_INDEXADO)
		{
			node->c2 = child;
		}
		else
		{
			node->c1 = child;
			node->c2 = va_start (arg, next);
			node->c3 = va_start (arg, next);
		}

		return node;
    }

    /*void insertNodeASTChild(nodeAST* parent, nodeAST* child, int index) //já tem no modify
    {
        switch (index)
        {
            case 1:
                if (parent->c1 != NULL)
                {
                    trimNodeAST(parent->c1);
                }
                parent->c1 = child;
                break;

            case 2:
                if (parent->c2 != NULL)
                {
                    trimNodeAST(parent->c2);
                }
                parent->c2 = child;
                break;

            case 3:
                if (parent->c3 != NULL)
                {
                    trimNodeAST(parent->c3);
                }
                parent->c3 = child;
                break;

            default:
                free(child);//hue
        }
        return;
    }*/

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

		va_list arg;        
		switch (index)
		{
			case 0:
				node->type = va_start (arg, index);
				break;
			case 1:
				if(node->c1 != NULL){trimNodeAST(node->c1);}
				node->c1 = va_start (arg, node);
				break;
			case 2:
				if(node->c2 != NULL){trimNodeAST(node->c2);}
				node->c2 = va_start (arg, node);
				break;
			case 3:
				if(node->c3 != NULL){trimNodeAST(node->c3);}
				node->c3 = va_start (arg, node);
				break;
			case 4:
				if(node->next != NULL){trimNodeAST(node->next);}
				node->next = va_start (arg, node);
				break;
			/*case 5:
				node->type = va_start (arg, int);
				break;*/

		}
		
		return;//much done, very ready
    }



