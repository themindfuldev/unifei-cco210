#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição de constantes
#define MAX 100

// Definição da estrutura
typedef struct dPILHA {
  char Exp;
  dPILHA *Prox;
} dPILHA;

// Definição de protótipos
int  CriaPilhas(dPILHA *&, dPILHA *&, char *);
int  dPush(dPILHA *&, char);
char *dPop(dPILHA *&);

//----------------------------------------------------------------------------//

// Início do programa main
void main(void) {

  // Definição de variáveis locais
  dPILHA *PilhaA, *PilhaB;
  char Exp[MAX];
  int ret;

  // Inicialização da pilha
  PilhaA = PilhaB = NULL;

  // Leitura da expressão
  clrscr();
  printf("\n\tDigite a expressao: ");
  gets(Exp);

  // Verificando a pilha
  ret = CriaPilhas(PilhaA, PilhaB, Exp);
  if (ret == -1) printf("\n\tERRO: Expressao incorreta!\n\t      Lembre-se de usar apenas numeros positivos.");
  else if (ret == -2) printf("\n\tERRO: Divisao por zero!");
  else printf("\n\tResultado: %d", ret);

  printf("\n\t[Pressione qualquer tecla para terminar...]\n");
  getch();

} // Fim de main

//----------------------------------------------------------------------------//

// Função CriaPilha: Cria a pilha de operadores
int CriaPilhas(dPILHA *&PilhaA, dPILHA *&PilhaB, char *Exp) {

  // Definição de variáveis locais
  int ret = 1, tam = strlen(Exp), numA, numB;
  char *op;

  // Varrendo a expressão
  for (int i=0; (i<tam)&&(ret!=-2); i++) {
    switch(Exp[i]) {
      case '(':
      case '[':
      case '{':
      case '+':
      case '-':
      case '*':
      case '/':
        dPush(PilhaB, Exp[i]);
        break;

      case ')':
        op = dPop(PilhaA);
        if (op[0] == 'e') ret = -1;
        numA = atoi(op);
        op = dPop(PilhaA);
        if (op[0] == 'e') ret = -1;
        numB = atoi(op);
        op = dPop(PilhaB);
        if (op[0] == 'e') ret = -1;
        switch (op[0]) {
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
        itoa(numA, op, 10);
        dPush(PilhaA, op[0]);
        op = dPop(PilhaB);
        if (op[0] != '(') ret = -1;
        break;

      case ']':
        op = dPop(PilhaA);
        if (op[0] == 'e') ret = -1;
        numA = atoi(op);
        op = dPop(PilhaA);
        if (op[0] == 'e') ret = -1;
        numB = atoi(op);
        op = dPop(PilhaB);
        if (op[0] == 'e') ret = -1;
        switch (op[0]) {
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
        itoa(numA, op, 10);
        dPush(PilhaA, op[0]);
        op = dPop(PilhaB);
        if (op[0] != '[') ret = -1;
        break;

      case '}':
        op = dPop(PilhaA);
        if (op[0] == 'e') ret = -1;
        numA = atoi(op);
        op = dPop(PilhaA);
        if (op[0] == 'e') ret = -1;
        numB = atoi(op);
        op = dPop(PilhaB);
        if (op[0] == 'e') ret = -1;
        switch (op[0]) {
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
        itoa(numA, op, 10);
        dPush(PilhaA, op[0]);
        op = dPop(PilhaB);
        if (op[0] != '{') ret = -1;
        break;

      default:
        dPush(PilhaA, Exp[i]);
    }
  }

  if ((PilhaB != NULL)||(PilhaA == NULL)) ret = -1;
  else if ((ret != -2)&&(ret != -1)) {
    op = "";
    op[0] = PilhaA->Exp;
    ret = atoi(op);
  }

  return ret;

} // Fim de CriaPilha

//----------------------------------------------------------------------------//

// Função dPush: Empilha um valor numa pilha
int dPush(dPILHA *&Pilha, char Valor) {

  // Definição de variáveis locais
  dPILHA *Px;

  // Verificando Overflow
  //if (Oper.Topo >= MAX-1) return -1;

  // Alocando o nó
  Px = (dPILHA *) calloc (1,sizeof(dPILHA));
  if (!Px) return -1;

  Px->Exp = Valor;
  Px->Prox = Pilha;
  Pilha = Px;

  return 1;

} // Fim de dPush

//----------------------------------------------------------------------------//

// Função dPop: Desempilha um valor de uma pilha
char *dPop(dPILHA *&Pilha) {

  // Definição de variáveis locais
  char *Valor = "";

  // Verificando Underflow
  if (Pilha == NULL)
    Valor[0] = 'e';
  else {
    Valor[0] = Pilha->Exp;
    Pilha = Pilha->Prox;
  }

  return Valor;

} // Fim de dPop