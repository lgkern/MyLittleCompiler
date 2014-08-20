#ifndef _SYMTABLE_
#define _SYMTABLE_

typedef struct{
	void**	data;
}TABLE;

typedef struct {
	int		token;
	char*	description
}TOKEN;


//Hash table API
TABLE*	createHashTable();
int		destroyHashTable(TABLE* table);

int		addHashElement(TABLE* table, TOKEN* token, int line);
int		retrieveHashLine(TABLE* table, TOKEN* token);

int		hash(TOKEN token);

#endif
