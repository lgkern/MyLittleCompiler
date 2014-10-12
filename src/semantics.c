#include "semantics.h"
#include "error_codes.h"
#include <stdlib.h>

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
