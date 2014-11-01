#include "generators.h"

int genRegister()
{
	static int i = -1;
	i++;
	return i;
}
int genLabel()
{
	static int i = -1;
	i++;
	return i;
}

