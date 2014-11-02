#include "iloc.h"
#include "generators.h"
#include "comp_dict.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

void 	defaultPrintArgs(INST* inst)
{
	printArg(inst, 0);
	printf(", ");
	printArg(inst, 1);
	printf(" => ");
	printArg(inst, 2);
	printf("\n");
}

void 	printInstruction(INST* inst)
{
	if(inst->instLabel != -1)
		printf("L%d:",inst->instLabel);

	switch(inst->instruction)
	{
		case NOP:
			printf("nop\n");
			break;
//Arithmetics 1
		case ADD:
			printf("add ");
			defaultPrintArgs(inst);
			break;
		case SUB:
			printf("sub ");
			defaultPrintArgs(inst);
			break;
		case MULT:
			printf("mult ");
			defaultPrintArgs(inst);
			break;
		case DIV:
			printf("div ");
			defaultPrintArgs(inst);
			break;
//Arithmetics 2
		case ADDI:
			printf("addI ");
			defaultPrintArgs(inst);
			break;
		case SUBI:
			printf("subI ");
			defaultPrintArgs(inst);
			break;
		case RSUBI:
			printf("rsubI ");
			defaultPrintArgs(inst);
			break;
		case MULTI:
			printf("multI ");
			defaultPrintArgs(inst);
			break;
		case DIVI:
			printf("divI ");
			defaultPrintArgs(inst);
			break;
		case RDIVI:
			printf("rdivI ");
			defaultPrintArgs(inst);
			break;
//Shifts 3
		case LSHIFT:
			printf("lshift ");
			defaultPrintArgs(inst);
			break;
		case LSHIFTI:
			printf("lshiftI ");
			defaultPrintArgs(inst);
			break;
		case RSHIFT:
			printf("rshift ");
			defaultPrintArgs(inst);
			break;
		case RSHIFTI:
			printf("rshiftI ");
			defaultPrintArgs(inst);
			break;
//Boolean Expressions
		case AND:
			printf("and ");
			defaultPrintArgs(inst);
			break;
		case ANDI:
			printf("andI ");
			defaultPrintArgs(inst);
			break;
		case OR:
			printf("or ");
			defaultPrintArgs(inst);
			break;
		case ORI:
			printf("orI ");
			defaultPrintArgs(inst);
			break;
		case XOR:
			printf("xor ");
			defaultPrintArgs(inst);
			break;
		case XORI:
			printf("xorI ");
			defaultPrintArgs(inst);
			break;
//Load Instructions
		case LOADI:
			printf("loadI ");
			printArg(inst, 0);
			printf(" => ");
			printArg(inst, 1);
			printf("\n");
			break;
		case LOAD:
			printf("load ");
			printArg(inst, 0);
			printf(" => ");
			printArg(inst, 1);
			printf("\n");
			break;
		case LOADAI:
			printf("loadAI ");
			defaultPrintArgs(inst);
			break;
		case LOADA0:
			printf("add ");
			defaultPrintArgs(inst);
			break;
//Character Loads
		case CLOAD:
			printf("cload ");
			printArg(inst, 0);
			printf(" => ");
			printArg(inst, 1);
			printf("\n");
			break;
		case CLOADAI:
			printf("cloadAI ");
			defaultPrintArgs(inst);
			break;
		case CLOADA0:
			printf("cloadA0 ");
			defaultPrintArgs(inst);
			break;
//Store Instructions
		case STORE:
			printf("store ");
			printArg(inst, 0);
			printf(" => ");
			printArg(inst, 1);
			printf("\n");
			break;
		case STOREAI:
			printf("storeAI ");
			printArg(inst, 0);
			printf(" => ");
			printArg(inst, 1);
			printf(", ");
			printArg(inst, 2);
			printf("\n");
			break;
		case STOREA0:
			printf("storeA0 ");
			printArg(inst, 0);
			printf(" => ");
			printArg(inst, 1);
			printf(", ");
			printArg(inst, 2);
			printf("\n");
			break;
//Character Store
		case CSTORE:
			printf("cstore ");
			printArg(inst, 0);
			printf(" => ");
			printArg(inst, 1);
			printf("\n");
			break;
		case CSTOREAI:
			printf("cstoreAI ");
			printArg(inst, 0);
			printf(" => ");
			printArg(inst, 1);
			printf(", ");
			printArg(inst, 2);
			printf("\n");
			break;
		case CSTOREA0:
			printf("cstoreA0 ");
			printArg(inst, 0);
			printf(" => ");
			printArg(inst, 1);
			printf(", ");
			printArg(inst, 2);
			printf("\n");
			break;
//Register Conversions
		case I2I:
			printf("i2i ");
			printArg(inst, 0);
			printf(" => ");
			printArg(inst, 1);
			printf("\n");
			break;
		case C2C:
			printf("c2c ");
			printArg(inst, 0);
			printf(" => ");
			printArg(inst, 1);
			printf("\n");
			break;
		case C2I:
			printf("c2i ");
			printArg(inst, 0);
			printf(" => ");
			printArg(inst, 1);
			printf("\n");
			break;
		case I2C:
			printf("i2c ");
			printArg(inst, 0);
			printf(" => ");
			printArg(inst, 1);
			printf("\n");
			break;
//Flow Control
		case JUMPI:
			printf("jumpI ");
			printf("-> ");
			printArg(inst, 0);
			printf("\n");
			break;
		case JUMP:
			printf("jump ");
			printf("-> ");
			printArg(inst, 0);
			printf("\n");
			break;
		case CBR:
			printf("cbr ");
			printArg(inst, 0);	
			printf("-> ");
			printArg(inst, 1);
			printf(", ");
			printArg(inst, 2);
			printf("\n");
			break;
		case CMP_LT:
			printf("cmp_LT ");
			printArg(inst, 0);
			printf(", ");
			printArg(inst, 1);
			printf(" -> ");
			printArg(inst, 2);
			printf("\n");
			break;
		case CMP_LE:
			printf("cmp_LE ");
			printArg(inst, 0);
			printf(", ");
			printArg(inst, 1);
			printf(" -> ");
			printArg(inst, 2);
			printf("\n");
			break;
		case CMP_EQ:
			printf("cmp_EQ ");
			printArg(inst, 0);
			printf(", ");
			printArg(inst, 1);
			printf(" -> ");
			printArg(inst, 2);
			printf("\n");
			break;
		case CMP_GE:
			printf("cmp_GE ");
			printArg(inst, 0);
			printf(", ");
			printArg(inst, 1);
			printf(" -> ");
			printArg(inst, 2);
			printf("\n");
			break;
		case CMP_GT:
			printf("cmp_GT ");
			printArg(inst, 0);
			printf(", ");
			printArg(inst, 1);
			printf(" -> ");
			printArg(inst, 2);
			printf("\n");
			break;
		case CMP_NE:
			printf("cmp_NE ");
			printArg(inst, 0);
			printf(", ");
			printArg(inst, 1);
			printf(" -> ");
			printArg(inst, 2);
			printf("\n");
			break;
	}
}

