#include <conio.h>
#include <malloc.h>
#include <stdio.h>

// Definição dos tipos e constantes
#define MAX 10

typedef struct FILA {
  int Valor;
  FILA *Prox;
} FILA;

// Protótipos das funções
FILA *AlocaNo(void);
int InsereNaFila(FILA *&, FILA *&, int);
int Listagem(FILA *);
int Menu(void);
int NumeroDeErro(int);
int RemoveDaFila(FILA *&);

//----------------------------------------------------------------------------//

// Programa main
void main(void) {

  // Variáveis do programa
  FILA *Pi, *Pf;
  int Valor, Opcao=0;

  // Inicialização dos ponteiros
  Pi = Pf = NULL;

  // Iniciando o programa
  while (Opcao != 9) {
    Opcao = Menu();
    switch (Opcao) {
      case 1: // Insere na fila
              do {
                printf("\n\n\tDigite o valor: ");
                scanf("%d", &Valor);
                if (Valor < 0) {
                  printf("\n\n\tDigite um valor positivo!\n\t[Pressione qualquer tecla para continuar...]\n");
                  getch();
                }
              }
              while (Valor < 0);
      		  Valor = InsereNaFila(Pi, Pf, Valor);
              if (Valor < 0) {
                NumeroDeErro(Valor);
                getch();
              }
              break;

      case 2: // Remove da fila
      		  Valor = RemoveDaFila(Pi);
              if (Valor >= 0) printf("\n\n\tValor removido: %d\n\t[Pressione qualquer tecla para continuar...]\n", Valor);
              else NumeroDeErro(Valor);
              getch();
              break;

      case 3: // Lista a fila
              if (Pi == NULL) {
                printf("\n\n\tA fila esta vazia!\n\t[Pressione qualquer tecla para continuar...]\n");
                getch();
              }
              else Listagem(Pi);
              break;

      case 9: // Fim do programa
      		  printf("\n\n\tFim do programa!\n\t[Pressione qualquer tecla para continuar...]\n");
              getch();
              break;

      default: // Erro de opção
               printf("\n\n\tEscolha uma opcao valida!\n\t[Pressione qualquer tecla para continuar...]\n");
               getch();
               break;
      } // Fim switch
   } // Fim while

} // Fim do programa

//----------------------------------------------------------------------------//

// Função AlocaNo: Aloca um nó na memória
FILA *AlocaNo(void) {
  FILA *P;
  P = (FILA *) calloc (1, sizeof(FILA));
  return P;
}

//----------------------------------------------------------------------------//

// Função InsereNaFila: Insere um valor na fila
int InsereNaFila(FILA *&Pi, FILA *&Pf, int Valor) {

  // Variáveis locais
  FILA *Px=Pi;
  int Nos=1;

  // Verificando Overflow
  while (Px!=NULL) {
    Px = Px->Prox;
    Nos++;
  }
  if (Nos >= MAX) return -1;

  // Alocando o nó
  Px = AlocaNo();
  Px->Valor = Valor;

  // Inserindo o primeiro elemento
  if (Pi == NULL) {
    Pi = Pf = Px;
    return Valor;
  }

  // Inserindo um elemento
  Pf->Prox = Px;
  Pf = Px;
  return Valor;

} // Fim de InsereNaFila

//----------------------------------------------------------------------------//

// Função Listagem: Lista a fila
int Listagem(FILA *Pi) {

  // Variáveis locais
  FILA *Px=Pi;
  int i=1;

  printf("\n\n");

  while (Px != NULL) {
    printf("\t%do. valor = %d\n", i++, Px->Valor);
    Px = Px->Prox;
  }

  printf("\n\t[Pressione qualquer tecla para continuar...]\n");

  getch();
  return 1;

} // Fim de Listagem

//----------------------------------------------------------------------------//

// Função Menu: Cria um menu
int Menu(void) {

  // Variáveis locais
  int Opcao;

  // Impressão do menu
  clrscr();
  printf("\n\tCCO210 - Prof. Sdnei Brito - Trabalho 10\n");
  printf("\tNome: Claudio Paulo Faustino   Mat: 12620   CCO2004\n");
  printf("\tNome: Tiago Romero Garcia      Mat: 12643   CCO2004\n\n\n");
  printf("\tMenu de opcoes:\n\n");
  printf("\t  1. Inserir valor na fila\n");
  printf("\t  2. Remover valor da fila\n");
  printf("\t  3. Lista a fila\n");
  printf("\t  9. Sair\n\n");
  printf("\tEntre com sua opcao: ");
  scanf("%d", &Opcao);
  return Opcao;

} // Fim de Menu

//----------------------------------------------------------------------------//
int NumeroDeErro(int Erro) {

  // Imprime o numero de erro
  printf("\n\n\tNumero do erro: %d", Erro);

  switch(Erro) {
    case -1: // Overflow
             printf("\n\tErro: Overflow!");
             break;

    case -2: // Nao ha valor para ser retirado
             printf("\n\tErro: Nao ha valor para ser retirado!");
             break;

    case -3: // Underlow
             printf("\n\tErro: Underflow!");
             break;

    default: // Erro de opcao
             break;
  }

  printf("\n\t[Pressione qualquer tecla para continuar...]\n");
  return 0;

} // Fim de NumeroDeErro

//----------------------------------------------------------------------------//

// Função RemoveDaFila: Remove um valor da fila
int RemoveDaFila(FILA *&Pi) {

  // Variáveis locais
  FILA *Px = Pi;
  int Valor;

  // Verificando Underflow
  if (Pi == NULL) return -2;

  // Retirando o elemento
  Valor = Px->Valor;
  Pi = Pi->Prox;
  free(Px);
  return Valor;

} // Fim de RemoveDaFila
