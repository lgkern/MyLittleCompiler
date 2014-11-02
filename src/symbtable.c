#include "symbtable.h"
#include "main.h"
#include "comp_dict.h"
#include "iloc.h"
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
		node->defaultRegister = RBSS;
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
	DIC*	lookupDIC(DIC* find)
	{
		return node_lookupDIC(myTree->current, find);
	}
	
	DIC*	recursiveLookup(int type, ...)
	{
		DIC* result = NULL;
		struct NODE* parent = myTree->current;
		char*	strTmp = NULL;
		int 	intTmp = 0;
		char	chrTmp = '0';
		float	fltTmp = 0.0f;
	
		va_list arg;       
		va_start (arg, type);
	
		switch (type) 
	    {
	        case IKS_SIMBOLO_LITERAL_STRING:
	        case IKS_SIMBOLO_IDENTIFICADOR:
				strTmp = va_arg(arg, char*);
	            break;
	        case IKS_SIMBOLO_LITERAL_INT:
	        case IKS_SIMBOLO_LITERAL_BOOL:
				intTmp = va_arg(arg, int);
				break;
	        case IKS_SIMBOLO_LITERAL_FLOAT:
				fltTmp = (float)va_arg(arg, double);
				break;
	        case IKS_SIMBOLO_LITERAL_CHAR:
				chrTmp = (char)va_arg(arg, int);
	            break;
	        default:
	            return NULL;          
	    }
	    

		do{
			switch (type) 
			{
			    case IKS_SIMBOLO_LITERAL_STRING:
			    case IKS_SIMBOLO_IDENTIFICADOR:
			        result = node_lookup(parent, type, strTmp);
			        break;
			    case IKS_SIMBOLO_LITERAL_INT:
			    case IKS_SIMBOLO_LITERAL_BOOL:
					result = node_lookup(parent, type, intTmp);
					break;
			    case IKS_SIMBOLO_LITERAL_FLOAT:
					result = node_lookup(parent, type, fltTmp);
					break;
			    case IKS_SIMBOLO_LITERAL_CHAR:
			        result = node_lookup(parent, type, chrTmp);
			        break;
			    default:
					; 
			}
			parent = parent->father;
		}
		while(parent != NULL && result == NULL);	
		
		return result;
	}
	
	DIC*	recursiveLookupDIC(DIC* find)
	{
		DIC* result = NULL;
		struct NODE* parent = myTree->current;
		
		do{
			result = node_lookupDIC(parent, find);
			parent = parent->father;
		}
		while(parent != NULL && result == NULL);	
		
		return result;
	}

//addScope adds a new level to myTree, while removeScope removes the last added level
	int 	addScope(int returnType)
	{
		//printf("\nAdded Scope\n");
		struct NODE* new = createNode();
		myTree->current->child = new;
		new->father = myTree->current;
		new->returnType = returnType;
		myTree->current = new;
	}

	int 	addScopeNonF()
	{
			addScope(myTree->current->returnType);
	}

	int 	removeScope()
	{
		//printf("\nRemoved Scope\n");
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
		myNode->returnType = INT;
		myNode->defaultRegister = FP;
		myNode->currentDeviation = 0;
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
		
			switch (type)
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
					result = table_lookup(node->data, type, (float)va_arg(arg, double));
					break;
		        case IKS_SIMBOLO_LITERAL_CHAR:
		            result = table_lookup(node->data, type, (char)va_arg(arg, int));
		            break;
		        default:
		            return NULL;          
		    }
		}
		return result;
	}
	
	DIC*	node_lookupDIC(struct NODE* node, DIC* find)
	{
		if (node != NULL)
		{		
			return table_lookupDIC(node->data, find);
		}
		return NULL;
	}

	int		retrieveReturnType()
	{
		return myTree->current->returnType;
	}

	int 	memory(int type)
	{
		switch(type)
		{
			case BOOL:
			case CHAR:
			case STRING:
				return 1;
			//	printf("allocated 1 byte");
			case INT:
			//	printf("allocated 4 bytes");
				return 4;
			case FLOAT:
			//	printf("allocated 8 bytes");
				return 8;
		}
	}

	void		allocateMemory(DIC* variable)
	{
		int oldMemPtr = myTree->current->currentDeviation;
		int mem = memory(variable->idType);
		int multiplier = 1;

		if(variable->idSpec == VECTOR || variable->idSpec == MULTIVECTOR)
			multiplier *= calculateDimensions(variable->vectorSize);		

		myTree->current->currentDeviation += multiplier * mem;
		variable->deviation = oldMemPtr;

		variable->baseRegister = baseRegister();

	}

	int 	baseRegister()
	{
			if(myTree->root != myTree->current)
				return FP;
			return RBSS;
	}

	int 	calculateDimensions(ARG* dimensions)
	{
		ARG* p;
		if(dimensions == NULL)
			return 1;
			
		p = dimensions;
		int ac = 1;
		while(p != NULL)
		{
			ac*=p->type;
			p = p->next;
		}
		return ac;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

//-------------------------------------------------------------------------------------------