void printArg(INST* inst, int index)
{
	switch(inst->argType[index])
	{
		case IREGISTER:
			if(inst->args[index] == FP)
				printf("fp");
			else if(inst->args[index] == RBSS)
				printf("rbss");
			else if(inst->args[index] == RARP)
				printf("rarp");
			else
				printf("t%d", inst->args[index]);
			break;

		case ICONSTANT:/*
			if(inst->specialReg[index] == FP)
				printf("fp+");
			else if(inst->specialReg[index] == RBSS)
				printf("rbss+");
			else if(inst->specialReg[index] == RARP)
				printf("rarp+");*/
			if(inst->idType == NONE)
				printf("%d", inst->args[index]);
			else
				switch(inst->idType)
				{
					case BOOL:
						if(inst->literal.integer == 0) //true
							printf("true");
						else
							printf("false");
						break;
					case INT:	
						printf("%d", inst->literal.integer);
						break;
					case FLOAT:
						printf("%f", inst->literal.floating);
						break;
					case CHAR:
						printf("%c", inst->literal.character);
						break;
					case STRING:
						printf("%s", inst->literal.string);
						break;
				}				
			break;

		case ILABEL:
			printf("L%d", inst->args[index]);
			break;
	}
}

INST*	createInstruction(int instruction, ...)
{
	va_list arg;       
	va_start (arg, instruction);

	INST* newInst = calloc(1,sizeof(INST));
	
	newInst->instruction = instruction;
	newInst->instLabel = -1;
	newInst->idType = NONE;

	switch(instruction)
	{
	//Three registers
		case ADD:
		case SUB:
		case MULT:
		case DIV:
		case LSHIFT:
		case RSHIFT:
		case LOADA0:
		case CLOADA0:
		case AND:
		case OR:
		case XOR:
		case STOREA0:
		case CSTOREA0:
		case CMP_LT:
		case CMP_LE:
		case CMP_EQ:
		case CMP_GE:
		case CMP_GT:
		case CMP_NE:
			newInst->argType[0] = IREGISTER;
			newInst->argType[1] = IREGISTER;
			newInst->argType[2] = IREGISTER;
			newInst->args[0] = va_arg(arg,int);
			newInst->args[1] = va_arg(arg,int);
			newInst->args[2] = va_arg(arg,int);
			break;
	//Register Constant Register
		case ADDI:
		case SUBI:
		case RSUBI:
		case MULTI:
		case DIVI:
		case RDIVI:
		case LSHIFTI:
		case RSHIFTI:
		case ANDI:
		case ORI:
		case XORI:
		case LOADAI:
		case CLOADAI:
			newInst->argType[0] = IREGISTER;
			newInst->argType[1] = ICONSTANT;
			newInst->argType[2] = IREGISTER;
			newInst->args[0] = va_arg(arg,int);
			newInst->args[1] = va_arg(arg,int);
			newInst->args[2] = va_arg(arg,int);
			break;
	//Register Register Constant
		case STOREAI:
		case CSTOREAI:
			newInst->argType[0] = IREGISTER;
			newInst->argType[1] = IREGISTER;
			newInst->argType[2] = ICONSTANT;
			newInst->args[0] = va_arg(arg,int);
			newInst->args[1] = va_arg(arg,int);
			newInst->args[2] = va_arg(arg,int);
			break;
	//Register Label Label
		case CBR:
			newInst->argType[0] = IREGISTER;
			newInst->argType[1] = ILABEL;
			newInst->argType[2] = ILABEL;
			newInst->args[0] = va_arg(arg,int);
			newInst->args[1] = va_arg(arg,int);
			newInst->args[2] = va_arg(arg,int);
			break;
	//Two Registers
		case LOAD:
		case CLOAD:
		case STORE:
		case CSTORE:
		case I2I:
		case C2C:
		case C2I:
		case I2C:
			newInst->argType[0] = IREGISTER;
			newInst->argType[1] = IREGISTER;
			newInst->args[0] = va_arg(arg,int);
			newInst->args[1] = va_arg(arg,int);
			break;
	//Constant Register
		case LOADI:
			newInst->argType[0] = ICONSTANT;
			newInst->argType[1] = IREGISTER;
			newInst->literal = va_arg(arg,VALUE);
			newInst->args[1] = va_arg(arg,int);
			newInst->idType = va_arg(arg,int);
			break;
	//Single Register
		case JUMP:
			newInst->argType[0] = IREGISTER;
			newInst->args[0] = va_arg(arg,int);
			break;
	//Single Label
		case JUMPI:
			newInst->argType[0] = ILABEL;
			newInst->args[0] = va_arg(arg,int);
			break;
		default:
			break;
	}
	return newInst;	
}

