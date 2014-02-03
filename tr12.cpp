/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 11 - Entrega: 27/8/2004                                           *
*   Avalia expressões matemáticas usando pilha encadeada                       *
*                                                                              *
*   Nome: Cláudio Paulo Faustino                Matrícula: 12620               *
*   Nome: Tiago Romero Garcia                   Matrícula: 12643               *
*   Ciências da Computação / 1° ano, 2° semestre                               *
*                                                                              *
*******************************************************************************/

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Definição de constantes
#define MAX 100

// Definição da estrutura
typedef struct sPILHA {
  char Exp;
  sPILHA *Prox;
} sPILHA;

// Definição de protótipos
int CriaPilha(sPILHA *&, char *);
int sPush(sPILHA *&, char);
char sPop(sPILHA *&);
sPILHA *AlocaNo(void);

//----------------------------------------------------------------------------//

// Início do programa main
void main(void) {

  // Definição de variáveis locais
  sPILHA *Topo;
  char Exp[MAX];
  Topo=NULL;

  // Leitura da expressão
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

//Função AlocaNo: Aloca memória para insercao de dados
sPILHA *AlocaNo(void) {
  sPILHA *Px;
  Px = (sPILHA *) calloc (1, sizeof(sPILHA));
  return Px;
} // Fim de AlocaNo

//----------------------------------------------------------------------------//

// Função CriaPilha: Cria a pilha de operadores
int CriaPilha(sPILHA *&Topo, char *Exp) {

  // Definição de variáveis locais
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

// Função sPush: Empilha um valor numa pilha
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

// Função sPop: Desempilha um valor de uma pilha
char sPop(sPILHA *&Topo) {

  // Definição de variáveis locais
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

