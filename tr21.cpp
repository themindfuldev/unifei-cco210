/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 21 - Entrega: 18/11/2004                                          *
*   Objetivos: Lista de exercício sobre árvores binárias                       *
*                                                                              *
*   Nome: Heron Yugo Inouye                     Matrícula: 11877               *
*   Nome: Tiago Romero Garcia                   Matrícula: 12643               *
*   Ciência da Computação - Universidade Federal de Itajubá                    *
*                                                                              *
*******************************************************************************/

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------------//

// Definição de constantes
#define MAX 20

//----------------------------------------------------------------------------//

// Declaração de estruturas
typedef struct NO
{
	NO *LL, *RL;
   char nome[20];
   long endereco;
} NO;

typedef struct PILHA
{
	int topo;
   NO *pilha[MAX];
} PILHA;

typedef struct FILA
{
   NO *fila[MAX];
   int base, limite, p, u;
} FILA;

//----------------------------------------------------------------------------//

// Protótipos de funções
NO *rBuscaNO(NO *R, char nome[20]);
int  InsereNaFila(FILA &Fila, NO *P);
NO *rInsereNO(NO *Raiz, NO *R, char nome[20], long endereco);
NO *sInsereNO(NO *&Raiz, char nome[20], long endereco);
int  Menu(void);
int sPercursoEmLargura(NO *R);
int rPercursoOrdemSimetrica(NO *R);
int sPercursoOrdemSimetrica(NO *R);
int rPercursoPosOrdem(NO *R);
int rPercursoPreOrdem(NO *R);
int sPercursoPreOrdem(NO *R);
NO  *Pop(PILHA &Pilha);
int  Push(PILHA &Pilha, NO *P);
NO  *ReservaNO(void);
NO  *RemoveDaFila(FILA &Fila);
int  Sucessor(FILA Fila, int px);

//----------------------------------------------------------------------------//

