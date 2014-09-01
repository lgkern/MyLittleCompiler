#include "symbtable.h"
#include <stdlib.h>
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

//-------------------------------------------------------------------------------------------
