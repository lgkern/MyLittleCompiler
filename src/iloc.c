#include <stdlib.h>
#include <stdio.h>

void 	printInstruction(INST* inst)
{
	if(inst->instLabel != NULL)
		printf("%s:",inst->instLabel);

	switch(inst->instruction)
	{
		case NOP:
			printf("nop\n");
			break;
		case ADD:
			printArg(inst, 0);
			printf(", ");
			printArg(inst, 1);
			printf(" => ");
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