// Função main: Estrutura do programa
void main(void)
{
	// Declaração de variáveis
   char nome[20];
   int  i, op, qtde, ret;
   long endereco;
	NO *Raiz=NULL, *Res;

   do
   {
   	op = Menu();
   	switch(op)
      {
      	case 1:  // Insere um nó numa árvore binária usando método seqüencial
         			do
                  {
							printf("\tDigite o numero de elementos a serem inseridos: ");
							scanf("%d", &qtde);
                     if (qtde <= 0)
                     {
		   					printf("\n\t\aERRO: Digite um numero positivo!\n\t[Pressione qualquer tecla para continuar...]\n\n\n");
      		            getch();
                     } // Fim de if
                  } while (qtde <= 0);
						for(i=0; i<qtde; i++)
						{
                  	do
                     {
								printf("\n\t  Digite o nome do %d elemento: ", i+1);
								scanf(" %[^\n]", &nome);
                        if (strlen(nome)>20)
                        {
                        	printf("\n\t\aERRO: Digite um nome com menos que 20 caracteres!\n\t[Pressione qualquer tecla para continuar...]\n\n");
                           getch();
                        } // Fim de if
                     } while (strlen(nome)>20);
							printf("\t  Digite o endereco do %d elemento: ",i+1);
							scanf("%ld", &endereco);
							Raiz = sInsereNO(Raiz, nome, endereco);
							if (!Raiz)
                     {
		   					printf("\n\t\aERRO: O no nao foi alocado com sucesso!\n\t[Pressione qualquer tecla para continuar...]\n");
      		            getch();
                     } // Fim de if
						} // Fim de for
                  break;

      	case 2:  // Insere um nó numa árvore binária usando método recursivo
         			do
                  {
							printf("\tDigite o numero de elementos a serem inseridos: ");
							scanf("%d", &qtde);
                     if (qtde <= 0)
                     {
		   					printf("\n\t\aERRO: Digite um numero positivo!\n\t[Pressione qualquer tecla para continuar...]\n\n\n");
      		            getch();
                     } // Fim de if
                  } while (qtde <= 0);
						for(i=0; i<qtde; i++)
						{
                  	do
                     {
								printf("\n\t  Digite o nome do %d elemento: ", i+1);
								scanf(" %[^\n]", &nome);
                        if (strlen(nome)>20)
                        {
                        	printf("\n\t\aERRO: Digite um nome com menos que 20 caracteres!\n\t[Pressione qualquer tecla para continuar...]\n\n");
                           getch();
                        } // Fim de if
                     } while (strlen(nome)>20);
                     printf("\t  Digite o endereco do %d elemento: ", i+1);
							scanf("%ld", &endereco);
                     Res = rInsereNO(Raiz, Raiz, nome, endereco);
							if (!Res)
                     {
		   					printf("\n\t\aERRO: O no nao foi alocado com sucesso!\n\t[Pressione qualquer tecla para continuar...]\n");
      		            getch();
                     } // Fim de if
							if (!Raiz) Raiz = Res;
						} // Fim de for
                  break;

      	case 3:  // Busca um nó na árvore usando método recursivo
         			if (!Raiz) printf("\t\aERRO: Arvore vazia!");
                  else
                  {
							printf("\tDigite um nome para pesquisa: ");
							scanf(" %[^\n]", &nome);
							Res = rBuscaNO(Raiz, nome);
							if (!Res)
								printf("\n\tO dado NAO consta na arvore!!!");
							else
								printf("\n\tO dado consta na arvore:\n\n\t  Nome: %s\n\t  Endereco: %ld\n\n", Res->nome, Res->endereco);
                  } // Fim de if
                  printf("\n\t[Pressione qualquer tecla para continuar...]\n");
                  getch();
                  break;

      	case 4:  // Lista os nós por pré-ordem usando método recursivo
         			if (Raiz) rPercursoPreOrdem(Raiz);
                  else printf("\t\aERRO: Arvore vazia!");
                  printf("\n\t[Pressione qualquer tecla para continuar...]\n");
						getch();
                  break;

      	case 5:  // Lista os nós por pré-ordem usando método seqüencial
						if (Raiz)
                  {
                  	ret = sPercursoPreOrdem(Raiz);
                     if (ret == -1) printf("\n\n\t\aERRO: Overflow!");
                     if (ret == -2) printf("\n\n\t\aERRO: Underflow!");
                  }
                  else printf("\t\aERRO: Arvore vazia!");
                  printf("\n\t[Pressione qualquer tecla para continuar...]\n");
						getch();
                  break;

      	case 6:  // Lista os nós por pós-ordem usando método recursivo
         			if (Raiz) rPercursoPosOrdem(Raiz);
                  else printf("\t\aERRO: Arvore vazia!");
                  printf("\n\t[Pressione qualquer tecla para continuar...]\n");
						getch();
                  break;

      	case 7:  // Lista os nós por ordem simétrica usando método recursivo
         			if (Raiz) rPercursoOrdemSimetrica(Raiz);
                  else printf("\t\aERRO: Arvore vazia!");
                  printf("\n\t[Pressione qualquer tecla para continuar...]\n");
						getch();
                  break;

      	case 8:  // Lista os nós por ordem simétrica usando método seqüencial
						if (Raiz)
                  {
                  	ret = sPercursoOrdemSimetrica(Raiz);
                     if (ret == -1) printf("\n\n\t\aERRO: Overflow!");
                     if (ret == -2) printf("\n\n\t\aERRO: Underflow!");
                  }
                  else printf("\t\aERRO: Arvore vazia!");
                  printf("\n\t[Pressione qualquer tecla para continuar...]\n");
						getch();
                  break;

      	case 9:  // Lista os nós por percurso em largura usando método seqüencial
         			if (Raiz) sPercursoEmLargura(Raiz);
                  else printf("\t\aERRO: Arvore vazia!");
                  printf("\n\t[Pressione qualquer tecla para continuar...]\n");
						getch();
                  break;

         case 0:  // Sair
   					printf("\tFinalizando...\n\t[Pressione qualquer tecla para continuar...]\n");
                  getch();
         			break;

         default: // Opção inválida
   					printf("\a\tOpcao invalida!\n\t[Pressione qualquer tecla para continuar...]\n");
                  getch();
         			break;
      } // Fim de switch
   } while(op);

} // Fim de main

