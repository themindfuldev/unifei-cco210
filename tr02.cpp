/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 2 - Entrega: 13/08/2004                                           *
*   Proposto: Criar e listar um baralho de 52 cartas                           *
*                                                                              *
*   Nome: Tiago Romero Garcia                                                  *
*   Matr�cula: 12643                                                           *
*   Ci�ncia da Computa��o / 1� ano, 2� semestre                                *
*                                                                              *
*******************************************************************************/

#include <conio.h>
#include <malloc.h>
#include <stdio.h>

// Defini��o das estruturas
typedef struct CARTA {
  int Naipe, Valor, Posicao;
  CARTA *Prox;
} CARTA;

// Defini��o de prot�tipos das fun��es
CARTA *AlocaCarta(void);

//----------------------------------------------------------------------------//

// In�cio do programa main()
void main(void)
{
  // Defini��o das vari�veis
  CARTA *Pinicio, *Pfinal, *Pnew;
  char *nNaipe, *nPosicao;

  // Estrutura do programa
  clrscr();
  printf("\n     2o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
  printf("\n     Nome: Tiago Romero Garcia - Matricula: 12643 - CCO 2004\n\n");

  // Cria��o do baralho
  Pnew = Pinicio = Pfinal = AlocaCarta();
  for (int naipe=1; naipe<=4; naipe++) {
    Pnew->Naipe = naipe;
    for (int valor=1; valor<=13; valor++) {
      Pnew->Valor = valor;
      Pnew->Posicao = 1;
      Pnew->Prox = NULL;
      Pfinal->Prox = Pnew;
      Pnew = AlocaCarta();
      Pfinal = Pfinal->Prox;
      Pfinal->Naipe = naipe;
    }
  }

  // Listagem do baralho
  printf("\n     Listagem do baralho:\n     [Pressione qualquer tecla para continuar...]\n\n");
  getch();

  Pnew = Pinicio;
  for (int i=1; Pnew; i++, Pnew=Pnew->Prox) {
    switch (Pnew->Posicao) {
      case 0: nPosicao = "cima";
              break;

      case 1: nPosicao = "baixo";
              break;

      default: nPosicao = "(?)";
               break;
    }
    switch (Pnew->Naipe) {
      case 1: nNaipe = "Copas";
              break;

      case 2: nNaipe = "Paus";
              break;

      case 3: nNaipe = "Ouros";
              break;

      case 4: nNaipe = "Espadas";
              break;

      default: nNaipe = "(?)";
               break;
    }
    switch (Pnew->Valor) {
      case 1: printf("\tCarta %d: As de %s virado para %s\n", i, nNaipe, nPosicao);
              break;

      case 11: printf("\tCarta %d: J de %s virado para %s\n", i, nNaipe, nPosicao);
               break;

      case 12: printf("\tCarta %d: Q de %s virado para %s\n", i, nNaipe, nPosicao);
               break;

      case 13: printf("\tCarta %d: K de %s virado para %s\n", i, nNaipe, nPosicao);
               break;

      default: printf("\tCarta %d: %d de %s virado para %s\n", i, Pnew->Valor, nNaipe, nPosicao);
               break;
    }
    if ((i%20==0)||(i==52)) {
      printf("\a\n\n     [Pressione qualquer tecla para continuar...]\n");
      getch();
      printf("\n");
    }
  }

} // Fim de main

//----------------------------------------------------------------------------//

// Fun��o AlocaCarta: Aloca na mem�ria uma carta
CARTA *AlocaCarta(void) {
  CARTA *P;
  P = (CARTA *) calloc (1, sizeof(CARTA));
  return P;
}

