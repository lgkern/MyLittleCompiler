#include "misc.h"
#include <stdlib.h>

extern int numLines;

int getLineNumber (void)
{
  //implemente esta função
  return numLines;
}

void yyerror (char const *mensagem)
{
  fprintf (stderr, "%s\n", mensagem); //altere para que apareça a linha
}

void main_init (int argc, char **argv)
{	
  //implemente esta função com rotinas de inicialização, se necessário
	createTable();
}

void main_finalize (void)
{
  //implemente esta função com rotinas de inicialização, se necessário
	destroyTable();
}
