#ifndef _SEMANTICS_
#define _SEMANTICS_

#include "error_codes.h"
#include "comp_dict.h"
#include "symbtable.h"
#include "comp_tree.h"


//A variable is valid for usage when it has a type and spec set
int variableCheck(DIC* dicEntry, int fatal);
void variableExists(DIC* dicEntry);

//Check if op1 and op2 are compatible, including coersion
void typeCompatibility(nodeAST* op1, nodeAST* op2);

//Check if the given arguments are compatible with the function
void functionCompatibility(nodeAST* functionName, nodeAST* parameterList);
ARG* 	generateParameters(nodeAST* parameterList);

//Command validators
void inputValidation(nodeAST* argument);
void outputValidation(nodeAST* argument);
void returnValidation(nodeAST* argument, int expectedReturn);

//H messing around
void specCheck(DIC* entry, int spec);


#endif
