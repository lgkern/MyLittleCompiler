#include "iloc.h"
#include <stdlib.h>
#include <stdio.h>

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
	if(inst->instLabel != NULL)
		printf("%s:",inst->instLabel);

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
			printf("add ");
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
			if(inst->regs[index] == FP)
				printf("fp");
			else if(inst->regs[index] == RBSS)
				printf("rbss");
			else if(inst->regs[index] == RARP)
				printf("rarp");
			else
				printf("t%d", inst->regs[index]);
			break;
		case ICONSTANT:
			printf("%d", inst->consts[index]);
			break;
		case ILABEL:
			printf("%s", inst->labels[index]);
			break;
	}
}
