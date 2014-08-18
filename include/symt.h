#ifndef _SYMTABLE_
#define _SYMTABLE_

typedef struct TABLE{
//TODO: Hash table structure
}TABLE


//Hash table API
TABLE*	createTable();
int		destroyTable(TABLE* table);

int		addElement(int token, char* description, int line);
int		retrieveLine(int token, char* descripton);

#endif
