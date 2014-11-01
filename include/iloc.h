#ifndef _ILOC_H_
#define _ILOC_H_

#include "ilocInstructions.h"

#define IREGISTER 	1
#define ICONSTANT 	2
#define ILABEL		3

//Special Registers
#define		FP		-1		//Frame pointer
#define		RBSS	-2		//Base Register for Global Variables
#define		RARP	-3		//Current Activation Register

typedef struct 
{
	int 	instLabel;
	int 	instruction;
	int 	argType[3];
	int 	args[3];
	int		specialReg[3];
}INST;

typedef struct _ILIST ILIST;

struct _ILIST{
	INST*	instruction;
    ILIST*	next;	
};

void 	printInstruction(INST* inst);
void 	printArg(INST* inst, int index);

INST*	createInstruction(int instruction, ...);
void	destroyInstruction(INST* inst);
void 	addInstructionLabel(INST* inst, int label);
void	addInstructionSpecialRegister(INST* inst, int index, int reg);

ILIST*	createInstructionList(INST* inst);
void	addInstruction(ILIST* l, INST* instruction);
ILIST*	mergeInstructionLists(ILIST* l1, ILIST* l2);
void 	destroyInstructionList(ILIST* l);

#endif
