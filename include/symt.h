#ifndef _SYMTABLE_
#define _SYMTABLE_

typedef struct{
//TODO: Hash table structure
}TABLE;


//Hash table API
TABLE*	createHashTable();
int		destroyHashTable(TABLE* table);

int		addHashElement(int token, char* description, int line);
int		retrieveHashLine(int token, char* descripton);

#endif
