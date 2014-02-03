/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 6 - Entrega: 27/8/2004                                            *
*   Problema de Josephus                                                       *
*                                                                              *
*   Nome: Cl�udio Paulo Faustino                Matr�cula: 12620               *
*   Nome: Tiago Romero Garcia                   Matr�cula: 12643               *
*   Ci�ncias da Computa��o / 1� ano, 2� semestre                               *
*                                                                              *
*******************************************************************************/

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

// Declara��o das estruturas
typedef struct Josephus {
  char Nome[30];
  Josephus *Prox;
} Josephus;

// Prot�tipos das fun��es
Josephus *AlocaNo(void);
Josephus *CriaLED(int);
int       DevolveNo(Josephus *&, Josephus *&);
int       InsereNo(Josephus *, Josephus *&);
int       InsereS(Josephus *&, Josephus *&);
int       LiberaLED(Josephus *&);
int       MenuJosephus(int, int);
Josephus	*RequisitaNo(Josephus *&);
int       SoldadoBuscaAjuda(Josephus *&, Josephus *&, int);

//----------------------------------------------------------------------------//

// Fun��o main
void main() {

  // Declara��o de vari�veis
  Josephus *LEDinicio, *Sfinal=NULL, *S;
  int Nsol, num, nnum, op;

  // Leitura do n�mero de soldados
  do {
    clrscr();
    printf("\n     6o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
    printf("\n     Nome: Claudio Paulo Faustino - Matricula: 12620 - CCO 2004");
    printf("\n     Nome: Tiago Romero Garcia    - Matricula: 12643 - CCO 2004\n");
    printf("\n\n\tQuantos soldados existem no grupo? ");
    scanf("%d", &num);
    if (num<1) {
      printf("\n\n\t\aDigite um valor positivo!\n\t[Pressione qualquer tecla para continuar...]\n");
      getch();
    }
    else {
      LEDinicio = CriaLED(num);
      if (!LEDinicio) {
        printf("\n\n\t\aMemoria insuficiente!\n\t[Pressione qualquer tecla para continuar...]\n");
        getch();
      }
    }
  }
  while ((num<1)||(!LEDinicio));

  do {

    // N�mero de soldados cadastrados
    Nsol = 0;
    S = LEDinicio;
    while (S != NULL) {
      S = S->Prox;
      Nsol++;
    }
    Nsol = num-Nsol;

    // Menu
    op = MenuJosephus(Nsol, num);
    switch(op) {
      case 49: // Inserir soldado
               if (InsereS(LEDinicio, Sfinal))
                 printf("\n\n\t\aSoldado inserido.\n\t[Pressione qualquer tecla para continuar...]\n");
               else
                 printf("\n\n\n\t\aTodos os soldados ja foram inseridos.\n\t[Pressione qualquer tecla para continuar...]\n");
               getch();
               break;

      case 50: // Selecionar soldado para buscar ajuda
               if (SoldadoBuscaAjuda(Sfinal, LEDinicio, num))
                 printf("\n\n\n\t\aGrupo de soldados desmanchado.\n\t[Pressione qualquer tecla para continuar...]\n");
               else
                 printf("\n\n\n\t\aNao existem soldados cadastrados.\n\t[Pressione qualquer tecla para continuar...]\n");
               getch();
               break;

      case 51: // Modificar n�mero de soldados do grupo
               printf("\n\n\n\tQuantos soldados existem no grupo? ");
               scanf("%d", &nnum);
               if (nnum<1)
                 printf("\n\n\n\t\aDigite um valor positivo!\n\t[Pressione qualquer tecla para continuar...]\n");
               else {
                 Sfinal = NULL;
                 LEDinicio = CriaLED(nnum);
                 if (!LEDinicio)
                   printf("\n\n\n\t\aMemoria insuficiente!\n\t[Pressione qualquer tecla para continuar...]\n");
                 else {
                   printf("\n\n\n\t\aGrupo de soldados recriado.\n\t[Pressione qualquer tecla para continuar...]\n");
                   num = nnum;
                 }
               }
               getch();
               break;

      case 52: // Sair
               if (Sfinal != NULL) {
                 printf("\n\n\n\t\aExistem soldados no grupo. Selecione um para buscar ajuda.\n\t[Pressione qualquer tecla para continuar...]\n");
                 getch();
                 op = 0;
                 break;
               }

               if (LiberaLED(LEDinicio))
                 printf("\n\n\n\t\aMemoria liberada...\n\t[Pressione qualquer tecla para continuar...]\n");
               else
                 printf("\n\n\n\t\aMemoria nao liberada...\n\t[Pressione qualquer tecla para continuar...]\n");
               getch();
               break;

      default: // Op��o inv�lida
               printf("\n\n\n\t\aOpcao invalida!\n\t[Pressione qualquer tecla para continuar...]\n");
               getch();
               break;
    }
  }
  while (op!=52);

} // Fim de main

//----------------------------------------------------------------------------//

// Fun��o AlocaNo: Aloca um n� na lista
Josephus *AlocaNo(void) {

  // Declara��o de vari�veis
  Josephus *p;

  // Aloca��o de mem�ria
  p = (Josephus *) calloc (1, sizeof(Josephus));

  // Retorno de p;
  return p;

} // Fim de AlocaNo

//----------------------------------------------------------------------------//

// Fun��o CriaLED: Cria uma Lista de Espa�o Dispon�vel (LED)
Josephus *CriaLED(int num) {

  // Declara��o de vari�veis
  Josephus *Pinicio, *Pnovo, *Pfinal;

  // Cria��o da lista
  Pinicio = Pnovo = Pfinal = AlocaNo();
  InsereNo(Pnovo, Pfinal);
  for (int i=1; i<num; i++) {
    Pnovo = AlocaNo();
    InsereNo(Pnovo, Pfinal);
  }

  // Retorno do ponteiro inicial
  return Pinicio;

} // Fim de CriaLED

//----------------------------------------------------------------------------//

// Fun��o InsereNo: Insere um n� em uma lista
int InsereNo(Josephus *Pnovo, Josephus *&Pfinal) {

  // Se for o primeiro da lista
  if (Pnovo == Pfinal) {
    Pnovo->Prox = NULL;
    return 1;
  }

  // Inserindo na lista
  Pnovo->Prox = NULL;
  Pfinal->Prox = Pnovo;
  Pfinal = Pnovo;

  // Retorno
  return 1;

} // Fim de InsereNo

//----------------------------------------------------------------------------//

// Fun��o MenuJosephus: Cria o menu
int MenuJosephus(int Nsol, int num) {

  // Declara��o de vari�veis
  int op;

  // Impress�o do menu
  clrscr();
  printf("\n     6o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
  printf("\n     Nome: Claudio Paulo Faustino - Matricula: 12620 - CCO 2004");
  printf("\n     Nome: Tiago Romero Garcia    - Matricula: 12643 - CCO 2004\n\n");
  printf("\n\tGrupo de soldados: %d cadastrados, maximo de %d\n", Nsol, num);
  printf("\n\tMenu de Opcoes:");
  printf("\n\n\t  1. Inserir soldado");
  printf("\n\t  2. Selecionar soldado para buscar ajuda");
  printf("\n\t  3. Modificar numero de soldados do grupo");
  printf("\n\t  4. Sair");
  printf("\n\n\tDigite sua opcao: ");
  op = getch();

  // Retorna a op��o escolhida
  return op;
} // Fim de MenuJosephus

//----------------------------------------------------------------------------//

// Fun��o InsereS: Insere um soldado na LS a partir de um n� da LED
int InsereS(Josephus *&LEDinicio, Josephus *&Sfinal) {

  // Declara��o de vari�veis
  Josephus *Pnovo, *Paux;

  // Verifica��o da exist�ncia da LED
  if (!LEDinicio) return 0;

  // Requisi��o do n�
  Pnovo = RequisitaNo(LEDinicio);

  // Leitura do nome
  printf("\n\n\n\tDigite o nome do soldado: ");
  scanf("%s", Pnovo->Nome);

  // Inserir n� na LS
  if (!Sfinal) {
    Sfinal = Pnovo;
    Pnovo->Prox = Sfinal;
  }
  else {
    Paux = Sfinal->Prox;
    InsereNo(Pnovo, Sfinal);
    Sfinal->Prox = Paux;
  }

  return 1;
} // Fim de de InsereS

//----------------------------------------------------------------------------//

// Fun��o RequisitaNo: Requisita um n� da LED para a LS
Josephus	*RequisitaNo(Josephus *&LEDinicio) {

  // Declara��o de vari�veis
  Josephus *Pnovo;

  // Requisi��o do n�
  Pnovo = LEDinicio;
  LEDinicio = LEDinicio->Prox;
  Pnovo->Prox = NULL;

  // Retorna n� requisitado
  return Pnovo;
} // Fim de RequisitaNo

//----------------------------------------------------------------------------//

// Fun��o SoldadoBuscaAjuda: Seleciona um soldado para buscar ajuda
int SoldadoBuscaAjuda(Josephus *&Sfinal, Josephus *&LEDinicio, int num) {

  // Declara��o de vari�veis
  Josephus *Paux;
  int Nsol, Npul;

  // Verifica��o da exist�ncia da LS
  if (!Sfinal) return 0;

  // Leitura do n�mero de saltos
  printf("\n\n\n\tVoce quer pular de quantos em quantos? ");
  scanf("%d", &Npul);

  // Sorteio do soldado inical da contagem
  randomize();
  Nsol = rand()%num;

  // Posicionamento do Sfinal no n� do soldado sorteado
  for (int i=0; i<Nsol; i++)
    Sfinal = Sfinal->Prox;
  printf("\n\n\tSoldado sorteado: %s\n", Sfinal->Nome);

  // Processo de contagem
  while (Sfinal->Prox != Sfinal) {
    for (int i=0; i<Npul; i++) {
      Paux = Sfinal;
      Sfinal = Sfinal->Prox;
    }
    printf("\n\tSoldado retirado: %s", Sfinal->Nome);
    DevolveNo(Paux, LEDinicio);
    Sfinal = Paux;
  }

  // Exibi��o do soldado escolhido
  printf("\n\n\tO soldado %s foi escalado para buscar ajuda!", Sfinal->Nome);

  // Devolu��o do soldado escolhido
  DevolveNo(Sfinal, LEDinicio);
  Sfinal = NULL;

  return 1;
} // Fim de SoldadoBuscaAjuda

//----------------------------------------------------------------------------//

// Fun��o DevolveNo: Devolve um n� para LED
int DevolveNo(Josephus *&Paux, Josephus *&LEDinicio) {

  // Declara��o de vari�veis
  Josephus *Sfinal;

  // Retirada da LS
  Sfinal = Paux->Prox;
  Paux->Prox = Sfinal->Prox;

  // Devolu��o do n� para a LED
  Sfinal->Prox = LEDinicio;
  LEDinicio = Sfinal;

  return 1;
} // Fim de DevolveNo

//----------------------------------------------------------------------------//

// Fun��o LiberaLED: Libera a LED
int LiberaLED(Josephus *&LEDinicio) {

  // Declara��o de vari�veis
  Josephus *P = LEDinicio, *Paux;

  if (LEDinicio == NULL) return 0;

  // Varredura e libera��o dos elementos da lista
  while (P != NULL) {
    Paux = P;
    P = P->Prox;
    free(Paux);
  }

  // Anula��o da lista
  LEDinicio = NULL;

  return 1;
} // Fim de LiberaLED
