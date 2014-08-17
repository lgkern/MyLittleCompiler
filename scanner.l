/*
  Coloque aqui o identificador do grupo e dos seus membros
*/
%{
#include "parser.h" //arquivo automaticamente gerado pelo bison
%}

ALPHA	[A-Za-z]
DIGIT	[0-9]
IDTERM	[ |\t]
INTEGER [-?{DIGIT}+]

%%
/*Palavras Reservadas da Linguagem*/
intIDTERM       return  TK_PR_INT;
{floatIDTERM}
{boolIDTERM}
{charIDTERM}
{stringIDTERM}
{ifIDTERM}
{thenIDTERM}
{elseIDTERM}
{whileIDTERM}
{doIDTERM}
{inputIDTERM}
{outputIDTERM}
{returnIDTERM}

/*Caracteres Especiais*/
{,}
{;}
{:}
{(}
{)}
{\[}
{\]}
{{}
{}}
{+}
{-}
{*}
{/}
{<}
{>}
{=}
{!}
{&}
{$}

/*Operadores Compostos*/
{<=}
{>=}
{==}
{!=}
{&&}
{\|\|}

/*Identificadores*/
{{ALPHA_}{ALPHADIGIT_}*IDTERM}

/*Literais*/
{INTEGER}
{INTEGER.{DIGIT}+}
{(false)|(true)]}
{'.'}//. é qualquer caractere menos o new-line
{".*"}

%%
