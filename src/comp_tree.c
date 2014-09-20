#include "comp_tree.h"
#include <stdlib.h>
#include <stdio.h>

    nodeAST* createNodeAST(int type, nodeAST* next, void* symTable, ...)
    {
        nodeAST* node = calloc(1, sizeof(nodeAST));
        node->type = type;
        node->next = next;
        node->symTable = symTable;
        node->c1 = NULL;
        node->c2 = NULL;
        node->c3 = NULL;
        // va_list arg;
        // va_start (arg, next);//NodeAST type
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



