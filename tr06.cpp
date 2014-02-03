/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 6 - Entrega: 27/8/2004                                            *
*   Problema de Josephus                                                       *
*                                                                              *
*   Nome: Cláudio Paulo Faustino                Matrícula: 12620               *
*   Nome: Tiago Romero Garcia                   Matrícula: 12643               *
*   Ciências da Computação / 1° ano, 2° semestre                               *
*                                                                              *
*******************************************************************************/

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

// Declaração das estruturas
typedef struct Josephus {
  char Nome[30];
  Josephus *Prox;
} Josephus;

// Protótipos das funções
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

// Função main
void main() {

  // Declaração de variáveis
  Josephus *LEDinicio, *Sfinal=NULL, *S;
  int Nsol, num, nnum, op;

  // Leitura do número de soldados
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

    // Número de soldados cadastrados
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

      case 51: // Modificar número de soldados do grupo
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

      default: // Opção inválida
               printf("\n\n\n\t\aOpcao invalida!\n\t[Pressione qualquer tecla para continuar...]\n");
               getch();
               break;
    }
  }
  while (op!=52);

} // Fim de main

//----------------------------------------------------------------------------//

// Função AlocaNo: Aloca um nó na lista
Josephus *AlocaNo(void) {

  // Declaração de variáveis
  Josephus *p;

  // Alocação de memória
  p = (Josephus *) calloc (1, sizeof(Josephus));

  // Retorno de p;
  return p;

} // Fim de AlocaNo

//----------------------------------------------------------------------------//

// Função CriaLED: Cria uma Lista de Espaço Disponível (LED)
Josephus *CriaLED(int num) {

  // Declaração de variáveis
  Josephus *Pinicio, *Pnovo, *Pfinal;

  // Criação da lista
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

// Função InsereNo: Insere um nó em uma lista
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

// Função MenuJosephus: Cria o menu
int MenuJosephus(int Nsol, int num) {

  // Declaração de variáveis
  int op;

  // Impressão do menu
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

  // Retorna a opção escolhida
  return op;
} // Fim de MenuJosephus

//----------------------------------------------------------------------------//

// Função InsereS: Insere um soldado na LS a partir de um nó da LED
int InsereS(Josephus *&LEDinicio, Josephus *&Sfinal) {

  // Declaração de variáveis
  Josephus *Pnovo, *Paux;

  // Verificação da existência da LED
  if (!LEDinicio) return 0;

  // Requisição do nó
  Pnovo = RequisitaNo(LEDinicio);

  // Leitura do nome
  printf("\n\n\n\tDigite o nome do soldado: ");
  scanf("%s", Pnovo->Nome);

  // Inserir nó na LS
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

// Função RequisitaNo: Requisita um nó da LED para a LS
Josephus	*RequisitaNo(Josephus *&LEDinicio) {

  // Declaração de variáveis
  Josephus *Pnovo;

  // Requisição do nó
  Pnovo = LEDinicio;
  LEDinicio = LEDinicio->Prox;
  Pnovo->Prox = NULL;

  // Retorna nó requisitado
  return Pnovo;
} // Fim de RequisitaNo

//----------------------------------------------------------------------------//

// Função SoldadoBuscaAjuda: Seleciona um soldado para buscar ajuda
int SoldadoBuscaAjuda(Josephus *&Sfinal, Josephus *&LEDinicio, int num) {

  // Declaração de variáveis
  Josephus *Paux;
  int Nsol, Npul;

  // Verificação da existência da LS
  if (!Sfinal) return 0;

  // Leitura do número de saltos
  printf("\n\n\n\tVoce quer pular de quantos em quantos? ");
  scanf("%d", &Npul);

  // Sorteio do soldado inical da contagem
  randomize();
  Nsol = rand()%num;

  // Posicionamento do Sfinal no nó do soldado sorteado
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

  // Exibição do soldado escolhido
  printf("\n\n\tO soldado %s foi escalado para buscar ajuda!", Sfinal->Nome);

  // Devolução do soldado escolhido
  DevolveNo(Sfinal, LEDinicio);
  Sfinal = NULL;

  return 1;
} // Fim de SoldadoBuscaAjuda

//----------------------------------------------------------------------------//

// Função DevolveNo: Devolve um nó para LED
int DevolveNo(Josephus *&Paux, Josephus *&LEDinicio) {

  // Declaração de variáveis
  Josephus *Sfinal;

  // Retirada da LS
  Sfinal = Paux->Prox;
  Paux->Prox = Sfinal->Prox;

  // Devolução do nó para a LED
  Sfinal->Prox = LEDinicio;
  LEDinicio = Sfinal;

  return 1;
} // Fim de DevolveNo

//----------------------------------------------------------------------------//

// Função LiberaLED: Libera a LED
int LiberaLED(Josephus *&LEDinicio) {

  // Declaração de variáveis
  Josephus *P = LEDinicio, *Paux;

  if (LEDinicio == NULL) return 0;

  // Varredura e liberação dos elementos da lista
  while (P != NULL) {
    Paux = P;
    P = P->Prox;
    free(Paux);
  }

  // Anulação da lista
  LEDinicio = NULL;

  return 1;
} // Fim de LiberaLED
