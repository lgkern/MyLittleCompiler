#include "misc.h"
#include "main.h"
#include "gv.h"
#include <stdlib.h>

extern int numLines;

int getLineNumber (void)
{
  //implemente esta função
  return numLines;
}

void yyerror (char const *mensagem)
{
  printf ("Erro na linha %d. Mensagem: %s\n", numLines, mensagem); //altere para que apareça a linha
}

void main_init (int argc, char **argv)
{	
  //implemente esta função com rotinas de inicialização, se necessário
	createTable();
	//gv_init("output.dot");
}

void main_finalize (void)
{
  //implemente esta função com rotinas de inicialização, se necessário
	destroyTable();
//	gv_close();
}