//----------------------------------------------------------------------------//

// Função BuscaNO: Busca um nó na árvore usando método recursivo
NO *rBuscaNO(NO *R, char nome[20])
{
	// Declaração de variáveis
   NO *Pesq;

	// Verifica se arvore está vazia
   if (!R) return 0;

   // Verificando se encontrou a informação
   if (strcmp(R->nome, nome)==0)
		return R;

   // Pesquisa pelas sub-árvores da esquerda e direita
   if (strcmp(nome, R->nome)<0)
   	Pesq = rBuscaNO(R->LL, nome);
   if (strcmp(nome, R->nome)>0)
   	Pesq = rBuscaNO(R->RL, nome);

   return Pesq;

} // Fim de BuscaNO

//----------------------------------------------------------------------------//

// Função BuscaSubArvore: Busca a i-ésima sub-árvore de uma árvore
NO *BuscaSubArvore(NO *R, int i)
{
	// Declaração de variáveis
   NO *P=NULL;

	switch(i)
   {
   	case 0:  // Sub-árvore esquerda
      			P = R->LL;
               break;

      case 1:  // Sub-arvore direita
      			P = R->RL;
               break;
   } // Fim de switch

   return P;

} // Fim de BuscaSubArvore

//----------------------------------------------------------------------------//

// Função InsereNaFila: Insere um valor na fila
int InsereNaFila(FILA &Fila, NO *P)
{
  // Verificando Overflow
  if (Sucessor(Fila, Fila.p) == Fila.u) return -1;

  // Inserindo um elemento
  Fila.fila[Fila.p] = P;
  Fila.p = Sucessor(Fila, Fila.p);
  return 1;

} // Fim de InsereNaFila

//----------------------------------------------------------------------------//

// Função rInsereNO: Insere um nó numa árvore binária usando método recursivo
NO *rInsereNO(NO *Raiz, NO *R, char nome[20], long endereco)
{
	// Se o ponto de inserção for localizado, insere um novo nó
	if (!R)
   {
   	// Reservando memória para um novo nó
   	R = ReservaNO();
      if (!R) return NULL; // Nó não alocado com sucesso

		// Inserindo informação no nó
		strcpy(R->nome, nome);
      R->endereco = endereco;
      R->LL = R->RL = NULL;

      if (Raiz)
      {
      	if (strcmp(nome, Raiz->nome)<0)
         	Raiz->LL = R;
      	else
         	Raiz->RL = R;
      } // Fim de if
      return R;

   } // Fim de if

	// Continua a busca pelo ponto de inserção (nó folha)
   if (strcmp(nome, R->nome)<0)
   	rInsereNO(R, R->LL, nome, endereco);
   else
   	rInsereNO(R, R->RL, nome, endereco);

   return R;

} // Fim de rInsereNO

//----------------------------------------------------------------------------//

// Função sInsereNO: Insere um nó numa árvore binária usando método seqüencial
NO *sInsereNO(NO *&Raiz, char nome[20], long endereco)
{
	// Declaração de variáveis
	NO *Px, *P, *Q;

   // Reservando memória para um novo nó
   Px = ReservaNO();
   if(!Px) return 0;

	// Inserindo informação no nó
	strcpy(Px->nome, nome);
   Px->endereco = endereco;
   Px->LL = Px->RL = NULL;

   // Inserindo nó se a arvore for vazia
   if(!Raiz)
   {
   	Raiz = Px;
      return Raiz;
   } // Fim de if

   // Inserindo se a árvore não for vazia
   Q = Raiz;
   while(Q)
   {
   	P = Q;
      if(strcmp(nome, P->nome)<0)
      	Q = P->LL;
      else
      	Q = P->RL;
   } // Fim de if

   // Insere como novo nó folha e finaliza
   if (strcmp(nome, P->nome)<0)
   	P->LL = Px;
   else
   	P->RL = Px;

   return Raiz;

} // Fim de sInsereNO

//----------------------------------------------------------------------------//

