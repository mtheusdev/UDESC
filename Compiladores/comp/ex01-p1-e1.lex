%{
/* Linguagem: Pascal-like */

/* ========================================================================== */
/* Abaixo, indicado pelos limitadores "%{" e "%}", as includes necessárias... */
/* ========================================================================== */

/* Para as funções atoi() e atof() */
#include <math.h>

/* ========================================================================== */
/* =========================== Sessão DEFINIÇÔES ========================== */
/* ========================================================================== */
%}

DIGITO [0-9]
ID [a-z][a-z0-9]*

%%

{DIGITO}+"."{DIGITO}*"E"{DIGITO}+ {
printf( "Um valor positivo em not cienfitica: %s\n", yytext);
}

{DIGITO}+"."{DIGITO}*"E-"{DIGITO}+ {
printf( "Um valor negativo em not cienfitica: %s\n", yytext);
}

"-"{DIGITO}+ {
printf( "Um valor inteiro negativo: %s (%d)\n", yytext,
atoi( yytext ) );
}
{DIGITO}+ {
printf( "Um valor inteiro positivo: %s (%d)\n", yytext,
atoi( yytext ) );
}

"-"{DIGITO}+"."{DIGITO}* {
printf( "Um valor real negativo: %s (%g)\n", yytext,
atof( yytext ) );
}

{DIGITO}+"."{DIGITO}* {
printf( "Um valor real positivo: %s (%g)\n", yytext,
atof( yytext ) );
}


if|then|begin|end|procedure|function {
printf( "Uma palavra-chave: %s\n", yytext );
}

{ID} printf( "Um identificador: %s\n", yytext );

"+"|"-"|"*"|"/" printf( "Um operador: %s\n", yytext );

"{"[^}\n]*"}" /* Lembre-se... comentários não tem utilidade! */

[ \t\n]+ /* Lembre-se... espaços em branco não tem utilidade! */

. printf( "Caracter não reconhecido: %s\n", yytext );

%%

int main( argc, argv )
int argc;
char **argv;
{
++argv, --argc;
if ( argc > 0 )
yyin = fopen( argv[0], "r" );
else
yyin = stdin;

yylex();

return 0;
}
