#ifndef _ERROR_CODES_
#define _ERROR_CODES_

#define IKS_SUCESS		            0

//Verificação de declarações
#define IKS_ERROR_UNDECLARED	    1   //identificador não declarado
#define IKS_ERROR_DECLARED	        2   //identificador já declarado

//Uso incorreto de identificadores
#define IKS_ERROR_VARIABLE	        3   //identificador deve ser usado como variável
#define	IKS_ERROR_VECTOR	        4   //identificador deve ser usado como vetor
#define IKS_ERROR_FUNCTION	        5   //identificador deve ser usado como função

//Tipos e tamanhos de dados
#define	IKS_ERROR_WRONG_TYPE	    6   //tipos incompatíveis
#define	IKS_ERROR_STRING_TO_X	    7   //coerção impossível do tipo string
#define	IKS_ERROR_CHAR_TO_X	        8   //coerção impossível do tipo char

//Argumentos e parâmetros
#define	IKS_ERROR_MISSING_ARGS		9   //faltam argumentos
#define	IKS_ERROR_EXCESS_ARGS		10  //sobram argumentos
#define	IKS_ERROR_WRONG_TYPE_ARGS	11  //argumentos incompatíveis

//Verificação de tipos em comandos
#define	IKS_ERROR_WRONG_PAR_INPUT   12  //Parâmetro não é identificador
#define	IKS_ERROR_WRONG_PAR_OUTPUT  13  //parâmetro não é literal string ou expressão
#define	IKS_ERROR_WRONG_PAR_RETURN  14  //parâmetro não é compatível com tipo do retorno

#endif
