#include "semantics.h"
#include "error_codes.h"
#include <stdlib.h>
#include <stdio.h>

    int variableCheck(DIC* dicEntry, int fatal)
    {
        if(dicEntry == NULL || dicEntry->idSpec == 0)
        {
        	if(fatal)
            {
                exit(IKS_ERROR_UNDECLARED);
            }
            return 1;
        }
        //printf("\tNot NULL:\n\t\tspec=%d\n\t\ttype=%d\n\t\tothertype=%d\n\t\tdescription=%s\n", dicEntry->idSpec, dicEntry->idType, dicEntry->token->token, dicEntry->token->description.string);         
        return 0;
    }

	void variableExists(DIC* dicEntry)
    {
        if(variableCheck(dicEntry, 0) == 0)
            exit(IKS_ERROR_DECLARED);
    }
    
  	void specCheck(DIC* entry, int spec)
  	{
  		variableCheck(entry, 1);
  		
  		if(entry->idSpec != spec)
  		{
  			switch(entry->idSpec)
  			{
  				case VARIABLE:
  					exit(IKS_ERROR_VARIABLE);
  					break;
  				case VECTOR:
  				  	exit(IKS_ERROR_VECTOR);
  					break;
  				case FUNCTION:
  					exit(IKS_ERROR_FUNCTION);
  					break;
  				case MULTIVECTOR:
  					exit(IKS_ERROR_VECTOR);//for now, since we don't have multi-vector just yet
  					break;
  				default:
  					exit(IKS_ERROR_UNDECLARED);//that's an error, what do I set this as? undeclared?
  					//half a mind to create an error code IKS_ERROR_MAGIA_NEGRA, just saying
  			}
  		}
  	}

	void 	functionCompatibility(nodeAST* functionName, nodeAST* parameterList)
	{
		//printf("\nLooking for the function:%s\n",((DIC*)functionName->symTable)->token->description.string);
		DIC* functionEntry = recursiveLookupDIC((DIC*)functionName->symTable);
		if(functionEntry == NULL)
		{
			printf("This shouldn't ever EVER happen");
			exit(IKS_ERROR_UNDECLARED);
		}

		ARG* arguments = functionEntry->argList;
		ARG* parameters = generateParameters(parameterList);

		ARG* currParameter = parameters;

		//printf("\nChecking parameters!\n");

		while(arguments != NULL && currParameter != NULL)
		{
			if(arguments->type != currParameter->type)
			{
				//printf("\nFunction Expects: %d\n",arguments->type);
			//	printf("\nFunction Received: %d\n",parameters->type);
				//printf("\nWrong type args!!\n");
				exit(IKS_ERROR_WRONG_TYPE_ARGS);
			}
			
			arguments = arguments->next;
			currParameter = currParameter->next;
		}
		if(arguments != NULL)
		{
			//printf("\nMissing Args!!\n");
			exit(IKS_ERROR_MISSING_ARGS);
			
		}
		if(parameters != NULL)
		{
			//printf("\nExcess args!!\n");
			exit(IKS_ERROR_EXCESS_ARGS);		
		}
	}

	ARG* 	generateParameters(nodeAST* parameterList)
	{
		if(parameterList == NULL)
			return NULL;

		ARG* newArg = createArg(parameterList->dataType);
		newArg->next = generateParameters(parameterList->next);

		return newArg;
	}

	void outputValidation(nodeAST* arguments)
	{
		nodeAST* current = arguments;
		while(current != NULL)
		{
			if(current->dataType != STRING && current->dataType != FLOAT && current->dataType != INT && current->dataType != BOOL)
			{
				exit(IKS_ERROR_WRONG_PAR_OUTPUT);
			}
			current = current->next;
		}
	}

	void returnValidation(nodeAST* argument)
	{
		if(argument->dataType != retrieveReturnType())
		{
			if(argument->dataType > 3) //No Coersion available
				exit(IKS_ERROR_WRONG_PAR_RETURN);
			if(argument->dataType > 0) //Coersion possible!
				if(!(retrieveReturnType() < 4 && retrieveReturnType() > 0)) //Return type isn't coersible 
					exit(IKS_ERROR_WRONG_PAR_RETURN);
		}
	}
  	
  	int typeCompatibility(nodeAST* op1, nodeAST* op2)
  	{
  		printf("\ttypecomp: %d vs %d\n", op1->dataType, op2->dataType);
  		if (op1->dataType != op2->dataType)
  		{
  			return coersion(op1->dataType, op2->dataType);
  		}
  		return op1->dataType;  	
  	}
  	
  	int coersion(int type1, int type2)
  	{
  		if(type2 == STRING)
  			exit(IKS_ERROR_STRING_TO_X);
  			
  		if(type2 == CHAR)
  			exit(IKS_ERROR_CHAR_TO_X);
  			
  		switch(type1)
  		{
  			case BOOL:
  				if(type2 == INT || type2 == FLOAT)
  					return type2;
  				break;
  			case INT:
  				if(type2 == BOOL || type2 == FLOAT)
  					return max(type1, type2);
  				break;
  			case FLOAT:
  				if(type2 == BOOL || type2 == INT)
  					return FLOAT;
  				break;
  			default:
  				;
  		}
  			
  		exit(IKS_ERROR_WRONG_TYPE);
  	}
  	
  	int max(int v1, int v2)
  	{
  		if (v1 > v2)
  			return v1;
  		return v2;
  	}


	void checkIndexer(nodeAST* indexer)
	{
			if(indexer->dataType == CHAR)
				exit(IKS_ERROR_CHAR_TO_X);
			if(indexer->dataType == STRING)
				exit(IKS_ERROR_STRING_TO_X);

	
	}
