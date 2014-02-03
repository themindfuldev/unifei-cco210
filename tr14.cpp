/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 11 - Entrega: 27/8/2004                                           *
*   Calcula express�es matem�ticas usando pilha encadeada                      *
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

// Defini��o de estruturas
typedef struct dPILHAf {
  float Valor;
  dPILHAf *Prox;
} dPILHAf;

typedef struct dPILHAc {
  char Valor;
  dPILHAc *Prox;
} dPILHAc;

// Defini��o de prot�tipos
float CriaPilhas(dPILHAf *&, dPILHAc *&, char *);
int   dPushc(dPILHAc *&, char);
int   dPushf(dPILHAf *&, float);
char  dPopc(dPILHAc *&);
float dPopf(dPILHAf *&);

//----------------------------------------------------------------------------//

// In�cio do programa main
void main(void) {

  // Defini��o de vari�veis locais
  dPILHAf *PilhaA;
  dPILHAc *PilhaB;
  char Exp[MAX] = "";
  float ret;

  // Inicializa��o da pilha
  PilhaA = NULL;
  PilhaB = NULL;

  // Leitura da express�o
  clrscr();
  printf("\n     14o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
  printf("\n     Nome: Claudio Paulo Faustino - Matricula: 12620 - CCO 2004");
  printf("\n     Nome: Tiago Romero Garcia    - Matricula: 12643 - CCO 2004\n");
  printf("\n\n     O programa funciona com:\n\t\t(, ), [, ], {, }, +, -, *, / e inteiros entre 0 e 9");
  printf("\n\n\tDigite a expressao: ");
  gets(Exp);

  // Verificando a pilha
  ret = CriaPilhas(PilhaA, PilhaB, Exp);
  if (ret == -1) printf("\n\tERRO: Expressao incorreta!\n\t      Lembre-se de usar apenas numeros positivos.");
  else if (ret == -2) printf("\n\tERRO: Divisao por zero!");
  else printf("\n\tResultado: %2.2f", ret);

  printf("\n\t[Pressione qualquer tecla para terminar...]\n");
  getch();

} // Fim de main

//----------------------------------------------------------------------------//

// Fun��o CriaPilha: Cria a pilha de operadores
float CriaPilhas(dPILHAf *&PilhaA, dPILHAc *&PilhaB, char *Exp) {

  // Defini��o de vari�veis locais
  int tam = strlen(Exp);
  float ret = 1, numA, numB;
  char op, *cnum="";

  // Varre a express�o
  for (int i=0; (i<tam)&&(ret!=-2); i++) {
    switch(Exp[i]) {
      case '(':
      case '[':
      case '{':
      case '+':
      case '-':
      case '*':
      case '/':
        dPushc(PilhaB, Exp[i]);
        break;

      case ')':
        numA = dPopf(PilhaA);
        if (numA == -1) ret = -1;
        numB = dPopf(PilhaA);
        if (numB == -1) ret = -1;
        op = dPopc(PilhaB);
        if (op == 'e') ret = -1;
        switch (op) {
          case '+':
            numA = numB+numA;
            break;

          case '-':
            numA = numB-numA;
            break;

          case '*':
            numA = numB*numA;
            break;

          case '/':
            if (numA == 0) {
              ret = -2;
              break;
            }
            numA = numB/numA;
            break;

          default:
            ret = -1;
        }
        dPushf(PilhaA, numA);
        op = dPopc(PilhaB);
        if (op != '(') ret = -1;
        break;

      case ']':
        numA = dPopf(PilhaA);
        if (numA == -1) ret = -1;
        numB = dPopf(PilhaA);
        if (numB == -1) ret = -1;
        op = dPopc(PilhaB);
        if (op == 'e') ret = -1;
        switch (op) {
          case '+':
            numA = numB+numA;
            break;

          case '-':
            numA = numB-numA;
            break;

          case '*':
            numA = numB*numA;
            break;

          case '/':
            if (numA == 0) {
              ret = -2;
              break;
            }
            numA = numB/numA;
            break;

          default:
            ret = -1;
        }
        dPushf(PilhaA, numA);
        op = dPopc(PilhaB);
        if (op != '[') ret = -1;
        break;

      case '}':
        numA = dPopf(PilhaA);
        if (numA == -1) ret = -1;
        numB = dPopf(PilhaA);
        if (numB == -1) ret = -1;
        op = dPopc(PilhaB);
        if (op == 'e') ret = -1;
        switch (op) {
          case '+':
            numA = numB+numA;
            break;

          case '-':
            numA = numB-numA;
            break;

          case '*':
            numA = numB*numA;
            break;

          case '/':
            if (numA == 0) {
              ret = -2;
              break;
            }
            numA = numB/numA;
            break;

          default:
            ret = -1;
        }
        dPushf(PilhaA, numA);
        op = dPopc(PilhaB);
        if (op != '{') ret = -1;
        break;

      default:
        if (i == 0) ret = -1;
        cnum[0] = Exp[i];
        dPushf(PilhaA, atof(cnum));
    }
  }

  if ((PilhaB != NULL)||(PilhaA == NULL)) ret = -1;
  else if ((ret != -2)&&(ret != -1)) {
    ret = PilhaA->Valor;
  }

  return ret;

} // Fim de CriaPilha

//----------------------------------------------------------------------------//

// Fun��o dPushc: Empilha um valor numa pilha char
int dPushc(dPILHAc *&Pilha, char Valor) {

  // Defini��o de vari�veis locais
  dPILHAc *Px;

  // Verificando Overflow
  //if (Oper.Topo >= MAX-1) return -1;

  // Alocando o n�
  Px = (dPILHAc *) calloc (1, sizeof(dPILHAc));
  if (!Px) return -1;

  Px->Valor = Valor;
  Px->Prox = Pilha;
  Pilha = Px;

  return 1;

} // Fim de dPushc

//----------------------------------------------------------------------------//

// Fun��o dPopf: Desempilha um valor de uma pilha char
char dPopc(dPILHAc *&Pilha) {

  // Defini��o de vari�veis locais
  dPILHAc *Px=Pilha;
  char Valor;

  // Verificando Underflow
  if (Pilha == NULL) return 'e';

  Valor = Pilha->Valor;
  Pilha = Pilha->Prox;
  free(Px);

  return Valor;

} // Fim de dPopf

//----------------------------------------------------------------------------//

// Fun��o dPushf: Empilha um valor numa pilha float
int dPushf(dPILHAf *&Pilha, float Valor) {

  // Defini��o de vari�veis locais
  dPILHAf *Px;

  // Verificando Overflow
  //if (Oper.Topo >= MAX-1) return -1;

  // Alocando o n�
  Px = (dPILHAf *) calloc (1, sizeof(dPILHAf));
  if (!Px) return -1;

  Px->Valor = Valor;
  Px->Prox = Pilha;
  Pilha = Px;

  return 1;

} // Fim de dPushf

//----------------------------------------------------------------------------//

// Fun��o dPopf: Desempilha um valor de uma pilha float
float dPopf(dPILHAf *&Pilha) {

  // Defini��o de vari�veis locais
  dPILHAf *Px=Pilha;
  float Valor;

  // Verificando Underflow
  if (Pilha == NULL) return -1;

  Valor = Pilha->Valor;
  Pilha = Pilha->Prox;
  free(Px);

  return Valor;

} // Fim de dPopf