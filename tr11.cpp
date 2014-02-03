/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 11 - Entrega: 27/8/2004                                           *
*   Avalia express�es matem�ticas usando pilha seq�encial                      *
*                                                                              *
*   Nome: Cl�udio Paulo Faustino                Matr�cula: 12620               *
*   Nome: Tiago Romero Garcia                   Matr�cula: 12643               *
*   Ci�ncias da Computa��o / 1� ano, 2� semestre                               *
*                                                                              *
*******************************************************************************/

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defini��o de constantes
#define MAX 100

// Defini��o da estrutura
typedef struct sPILHA {
  char Exp[MAX];
  int Base, Limite, Topo;
} sPILHA;

// Defini��o de prot�tipos
int  CriaPilha(sPILHA &, char *);
int  sPush(sPILHA &, char);
char sPop(sPILHA &);

//----------------------------------------------------------------------------//

// In�cio do programa main
void main(void) {

  // Defini��o de vari�veis locais
  sPILHA Oper;
  char Exp[MAX];

  // Inicializa��o da pilha
  Oper.Base = 0;
  Oper.Limite = MAX-1;
  Oper.Topo = -1;

  // Leitura da express�o
  clrscr();
  printf("\n     11o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
  printf("\n     Nome: Claudio Paulo Faustino - Matricula: 12620 - CCO 2004");
  printf("\n     Nome: Tiago Romero Garcia    - Matricula: 12643 - CCO 2004\n");
  printf("\n\n\tDigite a expressao: ");
  gets(Exp);

  // Verificando a pilha
  if (CriaPilha(Oper, Exp) == 1) printf("\n\tExpressao correta!");
  else if (CriaPilha(Oper, Exp) == -1) printf("\n\tExpressao incorreta!");

  printf("\n\t[Pressione qualquer tecla para terminar...]\n");
  getch();

} // Fim de main

//----------------------------------------------------------------------------//

// Fun��o CriaPilha: Cria a pilha de operadores
int CriaPilha(sPILHA &Oper, char *Exp) {

  // Defini��o de vari�veis locais
  int ret = 1, tam = strlen(Exp);

  // Varrendo a pilha
  for (int i=0; i<tam; i++) {
    switch(Exp[i]) {
      case '(':
      case '[':
      case '{':
        sPush(Oper, Exp[i]);
        break;

      case ')':
        if (sPop(Oper) != '(') ret = -1;
        break;

      case ']':
        if (sPop(Oper) != '[') ret = -1;
        break;

      case '}':
        if (sPop(Oper) != '{') ret = -1;
        break;
    }
  }

  if (Oper.Topo != -1) ret = -1;

  return ret;

} // Fim de CriaPilha

//----------------------------------------------------------------------------//

// Fun��o sPush: Empilha um valor numa pilha
int sPush(sPILHA &Oper, char Valor) {

  // Verificando Overflow
  if (Oper.Topo >= MAX-1) return -1;

  Oper.Topo++;
  Oper.Exp[Oper.Topo] = Valor;

  return 1;

} // Fim de sPush

//----------------------------------------------------------------------------//

// Fun��o sPop: Desempilha um valor de uma pilha
char sPop(sPILHA &Oper) {

  // Defini��o de vari�veis locais
  char Valor;

  // Verificando Underflow
  if (Oper.Topo < Oper.Base) return -1;

  Valor = Oper.Exp[Oper.Topo];
  Oper.Topo--;

  return Valor;

} // Fim de sPop

