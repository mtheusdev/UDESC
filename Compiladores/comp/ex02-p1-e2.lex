%{
/* Linguagem: Pascal-like */

/* ========================================================================== */
/* Abaixo, indicado pelos limitadores "%{" e "%}", as includes necessárias... */
/* ========================================================================== */

/* Para as funções atoi() e atof() */
int numeroRomano = 0;
/* ========================================================================== */
/* =========================== Sessão DEFINIÇÔES ========================== */
/* ========================================================================== */
%}


%%


"I" {
  numeroRomano += 1;
}

"V" {
  numeroRomano += 5;
}
"X" {
  numeroRomano += 10;
}
"L" {
  numeroRomano += 50;
}
"C" {
  numeroRomano += 100;
}
"D" {
  numeroRomano += 500;
}
"M" {
  numeroRomano += 1000;
}

"\n" {
   printf("Numero transformado: %d\n", numeroRomano);numeroRomano = 0;
}
. printf( "Caracter não reconhecido: %s\n", yytext );

%%

int main( argc, argv )
int argc;
char **argv;
{
++argv, --argc;
if ( argc > 0 )
yyin = fopen( argv[0], "r" );
else{
  yyin = stdin;
}

yylex();



return 0;
}
