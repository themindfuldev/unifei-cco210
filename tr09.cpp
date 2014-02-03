#include <conio.h>
#include <stdio.h>

// Definição dos tipos e constantes
#define MAX 10

typedef struct FILA {
  int Fila[MAX];
  int Base, Limite, P, U;
} FILA;

// Protótipos das funções
int InsereNaFila(FILA &, int);
int Menu(void);
int NumeroDeErro(int);
int RemoveDaFila(FILA &);
int Sucessor(FILA, int);

//----------------------------------------------------------------------------//

// Programa main
void main(void) {

  // Variáveis do programa
  FILA Fila;
  int Valor, Opcao=0;

  // Inicialização de fila
  Fila.Base = Fila.P = Fila.U = 0;
  Fila.Limite = MAX-1;

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
      		  Valor = InsereNaFila(Fila, Valor);
              if (Valor < 0) {
                NumeroDeErro(Valor);
                getch();
              }
              break;

      case 2: // Remove da fila
      		  Valor = RemoveDaFila(Fila);
              if (Valor >= 0) printf("\n\n\tValor removido: %d\n\t[Pressione qualquer tecla para continuar...]\n", Valor);
              else NumeroDeErro(Valor);
              getch();
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

// Função InsereNaFila: Insere um valor na fila
int InsereNaFila(FILA &Fila, int Valor) {

  // Verificando Overflow
  if (Sucessor(Fila, Fila.P) == Fila.U) return -1;

  // Inserindo um elemento
  Fila.Fila[Fila.P] = Valor;
  Fila.P = Sucessor(Fila, Fila.P);
  return Valor;

} // Fim de InsereNaFila

//----------------------------------------------------------------------------//

// Função Menu: Cria um menu
int Menu(void) {

  // Variáveis locais
  int Opcao;

  // Impressão do menu
  clrscr();
  printf("\n\tCCO210 - Prof. Sdnei Brito - Trabalho 9\n");
  printf("\tNome: Claudio Paulo Faustino   Mat: 12620   CCO2004\n");
  printf("\tNome: Tiago Romero Garcia      Mat: 12643   CCO2004\n\n\n");
  printf("\tMenu de opcoes:\n\n");
  printf("\t  1. Inserir valor na fila\n");
  printf("\t  2. Remover valor da fila\n");
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
int RemoveDaFila(FILA &Fila) {

  // Variáveis locais
  int Valor;

  // Verificando Underflow
  if (Fila.P == Fila.U) return -2;

  // Retirando o elemento
  Valor = Fila.Fila[Fila.U];
  Fila.U = Sucessor(Fila, Fila.U);
  return Valor;

} // Fim de RemoveDaFila

//----------------------------------------------------------------------------//

// Função Sucessor: Circula a lista
int Sucessor(FILA Fila, int Px) {

  if (Px >= Fila.Limite) return Fila.Base;
  return ++Px;

} // Fim de Sucessor
