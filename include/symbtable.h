#ifndef _SYMB_TABLE_
#define _SYMB_TABLE_

#include "comp_dict.h"

//Data definitions -------------------------------------------------------------------------

struct NODE{
	TABLE*	data;
	struct NODE*	child;
	struct NODE*	father;
	int		returnType;
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

	//Lookup as (int type, <entry data type> description)
	// e.g.:    (int type, string description)
	//          (int type, char description)
	DIC*	lookup(int type, ...);
	DIC*	lookupDIC(DIC* find);
	DIC*	recursiveLookup(int type, ...);
	DIC*	recursiveLookupDIC(DIC* find);


//addScope adds a new level to myTree, while removeScope removes the last added level
	int 	addScope(int returnType);
	int 	removeScope();
	int		retrieveReturnType();

//Node API ----------------------------------------------------------------------------------
	struct NODE*	createNode();
	int		destroyNode(struct NODE* node); 

	void* 	node_addSymbol(struct NODE* node, TOKEN* token, int line);
	int 	node_retrieveLine(struct NODE* node, TOKEN* token);

	DIC*	node_lookup(struct NODE* node, int type, ...);
	DIC*	node_lookupDIC(struct NODE* node, DIC* find);

//-------------------------------------------------------------------------------------------

#endif
