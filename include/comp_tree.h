#ifndef    _COMP_TREE_H_
#define    _COMP_TREE_H_

#include <stdarg.h>
typedef struct _nodeAST nodeAST;

struct _nodeAST{
    int type;
    nodeAST* next;
    nodeAST* c1;
    nodeAST* c2;
    nodeAST* c3;
    void* symTable;
};

nodeAST*     createNodeAST(int type, nodeAST* next, void* symTable, ...);
void         insertNodeASTChild(nodeAST* parent, nodeAST* child, int index);
void        trimNodeAST(nodeAST* node);
nodeAST*    destroyNodeAST(nodeAST* node);
void        modify(nodeAST* node, int index, ...);


#endif



