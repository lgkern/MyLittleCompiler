#ifndef    _COMP_TREE_H_
#define    _COMP_TREE_H_

#include <stdarg.h>
#include "iks_ast.h"
#include "comp_dict.h"

typedef struct _nodeAST nodeAST;

struct _nodeAST{
    int type;
    nodeAST* next;
    nodeAST* c1;
    nodeAST* c2;
    nodeAST* c3;
    void* symTable;
//new to e4
	int dataType;
};

nodeAST* myAST;

void		createAST(nodeAST* c1);
nodeAST*     createNodeAST(int type, nodeAST* next, DIC* symTable, ...);
void         insertNodeASTChild(nodeAST* parent, nodeAST* child, int index);
void        trimNodeAST(nodeAST* node);
nodeAST*    destroyNodeAST(nodeAST* node);
void        modify(nodeAST* node, int index, ...);


#endif



