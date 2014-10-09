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
    
    void destroyToken(TOKEN* token)
    {
    	if(token != NULL)
    	{
    		if(token->token == IKS_SIMBOLO_LITERAL_STRING 
             ||token->token == IKS_SIMBOLO_IDENTIFICADOR)
                free(token->description.string);
            free(token);
    	}
    	return;    
    }

    DIC*    addHashElement(TABLE* table, TOKEN* token, int line)
    {
        int position = 0;
        DIC* tDic = calloc(1,sizeof(DIC));
        tDic->token = token;
        tDic->line = line;
        tDic->next = NULL;

        position = hash(token);
		//printf("DIC position: %d\n", position);
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

    //TODO Check declaration clashes (int foo()  x  int foo)
    void    modifyIdSpec(DIC* dic, int newSpec)
    {
        dic->idSpec = newSpec;
        
    }

    void    modifyIdType(DIC* dic, int newType)
    {
        dic->idType = newType;
    }

    DIC*    addElementToBucket(DIC* first, DIC* newDic)
    {
        DIC* current = first;
        while(current != NULL)
        {
            if (compareDICS(current, newDic))
            {
				//printf("same dics \n");
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
        return compareTokens(dic1->token, dic2->token);
        /*if(dic1->token->token == dic2->token->token)
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
        return 1;*/
    }
    
    int    compareTokens(TOKEN* token1, TOKEN* token2)
    {
        if(token1->token == token2->token)
        {
            int compare = 1;
            switch (token1->token)
            {
                case IKS_SIMBOLO_LITERAL_STRING:
                case IKS_SIMBOLO_IDENTIFICADOR:
                    compare = strcmp(token1->description.string, token2->description.string);
                    break;
                case IKS_SIMBOLO_LITERAL_INT:
                case IKS_SIMBOLO_LITERAL_BOOL:
					compare = (token1->description.integer == token2->description.integer);
					break;
                case IKS_SIMBOLO_LITERAL_FLOAT:
					compare = (token1->description.floating == token2->description.floating);
					break;
                case IKS_SIMBOLO_LITERAL_CHAR:
                    compare = (token1->description.character == token2->description.character);
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
		//printf("%s\n",myToken->description.string);
        return myToken;
    }

	DIC*	table_lookup(TABLE* table, int type, ...)
	{
		TOKEN* myToken;
		
		va_list arg;       
		va_start (arg, type);
		
		switch (type)
        {
            case IKS_SIMBOLO_LITERAL_STRING:
            case IKS_SIMBOLO_IDENTIFICADOR:
                myToken = createStrToken(type, va_arg(arg, char*));
                break;
            case IKS_SIMBOLO_LITERAL_INT:
            case IKS_SIMBOLO_LITERAL_BOOL:
				myToken = createIntToken(type, va_arg(arg, int));
				break;
            case IKS_SIMBOLO_LITERAL_FLOAT:
				myToken = createFltToken(type, va_arg(arg, float));
				break;
            case IKS_SIMBOLO_LITERAL_CHAR:
                myToken = createChrToken(type, va_arg(arg, char));
                break;
            default:
                return NULL;          
        }        
        
        int position = 0;
        position = hash(myToken);
        
        DIC* current = table->data[position];
        while(current != NULL)
	    {
	        if (compareTokens(current->token, myToken))
	        {
				destroyToken(myToken);
				return current;
	        }
	        
	        current = current->next;
	    }
       	
       	destroyToken(myToken);
        return NULL;	
	}


