/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 5 - Entrega: 20/08/2004                                           *
*   Proposto: Simular um jogo de Vinte e Um                                    *
*                                                                              *
*   Nome: Cl�udio Paulo Faustino                   Matr�cula: 12620            *
*   Nome: Tiago Romero Garcia                      Matr�cula: 12643            *
*   Ci�ncia da Computa��o / 1� ano, 2� semestre                                *
*                                                                              *
*******************************************************************************/

#include <conio.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

// Defini��o da estrutura
typedef struct Carta {
  int Nipe, Posicao, Valor;
  Carta *Prox;
} Carta;

// Defini��o de prot�tipos
Carta *AlocaCarta(void);
int CriaBaralho(Carta *&);
int Embaralha(Carta *&);
int ListaBaralho(Carta *);
int Joga21(Carta *);

//----------------------------------------------------------------------------//

// Inicio da fun��o main
void main(void) {

	// Declara��o de vari�veis
   Carta *Pinicio;
   int op=0;

   // Cria o menu
   while(op!=50) {
      clrscr();
      printf("\n     5o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
      printf("\n     Nome: Claudio Paulo Faustino - Matricula: 12620 - CCO 2004");
      printf("\n     Nome: Tiago Romero Garcia    - Matricula: 12643 - CCO 2004\n\n");
      printf("\n\tEscolha uma das operacoes abaixo.\n");
      printf("\n\t  1. Jogar");
      printf("\n\t  2. Sair");
      printf("\n\n\tDigite sua opcao: ");
      op = getch();

	   switch(op) {
   		case 49: // Jogar
   			// Cria��o do baralho
			   CriaBaralho(Pinicio);
			   // Embaralhando o baralho
			   Embaralha(Pinicio);
	   		// Jogo
		   	Joga21(Pinicio);
   	      break;

      	case 50: // Sair
      		printf("\n\n\n\tFinalizando...\n\t[Pressione qualquer tecla para continuar...]\n");
	         getch();
   	      break;

      	default: // Op��o inv�lida
      		printf("\n\n\n\tDigite uma opcao valida!\n\t[Pressione qualquer tecla para continuar...]\n");
	         getch();
	         break;
   	}
   }
} // Fim da fun��o main

//----------------------------------------------------------------------------//

// Fun��o AlocaCarta: aloca mem�ria para o armazenamento de uma carta
Carta *AlocaCarta(void){

   // Declara��o de vari�veis
   Carta *p;

   // Aloca��o da carta
   p = (Carta *) calloc (1, sizeof(Carta));

   // Retorno
   return p;

} // Fim da fun��o AlocaCarta

//----------------------------------------------------------------------------//

// Fun��o CriaBaralho: cria um baralho de 52 cartas
int CriaBaralho(Carta *&Pinicio) {

	// Declara��o de vari�veis
   Carta *Pfim, *Pnovo;

   // Aloca��o da primeira carta
	Pnovo = Pinicio = Pfim = AlocaCarta();

   // Se n�o alocou, aborte
   if (!Pnovo) return 0;

	// In�cio da constru��o do baralho
   for (int Nipe=1; Nipe<=4; Nipe++){
      for (int Valor=1; Valor<=13; Valor++){
      	Pnovo->Nipe = Nipe;
         Pnovo->Valor = Valor;
         Pnovo->Posicao = 1;
         Pnovo->Prox = NULL;

         Pnovo = AlocaCarta();
         Pfim->Prox = Pnovo;
         Pfim = Pnovo;
      }
   } // Fim da constru��o do baralho

   // Retorno
   return 1;

} // Fim da fun��o CriaBaralho

//----------------------------------------------------------------------------//

// Fun��o Embaralha: embaralha o baralho
int Embaralha(Carta *&Pinicio) {

	// Declara��o de vari�veis
   int c;
   Carta *P1ant, *P1dep, *P2ant, *P2dep, *Ptemp;

   // Se n�o tem baralho, aborte
   if (!Pinicio) return 0;

   // Inicializando o gerador de n�meros aleat�rios
   randomize();

	// In�cio do embaralhamento do baralho
   for (int j=0; j<52; j++) {

     // Inicializa��o dos ponteiros
     P1ant = P1dep = P2ant = P2dep = Pinicio;

     // Primeira carta aleat�ria e seus ponteiros
     c = (rand()%51);
     for (int i=0; i<=c; i++) {
       P1ant = P1dep;
       P1dep = P1dep->Prox;
     }

     // Segunda carta aleat�ria e seus ponteiros
     c = (rand()%51);
     for (int i=0; i<=c; i++) {
       P2ant = P2dep;
       P2dep = P2dep->Prox;
     }

     // Troca das cartas
     P1ant->Prox = P2dep;
     P2ant->Prox = P1dep;

     Ptemp = P1dep->Prox;
     P1dep->Prox = P2dep->Prox;
     P2dep->Prox = Ptemp;
   }

   // Troca da primeira carta
   P1ant = P1dep = Pinicio;

   c = (rand()%51);
   for (int i=0; i<=c; i++) {
     P1ant = P1dep;
     P1dep = P1dep->Prox;
   }

   P1ant->Prox = Pinicio;
   Ptemp = P1dep->Prox;
   P1dep->Prox = Pinicio->Prox;
   Pinicio->Prox = Ptemp;
   Pinicio = P1dep;

   // Retorno
   return 1;

} // Fim da fun��o Embaralha

//----------------------------------------------------------------------------//

// Fun��o Joga21: conduz o jogo
int Joga21(Carta *Pinicio) {

   // Declara��o de vari�veis:

   // Variaveis que armazenam os pontos do jogador e computador
   int Ponj=0, Ponc=0;

   // Variaveis que verificam se o computador ou se o jogador ainda estao requisitando cartas
   int fjogador=1, fcomputador=1;

   // Cartas para computador e jogador
   Carta *Pj, *Pc;

   // Se n�o tem baralho, aborte
   if (!Pinicio) return 0;

   // Loop que verifica se jogadores solicitam cartas e se alguem estourou,
   // se ambos pararem de pedir carta ou se alguem estourar aborta o loop
	while (((fjogador!=112 && fjogador!=80) || fcomputador!=0) && (Ponc<=21 && Ponj<=21)) {

   	clrscr();

      // Se for teclado [P] ou [p] significa que o jogador n�o quer mais tirar cartas
      if (fjogador!=112 && fjogador!=80) {

	     	// Sorteio da carta do jogador e exibi��o do seu valor
     		Pj = Pinicio;
	     	printf("\n\tSua carta: ");
   	  	switch (Pj->Valor) {
      	 	case 1:
         		printf("As de ");
          		break;
	       	case 11:
   	      	printf("Valete de ");
      	    	break;
       		case 12:
          		printf("Dama de ");
	          	break;
   	    	case 13:
      	    	printf("Rei de ");
         	 	break;
	       	default:
   	       	printf("%i de ", Pj->Valor);
      	    	break;
	     	}
   	  	switch (Pj->Nipe) {
				case 1:
         	 	printf("Copas ");
          		break;
	        	case 2:
   	       	printf("Paus ");
      	    	break;
        		case 3:
          		printf("Ouro ");
	          	break;
   	     	case 4:
      	    	printf("Espada ");
         	 	break;
	     	}

   	  	// Contabiliza��o da pontua��o
     		Ponj += Pj->Valor;

     		// Remo��o do baralho da carta do jogador
	     	Pj = Pj->Prox;
   	  	free(Pinicio);
     		Pinicio = Pj;
      }
      else {
      	printf("\n\tJogador para de pedir carta");
      }

      // Se o computador tem menos de 15 pontos, tiramos carta para computador
		if (Ponc<=15){

			// Sorteio da carta do computador
	     	Pc = Pinicio;

     		// Contabiliza��o da pontua��o
     		Ponc += Pc->Valor;

     		// Remo��o do baralho da carta do computador
     		Pc = Pc->Prox;
     		free(Pinicio);
     		Pinicio = Pc;
     		printf("\n\tComputador: pede carta");
     		fcomputador=1;
   	}
      else {
			printf("\n\tComputador: para de pedir cartas");
      	fcomputador=0;
      }

      // Mostra pontua��o parcial da partida
      printf("\n\n\t  Sua pontuacao: %d", Ponj);

      // Se ninguem estourar e se o jogador ainda estiver pedindo cartas o jogador
      // ainda pode escolher se quer ou n�o mais cartas
      if (fjogador!=112 && fjogador!=80 && Ponc<=21 && Ponj<=21) {
	      printf("\n\n\n\tJogador: tecle [P] para parar de tirar cartas: ");
  			fjogador = getch();
			if (fcomputador != 0){
         	printf("\n\n\tComputador solicitara carta.\n\t[Pressione qualquer tecla para continuar...]\n");
            getch();
         }
         else {
	         printf("\n\n\tComputador nao solicitara carta.\n\t[Pressione qualquer tecla para continuar...]\n");
            getch();
         }
      }

   } // Fim do loop

   // Exibe resultado e pontua��o final
   printf("\n\n\n\tRESULTADO FINAL:");
   if (Ponc>21 && Ponj<=21){
   	printf("\n\n\t  Computador estourou e jogador venceu.");
   }
   else if (Ponj>21 && Ponc<=21){
   	printf("\n\n\t  Jogador estourou e computador venceu.");
   }
   else if (Ponj>21 && Ponc>21){
	   printf("\n\n\t  Jogador e computador estouraram. Jogo termina empatado.");
   }
   else if (Ponj>Ponc){
		printf("\n\n\t  Jogador fez mais pontos, portanto venceu.");
   }
   else if (Ponj<Ponc){
	   printf("\n\n\t  Computador fez mais pontos, portanto venceu.");
   }
   else if (Ponj==Ponc){
	   printf("\n\n\t  Jogador e computador empataram.");
   }

   printf("\n\n\tPontuacao final:\n");
   printf("\n\t  Sua pontuacao final: %d", Ponj);
   printf("\n\t  Pontuacao final do computador: %d\n\n\n\t[Pressione qualquer tecla para continuar...]\n", Ponc);
   getch();

   // Retorna
   return 1;

} // Fim da fun��o Joga21
