#ifndef _ILOC_H_
#define _ILOC_H_

#include "ilocInstructions.h"

#define IREGISTER 	1
#define ICONSTANT 	2
#define ILABEL		3

typedef struct 
{
	int instruction;
	int argType[3];
	int regs[3];
	int consts[3];
	char* labels[3];
}INST;

typedef struct _ILIST ILIST;

struct _ILIST{
	INST*	instruction;
    ILIST*	next;	
};

void 	printInstruction(INST* inst);

/*
 * The first 3 arguments define what type of arguments the instruction will have
 * tArg1 being 1, means that the first left-oriented argument from the TAC will be a register
 * tArg2 being 3, means that the second left-oriented argument from the TAC will be a label and so on...
 */

INST*	createInstruction(int tArg1, int tArg2, int tArg3, ...);
void	destroyInstruction(INST* inst);

void	mergeInstructionLists(ILIST* l1, ILIST* l2);
void 	destroyInstructionList(ILIST* l);

#endif
