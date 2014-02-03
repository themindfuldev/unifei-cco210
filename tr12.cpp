/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 11 - Entrega: 27/8/2004                                           *
*   Avalia express�es matem�ticas usando pilha encadeada                       *
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
#include <malloc.h>

// Defini��o de constantes
#define MAX 100

// Defini��o da estrutura
typedef struct sPILHA {
  char Exp;
  sPILHA *Prox;
} sPILHA;

// Defini��o de prot�tipos
int CriaPilha(sPILHA *&, char *);
int sPush(sPILHA *&, char);
char sPop(sPILHA *&);
sPILHA *AlocaNo(void);

//----------------------------------------------------------------------------//

// In�cio do programa main
void main(void) {

  // Defini��o de vari�veis locais
  sPILHA *Topo;
  char Exp[MAX];
  Topo=NULL;

  // Leitura da express�o
  clrscr();
  printf("\n     12o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
  printf("\n     Nome: Claudio Paulo Faustino - Matricula: 12620 - CCO 2004");
  printf("\n     Nome: Tiago Romero Garcia    - Matricula: 12643 - CCO 2004\n");
  printf("\n\tDigite a expressao: ");
  gets(Exp);

  // Verificando a pilha
  if (CriaPilha(Topo, Exp) == 1) printf("\n\tExpressao correta!");
  else if (CriaPilha(Topo, Exp) == -1) printf("\n\tExpressao incorreta!");

  printf("\n\t[Pressione qualquer tecla para terminar...]\n");
  getch();

} // Fim de main

//----------------------------------------------------------------------------//

//Fun��o AlocaNo: Aloca mem�ria para insercao de dados
sPILHA *AlocaNo(void) {
  sPILHA *Px;
  Px = (sPILHA *) calloc (1, sizeof(sPILHA));
  return Px;
} // Fim de AlocaNo

//----------------------------------------------------------------------------//

// Fun��o CriaPilha: Cria a pilha de operadores
int CriaPilha(sPILHA *&Topo, char *Exp) {

  // Defini��o de vari�veis locais
  int ret = 1, tam = strlen(Exp);

  // Varrendo a pilha
  for (int i=0; i<tam; i++) {
    switch(Exp[i]) {
      case '(':
      case '[':
      case '{':
        sPush(Topo, Exp[i]);
        break;

      case ')':
        if (sPop(Topo) != '(') ret = -1;
        break;

      case ']':
        if (sPop(Topo) != '[') ret = -1;
        break;

      case '}':
        if (sPop(Topo) != '{') ret = -1;
        break;
    }
  }

  if (Topo) ret = -1;

  return ret;

} // Fim de CriaPilha

//----------------------------------------------------------------------------//

// Fun��o sPush: Empilha um valor numa pilha
int sPush(sPILHA *&Topo, char Valor) {
  //Variaveis locais
  sPILHA *p;

  p=AlocaNo();

  if(Topo==NULL){

    Topo=p;
    Topo->Exp=Valor;
    Topo->Prox=NULL;

    return 1;

  }//fim do if

  //iserindo no
  p->Exp=Valor;
  p->Prox=Topo;
  Topo=p;

  return 1;

} // Fim de sPush

//----------------------------------------------------------------------------//

// Fun��o sPop: Desempilha um valor de uma pilha
char sPop(sPILHA *&Topo) {

  // Defini��o de vari�veis locais
  sPILHA *p;
  char Valor;

  // Verificando Underflow
  if (!Topo) return -1;

  //realizando desempilhamento

  Valor = Topo->Exp;
  p=Topo;
  Topo=Topo->Prox;
  p->Prox=NULL;

  free(p);

  return Valor;

} // Fim de sPop

