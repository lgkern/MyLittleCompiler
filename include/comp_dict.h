#ifndef _COMP_DICT_
#define _COMP_DICT_


#define		VARIABLE	0
#define 	VECTOR		1
#define		FUNCTION	2

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
	int 	idSpec;
	int 	idType;
    DIC*	next;
};

typedef struct{
    DIC**	data;
}TABLE;



//Hash table API
TABLE*	createHashTable();
int		destroyHashTable(TABLE* table);
DIC*	destroyHashElement(DIC* tDic);
void	destroyToken(TOKEN* token);

DIC*	addHashElement(TABLE* table, TOKEN* token, int line);
void    modifyIdSpec(DIC* dic, int newSpec);
void    modifyIdType(DIC* dic, int newType);
DIC*	addElementToBucket(DIC* first, DIC* dic);
int	    compareDICS(DIC* dic1, DIC* dic2);
int		compareTokens(TOKEN* token1, TOKEN* token2);
int		retrieveHashLine(TABLE* table, TOKEN* token);

int		hash(TOKEN* token);

TOKEN*	createToken(int token, char* description);
TOKEN*	createIntToken(int token, int description);
TOKEN*	createFltToken(int token, float description);
TOKEN*	createChrToken(int token, char description);
TOKEN*	createStrToken(int token, char* description);

DIC*	table_lookup(TABLE* table, int type, ...);

#endif