// Função Menu: Imprime o menu
int Menu(void)
{
	int op;

	clrscr();
	printf("\n     21o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
	printf("\n     Nome: Heron Yugo Inouye    -  Matricula: 11877  -  CCO 2003");
	printf("\n     Nome: Tiago Romero Garcia  -  Matricula: 12643  -  CCO 2004");
   printf("\n\n\n\tMenu de Opcoes:");
   printf("\n\t  1. Criar uma arvore binaria usando metodo sequencial");
   printf("\n\t  2. Criar uma arvore binaria usando metodo recursivo");
   printf("\n\t  3. Buscar um no na arvore usando metodo recursivo");
   printf("\n\t  4. Listar os nos por pre-ordem usando metodo recursivo");
   printf("\n\t  5. Listar os nos por pre-ordem usando metodo sequencial");
   printf("\n\t  6. Listar os nos por pos-ordem usando metodo recursivo");
   printf("\n\t  7. Listar os nos por ordem simetrica usando metodo recursivo");
   printf("\n\t  8. Listar os nos por ordem simetrica usando metodo sequencial");
   printf("\n\t  9. Lista os nos por percurso em largura usando metodo sequencial");
   printf("\n\t  0. Sair");
   printf("\n\n\tDigite a opcao desejada: ");
   scanf("%d", &op);
   printf("\n\n");

   return op;

} // Fim de Menu

//----------------------------------------------------------------------------//

// Função sPercursoEmLargura: Lista os nós por percurso em largura usando método seqüencial
int sPercursoEmLargura(NO *R)
{
	// Declaração de variáveis
   FILA Fila;
   NO *T;

   // Inicialização de variáveis
	Fila.base = Fila.p = Fila.u = 0;
	Fila.limite = MAX-1;

   InsereNaFila(Fila, R);
   while (Fila.p != Fila.u)
   {
   	R = RemoveDaFila(Fila);
	   printf("\tNome: %s\n", R->nome);
   	printf("\tEndereco: %ld\n\n", R->endereco);
      for (int i=0; i<2; i++)
      {
      	T = BuscaSubArvore(R, i);
         if (T) InsereNaFila(Fila, T);
      } // Fim de for

   } // Fim de while

	return 1;

} // Fim de sPercursoEmLargura

//----------------------------------------------------------------------------//

// Função rPercursoOrdemSimetrica: Lista os nós por ordem simétrica usando método recursivo
int rPercursoOrdemSimetrica(NO *R)
{
	// Verifica se a árvore está vazia
   if(!R) return 0;

   // Caminha na sub-árvore esquerda
   rPercursoOrdemSimetrica(R->LL);

   // Visita o nó
   printf("\tNome: %s\n", R->nome);
   printf("\tEndereco: %ld\n\n", R->endereco);

   // Caminha na sub-árvore direita
   rPercursoOrdemSimetrica(R->RL);

   return 1;

} // Fim de rPercursoOrdemSimetrica

//----------------------------------------------------------------------------//

// Função sPercursoOrdemSimetrica: Lista os nós por ordem simétrica usando método seqüencial
int sPercursoOrdemSimetrica(NO *R)
{
	// Declaração de variáveis
   bool v;
   NO *P, *Q;
   PILHA Pilha;

   // Inicialização de variáveis
   Pilha.topo = -1;
   Q = R;
   v = 1;

   while (v)
   {
   	while (Q)
      {
      	P = Q;
         if (Push(Pilha, P) == -1) return -1;
         Q = P->LL;
      } // Fim de while
      P = Pop(Pilha);
	   printf("\tNome: %s\n", P->nome);
	   printf("\tEndereco: %ld\n\n", P->endereco);

      while ((P->RL == 0)&&(Pilha.topo > -1))
      {
      	P = Pop(Pilha);
     		if (P == NULL) return -2;
		   printf("\tNome: %s\n", P->nome);
		   printf("\tEndereco: %ld\n\n", P->endereco);
      } // Fim de while

		if ((P->RL == 0)&&(Pilha.topo == -1)) v = 0;

      Q = P->RL;
   } // Fim de while

   return 1;

} // Fim de sPercursoOrdemSimetrica

//----------------------------------------------------------------------------//

// Função rPercursoPosOrdem: Lista os nós por pós-ordem usando método recursivo
int rPercursoPosOrdem(NO *R)
{
	// Verifica se a árvore está vazia
   if(!R) return 0;

   // Caminha nas sub-árvores esquerda e direita
   rPercursoPosOrdem(R->LL);
   rPercursoPosOrdem(R->RL);

   // Visita o nó
   printf("\tNome: %s\n", R->nome);
   printf("\tEndereco: %ld\n\n", R->endereco);

   return 1;

} // Fim de rPercursoPosOrdem

//----------------------------------------------------------------------------//

// Função rPercursoPreOrdem: Lista os nós por pré-ordem usando método recursivo
int rPercursoPreOrdem(NO *R)
{
	// Verifica se a árvore está vazia
   if(!R) return 0;

   // Visita o nó
   printf("\tNome: %s\n", R->nome);
   printf("\tEndereco: %ld\n\n", R->endereco);

   // Caminha nas sub-árvores esquerda e direita
   rPercursoPreOrdem(R->LL);
   rPercursoPreOrdem(R->RL);

   return 1;

} // Fim de rPercursoPreOrdem

//----------------------------------------------------------------------------//

// Função sPercursoPreOrdem: Lista os nós por pré-ordem usando método seqüencial
int sPercursoPreOrdem(NO *R)
{
	// Declaração de variáveis
   bool v;
	NO *P, *Q;
   PILHA Pilha;

	// Inicialização de variáveis
   Pilha.topo = -1;
   v = 1;
   Q = R;

   while (v)
   {
   	while (Q)
      {
      	P = Q;
		   printf("\tNome: %s\n", P->nome);
		   printf("\tEndereco: %ld\n\n", P->endereco);
         if (Push(Pilha, P) == -1) return -1;
         Q = P->LL;
      } // Fim de while
      P = Pop(Pilha);
     	while ((P->RL == 0)&&(Pilha.topo > -1))
     	{
     		P = Pop(Pilha);
     		if (P == NULL) return -2;
     	} // Fim de while

		if ((P->RL == 0)&&(Pilha.topo == -1)) v = 0;
    	Q = P->RL;
   } // Fim de while

   return 1;

} // Fim de sPrecursoPreOrdem

//----------------------------------------------------------------------------//

// Função Push: Empilha um nó numa pilha seqüencial
int Push(PILHA &Pilha, NO *P)
{
	// Verificando overflow
   if (Pilha.topo >= MAX-1) return -1;

   Pilha.topo++;
   Pilha.pilha[Pilha.topo] = P;

   return 1;

} // Fim de Push

//----------------------------------------------------------------------------//

// Função Pop: Desempilha um nó de uma pilha seqüencial
NO *Pop(PILHA &Pilha)
{
	// Declaração de variáveis
   NO *P;

	// Verificando underflow
   if (Pilha.topo <= -1) return NULL;

   P = Pilha.pilha[Pilha.topo];
   Pilha.topo--;

   return P;

} // Fim de Pop

//----------------------------------------------------------------------------//

// Função RemoveDaFila: Remove um valor da fila
NO *RemoveDaFila(FILA &Fila)
{
	// Variáveis locais
	NO *P;

	// Verificando Underflow
	if (Fila.p == Fila.u) return NULL;

	// Retirando o elemento
	P = Fila.fila[Fila.u];
	Fila.u = Sucessor(Fila, Fila.u);
	return P;

} // Fim de RemoveDaFila

//----------------------------------------------------------------------------//

// Função ReservaNO: Reserva um nó na memória
NO *ReservaNO(void)
{
	NO *P;
   P = (NO *) calloc (1, sizeof(NO));
   return P;

} // Fim de ReservaNO

//----------------------------------------------------------------------------//

// Função Sucessor: Circula a lista
int Sucessor(FILA Fila, int px)
{
	if (px >= Fila.limite) return Fila.base;
	return ++px;

} // Fim de Sucessor

