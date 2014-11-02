#ifndef    _COMP_TREE_H_
#define    _COMP_TREE_H_

#define TYPE	0
#define C1		1
#define C2		2
#define C3		3
#define NEXT	4
#define DATA	5
#define STABLE	7

#include <stdarg.h>
#include "iks_ast.h"
#include "comp_dict.h"
#include "iloc.h"

typedef struct _nodeAST nodeAST;

struct _nodeAST{
    int 		type;
    nodeAST* 	next;
    nodeAST* 	c1;
    nodeAST* 	c2;
    nodeAST* 	c3;
    void* 		symTable;
//new to e4
	int 		dataType;
	int 		coersion;
//new to e5
	ILIST* 		code;
	int 		local;
	int			t;
	int			f;
};

nodeAST* myAST;

void		createAST(nodeAST* c1);
nodeAST*    createNodeAST(int type, nodeAST* next, DIC* symTable, int dataType, int coersion, ...);
void        insertNodeASTChild(nodeAST* parent, nodeAST* child, int index);
void        trimNodeAST(nodeAST* node);
nodeAST*    destroyNodeAST(nodeAST* node);
void        modify(nodeAST* node, int index, ...);
ILIST*  	vectorDeviation(nodeAST* n, int reg);

#endif



