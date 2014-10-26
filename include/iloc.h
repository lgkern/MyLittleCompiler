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
	char* 	instLabel;
	int 	instruction;
	int 	argType[3];
	int 	regs[3];
	int 	consts[3];
	char* 	labels[3];

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
//Do not free label after calling addInstructionLabel
void 	addInstructionLabel(INST* inst, char* label);

ILIST*	createInstructionList(INST* inst);
void	addInstruction(ILIST* l, INST* instruction);
ILIST*	mergeInstructionLists(ILIST* l1, ILIST* l2);
void 	destroyInstructionList(ILIST* l);

#endif