void	destroyInstruction(INST* inst)
{
	free(inst);
}

void 	addInstructionLabel(INST* inst, int label)
{
	inst->instLabel = label;
}

void	addInstructionSpecialRegister(INST* inst, int index, int reg)
{
	if(reg <= FP && reg >= RARP) //Check if register is valid
	{
		inst->specialReg[index] = reg;
	}
}

ILIST*	mergeInstructionLists(ILIST* l1, ILIST* l2)
{
	ILIST* tempList = l1;

	if(l1 == NULL)
	{
		return l2;
	}

	while(tempList->next != NULL){tempList = tempList->next;}

	tempList->next = l2;
	return l1;
}

void 	destroyInstructionList(ILIST* l)
{
	ILIST* tempList = l;
	ILIST* nextList;
	if(l != NULL)
	{
		while(tempList != NULL)
		{
			destroyInstruction(tempList->instruction);
			nextList = tempList->next;
			free(tempList);
			tempList = nextList;
		}
	}
}

ILIST*	createInstructionList(INST* inst)
{
	ILIST* myList = calloc(1,sizeof(ILIST));
	myList->instruction = inst;
	myList->next = NULL;
	return myList;
}

void	addInstruction(ILIST* l, INST* instruction)
{
	ILIST* tempList = l;

	while(tempList->next != NULL){tempList = tempList->next;}

	ILIST* newList = createInstructionList(instruction);
	mergeInstructionLists(l, newList);
}

void 	printInstructionList(ILIST* l)
{
	if(l != NULL)
	{
		while(l != NULL)
		{
			printInstruction(l->instruction);
			l = l->next;
		}
	}
}
