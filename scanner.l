/*
  Coloque aqui o identificador do grupo e dos seus membros
*/
ALPHA	[A-Za-z]
DIGIT	[0-9]
IDTERM	[ |\t]
INTEGER [-?{DIGIT}+]

%{
#include "parser.h" //arquivo automaticamente gerado pelo bison
%}

%%
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

{<=}
{>=}
{==}
{!=}
{&&}
{\|\|}


{{ALPHA_}{ALPHADIGIT_}*IDTERM}

{INTEGER}
{INTEGER.{DIGIT}+}
{(false)|(true)]}
{'.'}
{".*"}

%%
