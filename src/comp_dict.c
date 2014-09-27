#include "comp_dict.h"
#include "crc16.h"
#include "main.h"
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
				if(table->data[i]->token->token == IKS_SIMBOLO_LITERAL_STRING 
				 ||table->data[i]->token->token == IKS_SIMBOLO_IDENTIFICADOR)
					free(table->data[i]->token->description.string);
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
			if(table->data[position]->token->token == IKS_SIMBOLO_LITERAL_STRING 
			 ||table->data[position]->token->token == IKS_SIMBOLO_IDENTIFICADOR)
				free(table->data[position]->token->description.string);
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
		int length = 0;
		switch(token->token)		
		{
		case IKS_SIMBOLO_LITERAL_STRING:
			length = strlen(token->description.string);
			break;
		case IKS_SIMBOLO_IDENTIFICADOR:
			length = strlen(token->description.string);
			break;
		case IKS_SIMBOLO_LITERAL_BOOL:
			length = sizeof(int);
			break;
		case IKS_SIMBOLO_LITERAL_FLOAT:
			length = sizeof(float);
			break;
		case IKS_SIMBOLO_LITERAL_INT:
			length = sizeof(int);
			break;
		case IKS_SIMBOLO_LITERAL_CHAR:
			length = sizeof(char);
			break;
		default:
			length = 0;			
		}
		length += 4;

		return crc16_ccitt((const void*)token,length);
	}

	TOKEN* createToken(int token, char* description)
	{
		TOKEN* myToken;
		myToken = calloc(1,sizeof(TOKEN));
		myToken->token = token;
		myToken->description.string = strdup(description);
		return myToken;
	}

	TOKEN* createIntToken(int token, int description)
	{
		TOKEN* myToken;
		myToken = calloc(1,sizeof(TOKEN));
		myToken->token = token;
		myToken->description.integer = description;
		return myToken;
	}

	TOKEN* createFltToken(int token, float description)
	{		
		TOKEN* myToken;
		myToken = calloc(1,sizeof(TOKEN));
		myToken->token = token;
		myToken->description.floating = description;
		return myToken;
	}

	TOKEN* createChrToken(int token, char description)
	{
		TOKEN* myToken;
		myToken = calloc(1,sizeof(TOKEN));
		myToken->token = token;
		myToken->description.character = description;
		return myToken;
	}

	TOKEN* createStrToken(int token, char* description)
	{
		TOKEN* myToken;
		int strsize = 0;
		myToken = calloc(1,sizeof(TOKEN));
		myToken->token = token;
		strsize = strlen(description);
		description[strsize-3] = '\0'; //remove the last quotation
		myToken->description.string = strdup(description);
		description[strsize-3] = 'a'; //put some trash back in so it doesn't lose the pointer
		return myToken;
	}

