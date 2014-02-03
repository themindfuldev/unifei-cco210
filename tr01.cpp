/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 1 - Entrega: 13/08/2004                                           *
*   Proposto: Ordenar uma lista linear seq�encial de valores inteiros          *
*                                                                              *
*   Nome: Tiago Romero Garcia                                                  *
*   Matr�cula: 12643                                                           *
*   Ci�ncia da Computa��o / 1� ano, 2� semestre                                *
*                                                                              *
*******************************************************************************/

#include <conio.h>
#include <malloc.h>
#include <stdio.h>

// Defini��o de constante
#define LIM 100

// Defini��o das estruturas
typedef struct LISTA {
  int Valor;
  int Prox;
} LISTA;

// Defini��o de prot�tipos das fun��es
int InsereLista(LISTA *, int &, int &, int);
void Listar(LISTA *, int, int);

//----------------------------------------------------------------------------//

// In�cio do programa main()
void main(void)
{

  // Defini��o das vari�veis
  int max, iPi=0, iPf=0;
  LISTA lis[LIM];

  // Estrutura do programa:

  // Leitura do tamanho da lista
  do {
    clrscr();
    printf("\n     1o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
    printf("\n     Nome: Tiago Romero Garcia - Matricula: 12643 - CCO 2004\n\n");
    printf("\n\tDigite com quantos numeros deseja trabalhar: ");
    scanf("%d", &max);
    if ((max<1)||(max>100)) {
      printf("\n\n\tDigite um valor entre 1 e 100!\n\t[Pressione qualquer tecla para continuar...]\n\a");
      getch();
    }
  } // Fim do
  while ((max<1)||(max>100));
  printf("\n");

  // Inser��o na lista
  for (int i=0; i<max; i++) {
    InsereLista(lis, iPi, iPf, i);
  } // Fim for

  // Listagem dos n�s
  Listar(lis, max, iPi);

} // Fim de main

//----------------------------------------------------------------------------//

// Fun��o InsereLista: Insere um valor na lista em ordem crescente
int InsereLista(LISTA *lis, int &iPi, int &iPf, int pos)
{

  // Defini��o das vari�veis
  int val, posa, posp=iPi, iPa=iPi;

  // Inser��o de Info(NO)
  printf("\tDigite o valor do no %d: ", pos);
  scanf("%d", &val);
  lis[pos].Valor = val;

  // Organiza��o de Prox(NO):

  // Incremento de iPf
  if (lis[iPf].Valor > val)
    lis[iPf].Prox = pos+1;

  // Se o valor digitado for menor que o do �ndice do in�cio da lista (iPi)
  if (val <= lis[iPi].Valor) {
    lis[pos].Prox = iPi;
    iPi = pos;
    if (lis[iPi].Valor == lis[iPf].Valor) {
      lis[iPf].Prox = pos+1;
    }
    return 1;   // T�rmino da inser��o
  }
  else {

    // Se for maior que o de iPf
    if (val >= lis[iPf].Valor) {
      lis[pos].Prox = pos+1;
      iPf = pos;
      return 1; // T�rmino da inser��o
    }

    // Sen�o, procura a posi��o correta de inser��o do n�,
    // armazena as posi��es anterior e posterior e insere o n� entre estas
    while (val > lis[iPa].Valor) {
      posa = posp;
      posp = lis[posa].Prox;
      iPa = posp;
    }
    lis[pos].Prox = posp;
    lis[posa].Prox = pos;
    return 1; // T�rmino da inser��o
  }

} // Fim de InsereLista

//----------------------------------------------------------------------------//

// Fun��o Listar: Lista os valores armazenados na lista
void Listar(LISTA *lis, int max, int iPi)
{

  // Listagem dos n�s na ordem seq�encial da lista
  printf("\n\tLista na ordem sequencial:\n");
  for (int i=0; i<max; i++) {
    printf("\t  Lista[%d]: Valor = %d, Prox = %d\n", i, lis[i].Valor, lis[i].Prox);
  }
  printf("\tO primeiro no e Lista[%d]\n", iPi);

  // Listagem dos n�s em ordem crescente dos valores
  printf("\n\tLista em ordem crescente dos valores:\n");
  for (int i=iPi; i<max; i=lis[i].Prox) {
    printf("\t  Lista[%d]: Valor = %d, Prox = %d\n", i, lis[i].Valor, lis[i].Prox);
  }
  getch();

} // Fim de Listar
