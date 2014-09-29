#ifndef _COMP_DICT_
#define _COMP_DICT_

typedef union{
    int		integer;
    float	floating;
    char	character;
    char*	string;
}VALUE;

typedef struct {
    int		token;
    VALUE	description;
}TOKEN;

typedef struct _DIC DIC;

struct _DIC{
    TOKEN*	token;
    int		line;
    DIC*	next;
};

typedef struct{
    DIC**	data;
}TABLE;



//Hash table API
TABLE*	createHashTable();
int		destroyHashTable(TABLE* table);
DIC*	destroyHashElement(DIC* tDic);

DIC*	addHashElement(TABLE* table, TOKEN* token, int line);
DIC*	addElementToBucket(DIC* first, DIC* dic);
int	    compareDICS(DIC* dic1, DIC* dic2);
int		retrieveHashLine(TABLE* table, TOKEN* token);

int		hash(TOKEN* token);

TOKEN*	createToken(int token, char* description);

TOKEN*	createIntToken(int token, int description);

TOKEN*	createFltToken(int token, float description);

TOKEN*	createChrToken(int token, char description);

TOKEN*	createStrToken(int token, char* description);

#endif



