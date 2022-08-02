%{
/* Linguagem: Pascal-like */

/* ========================================================================== */
/* Abaixo, indicado pelos limitadores "%{" e "%}", as includes necessárias... */
/* ========================================================================== */

/* Para as funções atoi() e atof() */
#include <math.h>
#include <string.h>
char text[100];
/* ========================================================================== */
/* =========================== Sessão DEFINIÇÔES ========================== */
/* ========================================================================== */
%}

TEXTO [a-z||A-Z||' ']*

%%
{TEXTO} {
  strcat(text,yytext);
}

"<HIDE" {
  strcat (text,yytext);
}
"HIDE>" {
  strcat (text,yytext);
}
">"{TEXTO}"</" {
  int len = strlen(yytext);
  char arr[1] = ">";
  char ar[2] = "</";
  char x[1] = "X";
  char vet[len-3];
  for(int i = 0; i < (len-3);i++){
    strcpy(&vet[i],"X");
  }

  strcat(text,arr);
  strcat(text,vet);
  strcat(text,ar);
}
"\n" {
     printf("Saída: %s\n", text);
}

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
