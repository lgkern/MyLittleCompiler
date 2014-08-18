#ifndef _SYMB_TABLE_
#define _SYMB_TABLE_

#include "symt.h"

//Data definitions -------------------------------------------------------------------------
typedef struct TOKEN{
	int		token;
	char*	description
}TOKEN;

typedef struct NODE{
	TABLE*	data;
	NODE*	child;
	NODE*	father;
}NODE

typedef struct SYMBTREE{
	NODE*	root;
	NODE*	current;
}SYMBTREE;
//-----------------------------------------------------------------------------------------

	SYMBTREE	myTree;

//Symbol Table API -------------------------------------------------------------------------

	int		createTable();
	int		destroyTable();

	int 	addSymbol(TOKEN* token, int line);
	int		retrieveLine(TOKEN* token);


//addScope adds a new level to myTree, while removeScope removes the last added level
	int 	addScope();
	int 	removeScope();

//Node API ----------------------------------------------------------------------------------
	NODE*	createNode();
	int		destroyNode(NODE* node); 

	int 	addSymbol(NODE* node, TOKEN* token);
	int 	retrieveLine(NODE* node, TOKEN* token);

//-------------------------------------------------------------------------------------------

#endif
