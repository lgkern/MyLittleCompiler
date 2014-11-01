#ifndef _COMP_DICT_
#define _COMP_DICT_


#define		VARIABLE	1
#define 	VECTOR		2
#define		FUNCTION	3
#define     MULTIVECTOR 4

#define 	NONE		0
#define 	BOOL		1
#define 	INT			2		
#define		FLOAT		3
#define		CHAR		4
#define		STRING		5

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


typedef struct _ARG ARG;

struct _ARG{
	int type;
	ARG* next;
};

typedef struct _DIC DIC;

struct _DIC{
    TOKEN*	token;
    int		line;
	int 	idSpec;
	int 	idType;
	ARG*	argList;
    DIC*	next;	
//new to e5
	int		baseRegister;
	int 	deviation;
	int		strSize;
	int		vectorSize; //Need to be changed to support multivectors
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
DIC*	table_lookupDIC(TABLE* table, DIC* find);

ARG*	createArg(int type);
void	addFunctionArg(DIC* fooEntry, ARG* argList);
//void 	checkFunctionArg(DIC* fooEntry, int type, int reset, int isFinal);

ARG*	createMultiVector(DIC* type);

#endif



