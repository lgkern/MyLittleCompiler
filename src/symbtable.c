#include "symbtable.h"
#include "main.h"
#include "comp_dict.h"
#include <string.h>
#include <values.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Symbol Table API -------------------------------------------------------------------------

	int		createTable()
	{
		myTree = calloc(1,sizeof(SYMBTREE));
		struct NODE* node = createNode();
		myTree->root = node;
		myTree->current = node;
	}
	int		destroyTable()
	{
		while(myTree->root != NULL)
		{
			removeScope();
		}
		free(myTree);
	}

	void* 	addSymbol(TOKEN* token, int line)
	{
		return node_addSymbol(myTree->current, token, line);	
	}
	int		retrieveLine(TOKEN* token)
	{
		int found = -1;
		struct NODE* node = myTree->current;

		while(found == -1 && node != myTree->root)
		{
			found = retrieveHashLine(node->data, token);
			node = node->father;
		}
		
		return found;
	}

	DIC*	lookup(int type, ...)
	{
		DIC* result;
		
		va_list arg;       
		va_start (arg, type);
		
		switch (type) 
        {
            case IKS_SIMBOLO_LITERAL_STRING:
            case IKS_SIMBOLO_IDENTIFICADOR:
                result = node_lookup(myTree->current, type, va_arg(arg, char*));
                break;
            case IKS_SIMBOLO_LITERAL_INT:
            case IKS_SIMBOLO_LITERAL_BOOL:
				result = node_lookup(myTree->current, type, va_arg(arg, int));
				break;
            case IKS_SIMBOLO_LITERAL_FLOAT:
				result = node_lookup(myTree->current, type, (float)va_arg(arg, double));
				break;
            case IKS_SIMBOLO_LITERAL_CHAR:
                result = node_lookup(myTree->current, type, (char)va_arg(arg, int));
                break;
            default:
                return NULL;          
        }
        return result;
	}
	
	DIC*	recursiveLookup(int type, ...)
	{
		DIC* result = NULL;
		struct NODE* parent = myTree->current;
		
		va_list arg;       
		va_start (arg, type);
		
		do
		{
			switch (type) 
		    {
		        case IKS_SIMBOLO_LITERAL_STRING:
		        case IKS_SIMBOLO_IDENTIFICADOR:
		            result = node_lookup(parent, type, va_arg(arg, char*));
		            break;
		        case IKS_SIMBOLO_LITERAL_INT:
		        case IKS_SIMBOLO_LITERAL_BOOL:
					result = node_lookup(parent, type, va_arg(arg, int));
					break;
		        case IKS_SIMBOLO_LITERAL_FLOAT:
					result = node_lookup(parent, type, (float)va_arg(arg, double));
					break;
		        case IKS_SIMBOLO_LITERAL_CHAR:
		            result = node_lookup(parent, type, (char)va_arg(arg, int));
		            break;
		        default:
		            return NULL;          
		    }
		    parent = parent->father;		
		}
		while(parent != NULL && result == NULL);	
		
		return result;
	}

//addScope adds a new level to myTree, while removeScope removes the last added level
	int 	addScope()
	{
		struct NODE* new = createNode();
		myTree->current->child = new;
		new->father = myTree->current;
		myTree->current = new;
	}
	int 	removeScope()
	{
		myTree->current = myTree->current->father;
		destroyNode(myTree->current->child);
	}

//Node API ----------------------------------------------------------------------------------
	struct NODE*	createNode()
	{
		struct NODE* myNode = calloc(1, sizeof(struct NODE));
		myNode->data = createHashTable();
		myNode->father = NULL;
		myNode->child = NULL;
		return myNode;
	}
	int		destroyNode(struct NODE* node)
	{
		destroyHashTable(node->data);
		free(node);
	}

	void* 	node_addSymbol(struct NODE* node, TOKEN* token, int line)
	{
		return (void*)addHashElement(node->data, token, line);
	}
	
	int 	node_retrieveLine(struct NODE* node, TOKEN* token)
	{
		return retrieveHashLine(node->data, token);
	}
	
	DIC*	node_lookup(struct NODE* node, int type, ...)
	{
		DIC* result = NULL;
		
		if (node != NULL)
		{		
			va_list arg;       
			va_start (arg, type);
		
			switch (type) //oddly enough, these warnings only occurred on this function and not on the table_lookup one
		    {
		        case IKS_SIMBOLO_LITERAL_STRING:
		        case IKS_SIMBOLO_IDENTIFICADOR:
		            result = table_lookup(node->data, type, va_arg(arg, char*));
		            break;
		        case IKS_SIMBOLO_LITERAL_INT:
		        case IKS_SIMBOLO_LITERAL_BOOL:
					result = table_lookup(node->data, type, va_arg(arg, int));
					break;
		        case IKS_SIMBOLO_LITERAL_FLOAT:
					result = table_lookup(node->data, type, va_arg(arg, double));//va_arg(arg, float)); //make warning, float converted to double when passed through ... by default
					break;
		        case IKS_SIMBOLO_LITERAL_CHAR:
		            result = table_lookup(node->data, type, va_arg(arg, int));//va_arg(arg, char)); //make warning, char converted to int when passed through ... by default
		            break;
		        default:
		            return NULL;          
		    }
		}
		return result;
	}
	
	DIC*	node_recursiveLookup(struct NODE* node, int type, ...)
	{
		return NULL; 
/*I don't understand the meaning of this function, since each node is a separate scope. I can see an use for recursive lookup for the tree as a whole by looking at the node's father whenever the token isn't found, however I can't really see how I could search recursively from a node. Checking the child wouldn't make any sense and checking the parent would be the up to the tree recursive lookup*/
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

//-------------------------------------------------------------------------------------------
