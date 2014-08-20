#include "symt.h"
#include "crc16.h"
#include <string.h>
#include <values.h>
#include <stdlib.h>

//Hash table API
	TABLE*	createHashTable()
	{
		TABLE* myTable = calloc(1,sizeof(TABLE));
		myTable->data = calloc(2*MAXSHORT,sizeof(DIC*));
	}
	int	destroyHashTable(TABLE* table)
	{
		int i;
		for(i = 0; i < 2*MAXSHORT; i++)
		{
			if(&table[i] != NULL)
			{
				free(table->data[i]->token->description);
				free(table->data[i]->token);
				free(table->data[i]);
			}
			free(table);
		}
	}

	int	addHashElement(TABLE* table, TOKEN* token, int line)
	{
		//TODO testar se não teve conflito
		int position = 0;
		DIC* tDic = calloc(1,sizeof(DIC));
		tDic->token = token;
		tDic->line = line;

		position = hash(token);

		table->data[position] = tDic;
		
	}
	int	retrieveHashLine(TABLE* table, TOKEN* token)
	{
		int position = 0;

		position = hash(token);

		if(table->data[position] != NULL)
		{
			//TODO testar se não teve conflito
			return table->data[position]->line;
		}
		return -1;
	}

	int	hash(TOKEN* token)
	{
		int length = strlen(token->description);
		length += 4;

		return crc16_ccitt((const void*)token,length);
	}

