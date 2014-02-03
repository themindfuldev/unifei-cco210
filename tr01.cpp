/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 1 - Entrega: 13/08/2004                                           *
*   Proposto: Ordenar uma lista linear seqüencial de valores inteiros          *
*                                                                              *
*   Nome: Tiago Romero Garcia                                                  *
*   Matrícula: 12643                                                           *
*   Ciência da Computação / 1° ano, 2° semestre                                *
*                                                                              *
*******************************************************************************/

#include <conio.h>
#include <malloc.h>
#include <stdio.h>

// Definição de constante
#define LIM 100

// Definição das estruturas
typedef struct LISTA {
  int Valor;
  int Prox;
} LISTA;

// Definição de protótipos das funções
int InsereLista(LISTA *, int &, int &, int);
void Listar(LISTA *, int, int);

//----------------------------------------------------------------------------//

// Início do programa main()
void main(void)
{

  // Definição das variáveis
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

  // Inserção na lista
  for (int i=0; i<max; i++) {
    InsereLista(lis, iPi, iPf, i);
  } // Fim for

  // Listagem dos nós
  Listar(lis, max, iPi);

} // Fim de main

//----------------------------------------------------------------------------//

// Função InsereLista: Insere um valor na lista em ordem crescente
int InsereLista(LISTA *lis, int &iPi, int &iPf, int pos)
{

  // Definição das variáveis
  int val, posa, posp=iPi, iPa=iPi;

  // Inserção de Info(NO)
  printf("\tDigite o valor do no %d: ", pos);
  scanf("%d", &val);
  lis[pos].Valor = val;

  // Organização de Prox(NO):

  // Incremento de iPf
  if (lis[iPf].Valor > val)
    lis[iPf].Prox = pos+1;

  // Se o valor digitado for menor que o do índice do início da lista (iPi)
  if (val <= lis[iPi].Valor) {
    lis[pos].Prox = iPi;
    iPi = pos;
    if (lis[iPi].Valor == lis[iPf].Valor) {
      lis[iPf].Prox = pos+1;
    }
    return 1;   // Término da inserção
  }
  else {

    // Se for maior que o de iPf
    if (val >= lis[iPf].Valor) {
      lis[pos].Prox = pos+1;
      iPf = pos;
      return 1; // Término da inserção
    }

    // Senão, procura a posição correta de inserção do nó,
    // armazena as posições anterior e posterior e insere o nó entre estas
    while (val > lis[iPa].Valor) {
      posa = posp;
      posp = lis[posa].Prox;
      iPa = posp;
    }
    lis[pos].Prox = posp;
    lis[posa].Prox = pos;
    return 1; // Término da inserção
  }

} // Fim de InsereLista

//----------------------------------------------------------------------------//

// Função Listar: Lista os valores armazenados na lista
void Listar(LISTA *lis, int max, int iPi)
{

  // Listagem dos nós na ordem seqüencial da lista
  printf("\n\tLista na ordem sequencial:\n");
  for (int i=0; i<max; i++) {
    printf("\t  Lista[%d]: Valor = %d, Prox = %d\n", i, lis[i].Valor, lis[i].Prox);
  }
  printf("\tO primeiro no e Lista[%d]\n", iPi);

  // Listagem dos nós em ordem crescente dos valores
  printf("\n\tLista em ordem crescente dos valores:\n");
  for (int i=iPi; i<max; i=lis[i].Prox) {
    printf("\t  Lista[%d]: Valor = %d, Prox = %d\n", i, lis[i].Valor, lis[i].Prox);
  }
  getch();

} // Fim de Listar
