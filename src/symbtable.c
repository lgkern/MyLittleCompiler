#include "symbtable.h"
#include <stdlib.h>

//Symbol Table API -------------------------------------------------------------------------

	int		createTable()
	{
		myTree = calloc(1,sizeof(SYMBTREE));
	}
	int		destroyTable()
	{
	
	}

	int 	addSymbol(TOKEN* token, int line)
	{
	
	}
	int		retrieveLine(TOKEN* token)
	{
	
	}


//addScope adds a new level to myTree, while removeScope removes the last added level
	int 	addScope()
	{
	
	}
	int 	removeScope()
	{
	
	}

//Node API ----------------------------------------------------------------------------------
	struct NODE*	createNode()
	{
	
	}
	int		destroyNode(struct NODE* node)
	{
	
	}

	int 	node_addSymbol(struct NODE* node, TOKEN* token, int line)
	{
	
	}
	int 	node_retrieveLine(struct NODE* node, TOKEN* token)
	{
	
	}

//-------------------------------------------------------------------------------------------
