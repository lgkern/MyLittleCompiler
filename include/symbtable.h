#ifndef _SYMB_TABLE_
#define _SYMB_TABLE_

#include "symt.h"

//Data definitions -------------------------------------------------------------------------

struct NODE{
	TABLE*	data;
	struct NODE*	child;
	struct NODE*	father;
};

typedef struct {
	struct NODE*	root;
	struct NODE*	current;
}SYMBTREE;
//-----------------------------------------------------------------------------------------

	SYMBTREE*	myTree;

//Symbol Table API -------------------------------------------------------------------------

	int		createTable();
	int		destroyTable();

	void* 	addSymbol(TOKEN* token, int line);
	int		retrieveLine(TOKEN* token);


//addScope adds a new level to myTree, while removeScope removes the last added level
	int 	addScope();
	int 	removeScope();

//Node API ----------------------------------------------------------------------------------
	struct NODE*	createNode();
	int		destroyNode(struct NODE* node); 

	void* 	node_addSymbol(struct NODE* node, TOKEN* token, int line);
	int 	node_retrieveLine(struct NODE* node, TOKEN* token);

//-------------------------------------------------------------------------------------------

#endif
