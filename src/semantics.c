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
        if(!variableCheck(dicEntry, 1))
            exit(IKS_ERROR_DECLARED);
    }
