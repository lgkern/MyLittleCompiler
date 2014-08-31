#include "symt.h"
#include "crc16.h"
#include <string.h>
#include <values.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Hash table API
	TABLE*	createHashTable()
	{
		TABLE* myTable = calloc(1,sizeof(TABLE));
		myTable->data = calloc(2*32769,sizeof(DIC*));
		//printf("\nAlocado %lu memoria\n",2*32769*sizeof(DIC*));
	}
	int	destroyHashTable(TABLE* table)
	{
		int i;
		for(i = 0; i < 2*MAXSHORT; i++)
		{
			if(&table->data[i] != NULL)
			{
				free(table->data[i]->token->description);
				free(table->data[i]->token);
				free(table->data[i]);
			}
			
		}
		free(table);
	}

	DIC*	addHashElement(TABLE* table, TOKEN* token, int line)
	{
		//TODO testar se não teve conflito
		int position = 0;
		DIC* tDic = calloc(1,sizeof(DIC));
		tDic->token = token;
		tDic->line = line;

		position = hash(token);
		if(table->data[position]!= NULL)
		{
			free(table->data[position]->token->description);
			free(table->data[position]->token);
			free(table->data[position]);
		}
		//printf("\n\nPointer : %p\n\n", tDic);
		table->data[position] = tDic;		
		return tDic;
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

	TOKEN* createToken(int token, char* description)
	{
		TOKEN* myToken;
		myToken = calloc(1,sizeof(TOKEN));
		myToken->token = token;
		myToken->description = strdup(description);
	}

