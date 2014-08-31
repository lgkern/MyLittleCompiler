#ifndef _SYMTABLE_
#define _SYMTABLE_

typedef struct {
	int		token;
  char*	description;
}TOKEN;

typedef struct {
	TOKEN*	token;
	int		line;
}DIC;

typedef struct{
	DIC**	data;
}TABLE;



//Hash table API
TABLE*	createHashTable();
int		destroyHashTable(TABLE* table);

int		addHashElement(TABLE* table, TOKEN* token, int line);
int		retrieveHashLine(TABLE* table, TOKEN* token);

int		hash(TOKEN* token);

TOKEN* createToken(int token, char* description);

#endif