#include "comp_dict.h"
#include "crc16.h"
#include "main.h"
#include <string.h>
#include <values.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Hash table API
    TABLE*    createHashTable()
    {
        TABLE* myTable = calloc(1,sizeof(TABLE));
        myTable->data = calloc(2*32769,sizeof(DIC*));
        //printf("\nAlocado %lu memoria\n",2*32769*sizeof(DIC*));
    }
    int    destroyHashTable(TABLE* table)
    {
        int i;
        for(i = 0; i < 2*MAXSHORT; i++)
        {
            if(&table->data[i] != NULL)
            {
                DIC* next = table->data[i];
                do 
                {
                    next = destroyHashElement(next);
                }
                while(next != NULL);
                /*if(table->data[i]->token->token == IKS_SIMBOLO_LITERAL_STRING 
                 ||table->data[i]->token->token == IKS_SIMBOLO_IDENTIFICADOR)
                    free(table->data[i]->token->description.string);
                free(table->data[i]->token);
                free(table->data[i]);*/
            }
            
        }
        free(table);
    }

    DIC*    destroyHashElement(DIC* tDic)
    {
        DIC* next = NULL;
        if(tDic != NULL)
        {
            next = tDic->next;
            if(tDic->token->token == IKS_SIMBOLO_LITERAL_STRING 
             ||tDic->token->token == IKS_SIMBOLO_IDENTIFICADOR)
                free(tDic->token->description.string);
            free(tDic->token);
            free(tDic);
        }
        return next;
    }

    DIC*    addHashElement(TABLE* table, TOKEN* token, int line)
    {
        int position = 0;
        DIC* tDic = calloc(1,sizeof(DIC));
        tDic->token = token;
        tDic->line = line;
        tDic->next = NULL;

        position = hash(token);
		printf("DIC position: %d\n", position);
        if(table->data[position]!= NULL)
        {                
            tDic = addElementToBucket(table->data[position], tDic);
        }
		else
		{
        	table->data[position] = tDic;
		}
		//printf("\n\nPointer : %p\n\n", tDic);
       
        return tDic;
    }

    DIC*    addElementToBucket(DIC* first, DIC* newDic)
    {
        DIC* current = first;
        while(current != NULL)
        {
            if (compareDICS(current, newDic))
            {
				printf("same dics \n");
                current->line = newDic->line;
				//destroyHashElement(newDic);
                return newDic;
            }
            if (current->next == NULL)
            {
                current->next = newDic;
                return newDic;
            }

            current = current->next;
        }
        return newDic;
    }

    int    compareDICS(DIC* dic1, DIC* dic2)
    {
        if(dic1->token->token == dic2->token->token)
        {
            int compare = 1;
            switch (dic1->token->token)
            {
                case IKS_SIMBOLO_LITERAL_STRING:
                case IKS_SIMBOLO_IDENTIFICADOR:
                    compare = strcmp(dic1->token->description.string, dic2->token->description.string);
                    break;
                case IKS_SIMBOLO_LITERAL_INT:
                case IKS_SIMBOLO_LITERAL_BOOL:
					compare = (dic1->token->description.integer == dic2->token->description.integer);
					break;
                case IKS_SIMBOLO_LITERAL_FLOAT:
					compare = (dic1->token->description.floating == dic2->token->description.floating);
					break;
                case IKS_SIMBOLO_LITERAL_CHAR:
                    compare = (dic1->token->description.character == dic2->token->description.character);
                    break;
                default:
                    ;            
            }
            return compare;
        }
        return 1;
    }

    int    retrieveHashLine(TABLE* table, TOKEN* token)
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

    int    hash(TOKEN* token)
    {
        int length = 0;
        switch(token->token)        
        {
        case IKS_SIMBOLO_LITERAL_STRING:
        case IKS_SIMBOLO_IDENTIFICADOR:
            length = strlen(token->description.string);
			return crc16_ccitt((const void*)token->description.string,length);
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
	description++;
        description[strsize-2] = '\0'; //remove the last quotation
        myToken->description.string = strdup(description);
        description[strsize-2] = 'a'; //put some trash back in so it doesn't lose the pointer
	description--;
//	printf("%s\n",myToken->description.string);
        return myToken;
    }



