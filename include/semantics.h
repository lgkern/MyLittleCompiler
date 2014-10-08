#include "error_codes.h"
#include "comp_dict.h"
#include "symbtable.h"


//A variable is valid to usage when it has a type and spec set
void variableCheck(DIC* dicEntry);

//Check if op1 and op2 are compatible, including coersion
void typeCompatibility(nodeAST* op1, nodeAST* op2);

//Check if the given arguments are compatible with the function
void functionCompatibility(nodeAST* parameterList, nodeAST* functionPrototype);

//Command validators
void inputValidation(nodeAST* argument);
void outputValidation(nodeAST* argument);
void returnValidation(nodeAST* argument, int expectedReturn);
