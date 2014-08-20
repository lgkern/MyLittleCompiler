#include "symt.h"
#include "crc16.h"
#include <string.h>
#include <values.h>
#include <stdlib.h>

//Hash table API
	TABLE*	createHashTable()
	{
		TABLE* myTable = calloc(1,sizeof(TABLE));
		myTable->data = calloc(2*MAXSHORT,sizeof(void*));
	}
	int	destroyHashTable(TABLE* table)
	{
	
	}

	int	addHashElement(TABLE* table, TOKEN* token, int line)
	{
		
	}
	int	retrieveHashLine(TABLE* table, TOKEN* token)
	{
	
	}

	int	hash(TOKEN token)
	{
		int length = strlen(token.description);
		length += 4;

		return crc16_ccitt((const void*)&token,length);
	}

