/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Projeto final de curso - Entrega: 10/12/2004                               *
*   Objetivos: Criar um sistema de arquivo seq�encial indexado com chave       *
*					prim�ria �nica armazenada em um arquivo de chaves, organizado   *
*              na forma de uma �rvore de grau 2 (bin�ria), utilizando o        *
*              m�todo Ordem Sim�trica                                          *
*                                                                              *
*   Nome: Heron Yugo Inouye                     Matr�cula: 11877               *
*   Nome: Tiago Romero Garcia                   Matr�cula: 12643               *
*   Ci�ncia da Computa��o - Universidade Federal de Itajub�                    *
*                                                                              *
*******************************************************************************/

// Declara��o das bibliotecas
#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//----------------------------------------------------------------------------//

// Defini��o de constantes
#define MAX 50

//----------------------------------------------------------------------------//

// Declara��o de estruturas
typedef struct ARVORE
{
	ARVORE *LL, *RL;
   int  Matricula;
   long EnderecoRegistro;
} ARVORE;

typedef struct DADOS
{
	int Matricula;
	char Nome[20], Telefone[10];
} DADOS;

typedef struct FILA
{
   ARVORE *fila[MAX];
   int base, limite, p, u;
} FILA;

typedef struct PILHA
{
	ARVORE *Pilha[MAX];
   int Topo;
} PILHA;

//----------------------------------------------------------------------------//

// Prot�tipos das fun��es
void    ArbVal(int Ls, int Li, int *V,int *V2, int *vetNovo, int *vet, int NReg);
ARVORE *BalanArvore(ARVORE *Raiz);
void    BuscaInfo(ARVORE *Raiz, int mat);
ARVORE *BuscaNo(ARVORE *Raiz, int mat);
ARVORE *BuscaSubArvore(ARVORE *R, int i);
ARVORE *CarregaArvore(ARVORE *Raiz);
void    CompactaArquivo(ARVORE *Raiz);
ARVORE *CriaNovaArvore(ARVORE *Raiz1, ARVORE *Raiz2, int *V2);
int     InsereNaFila(FILA &Fila, ARVORE *P);
ARVORE *InsereNovoRegistro(ARVORE *Raiz);
int     LeReg(void);
void    LiberaMem(ARVORE *Raiz);
void    OrdemSimetrica(ARVORE *Raiz, int *V);
ARVORE *Pop(PILHA *PilhaA);
void    Push(PILHA *PilhaA, ARVORE *P);
ARVORE *Remove(ARVORE *Raiz, int mat);
ARVORE *RemoveDaFila(FILA &Fila);
ARVORE *RemoveNoArvore(ARVORE *R, int x);
ARVORE *ReservaNo(void);
int     Menu(void);
void    SalvaArvore(ARVORE *Raiz);
void    SalvaReg(DADOS *Info);
int     Sucessor(FILA Fila, int px);

//----------------------------------------------------------------------------//

// Programa main
void main(void)
{
   // Defini��o de vari�veis
	ARVORE *Raiz = NULL;
   int op;
   int mat;

	// Carregando arquivo da arvore
	Raiz = CarregaArvore(Raiz);

	// Programa
	do
   {
		op = Menu();
   	switch(op)
      {
         case 1: // Insere um registro
            Raiz = InsereNovoRegistro(Raiz);
            printf("\t[Pressione qualquer tecla para continuar...]\n");
            getch();
            break;

         case 2: // Remove um registro
            if (!Raiz)
            {
               printf("\t\aERRO: Arquivo de chaves inexistente.\n");
	            printf("\t[Pressione qualquer tecla para continuar...]\n");
               getch();
            	break;
            } // Fim de if
				printf("\tDigite a matricula: ");
				scanf("%d", &mat);
            Raiz = Remove(Raiz, mat);
            printf("\t[Pressione qualquer tecla para continuar...]\n");
            getch();
            break;

         case 3: // Busca de um registro
            if (!Raiz)
            {
               printf("\t\aERRO: Arquivo de chaves inexistente.\n");
	            printf("\t[Pressione qualquer tecla para continuar...]\n");
               getch();
               break;
            } // Fim de if
				printf("\tDigite a matricula: ");
				scanf("%d", &mat);
				BuscaInfo(Raiz, mat);
            printf("\t[Pressione qualquer tecla para continuar...]\n");
				getch();
            break;

         case 4: // Compacta��o do arquivo
            if (!Raiz)
            {
               printf("\t\aERRO: Arquivo de chaves inexistente.\n");
               printf("\t[Pressione qualquer tecla para continuar...]\n");
               getch();
               break;
            } // Fim de if
            CompactaArquivo(Raiz);
  	         Raiz = BalanArvore(Raiz);
            printf("\tArquivo de chaves balanceado e arquivo de dados compactado com sucesso.\n");
            printf("\t[Pressione qualquer tecla para continuar...]\n");
            getch();
            break;

         case 0: // Sair
         	if (Raiz)
            {
					SalvaArvore(Raiz);
            	LiberaMem(Raiz);
            	printf("\tArquivo de chaves salvo em INDEX.DAT.\n\tMemoria liberada com sucesso.\n\n");
            } // Fim de if
            else
            	printf("\tO arquivo de chaves esta vazio, portanto INDEX.DAT foi removido.\n\n");
            printf("\tFinalizando o programa...\n\t[Pressione qualquer tecla para continuar...]\n");
            getch();
            break;

         default: // Op��o inv�lida
            printf("\t\aERRO: Opcao invalida...\n");
            printf("\t[Pressione qualquer tecla para continuar...]\n");
            getch();
            break;
   	} // Fim de switch
	} while(op); // Fim de do while

} // Fim de main

//----------------------------------------------------------------------------//

// Fun��o ArbVal: Balanceia uma �rvore
void ArbVal(int Ls, int Li, int *V,int *V2, int *vetNovo, int *vet, int NReg)
{
   // Defini��o de vari�veis
	int Meio;
   static j = 0;

   if (NReg == Ls) j = 0;
   Meio = (Ls+Li)/2;
   if (Li > Ls) return;
   V2 = vetNovo;
   V = vet;
   V2 += j;
   V += (Meio-1);
   *V2 = *V;
   j++;
   ArbVal(Meio-1, Li, V, V2, vetNovo, vet, -1);
   ArbVal(Ls, Meio+1, V, V2, vetNovo, vet, -1);
} // Fim de ArbVal

//----------------------------------------------------------------------------//

// Fun��o BalanArvore: Balanceia a �rvore
ARVORE *BalanArvore(ARVORE *Raiz)
{
   int *vet, *V, *V2, *vetNovo;
   int NReg, i;
   ARVORE *Raiz2 = NULL;

   NReg = LeReg();

   vet = (int *) calloc (NReg, sizeof(int));
   vetNovo = (int *) calloc (NReg, sizeof(int));
   if ((!vet)||(!vetNovo))
   {
   	printf("\n\t\aERRO: Nao foi possivel alocar o vetor dos registros.\n");
      return NULL;
   }
   V = vet;
	OrdemSimetrica(Raiz,V);
	V = vet;
   V2 = vetNovo;
   ArbVal(NReg, 1, V, V2, vetNovo, vet, NReg);
	V2 = vetNovo;
   for(i=1; i<=NReg; i++)
   {
	   Raiz2 = CriaNovaArvore(Raiz, Raiz2, V2);
      V2++;
   }

	// Libera a memoria da �rvore antiga e dos vetores alocados dinamicamente
  	LiberaMem(Raiz);
   free(vetNovo);
	free(vet);
   return Raiz2;
} // Fim de BalanArvore

//----------------------------------------------------------------------------//

// Fun��o BuscaInfo: Verifica se um dado est� no arquivo de dados
void BuscaInfo(ARVORE *Raiz, int mat)
{
	// Defini��o de vari�veis locais
	FILE *Pf;
	DADOS Dados;
   ARVORE *Paux;

   // Busca o ponteiro que aponta para n� da arvore
   Paux = BuscaNo(Raiz, mat);
   if (!Paux)
   {
      printf("\n\tDado nao encontrado.\n");
      return;
   }

	// Busca no arquivo
	Pf = fopen("AGENDA.DAT", "rb+");
	if (Pf == NULL)
   {
		printf("\n\t\aERRO: Arquivos de dados nao encontrado.\n");
	  	return;
   } // Fim de if
   fseek(Pf, Paux->EnderecoRegistro, 0);
	fread(&Dados, sizeof(DADOS), 1, Pf);
	fclose(Pf);
   printf("\n\tDado encontrado.");
   printf("\n\t  Matricula: %d", Dados.Matricula);
   printf("\n\t  Nome: %s", Dados.Nome);
   printf("\n\t  Telefone: %s\n", Dados.Telefone);
} // Fim de BuscaInfo

//----------------------------------------------------------------------------//

// Fun��o BuscaNO: Busca um determinado n� na �rvore
ARVORE *BuscaNo(ARVORE *Raiz, int mat)
{
	// Defini��o de vari�veis
   ARVORE *Paux;

	// Verifica se a �rvore est� vazia
   if (!Raiz) return NULL;

   // Verifica se encontrou o n� com a informa��o dado
   if (mat == Raiz->Matricula) return Raiz;

  	//Pesquisar Na Sub-Arvore Esquerda e Direita
	if (mat <= Raiz->Matricula) Paux = BuscaNo(Raiz->LL, mat);
  	if (mat > Raiz->Matricula) Paux = BuscaNo(Raiz->RL, mat);
	return Paux;
} // Fim de BuscaNO

//----------------------------------------------------------------------------//

// Fun��o BuscaSubArvore: Busca a i-�sima sub-�rvore de uma �rvore
ARVORE *BuscaSubArvore(ARVORE *R, int i)
{
	// Declara��o de vari�veis
   ARVORE *P=NULL;

	switch(i)
   {
   	case 0:  // Sub-�rvore esquerda
      			P = R->LL;
               break;

      case 1:  // Sub-arvore direita
      			P = R->RL;
               break;
   } // Fim de switch

   return P;

} // Fim de BuscaSubArvore

//----------------------------------------------------------------------------//

// Fun��o CarregaArvore: Carrega arquivo de chaves do arquivo INDEX.DAT
ARVORE *CarregaArvore(ARVORE *Raiz)
{
	// Defini��o de vari�veis
	FILE *Pf;
   ARVORE *Px, *p, *q;

   Px = ReservaNo();
	Pf = fopen("INDEX.DAT", "rb");
	if (!Pf)
   {
	  	clrscr();
   	printf("\n\tStatus da recuperacao dos arquivos:\n");
      printf("\n\t\aALERTA: Nao foi possivel abrir o arquivo de chaves INDEX.DAT.\n");
      getch();
		return NULL;
   }

   // Leitura do arquivo
   while (fread(Px, sizeof(ARVORE), 1, Pf)!=0)
   {
		Px->RL = Px->LL = NULL;

      // Monta a �rvore
      if (Raiz == NULL)
		   Raiz = Px;
      else
      {
			q = Raiz;
			while(q != NULL)
         {
				p = q;
				if (Px->Matricula < q->Matricula) q = p->LL;
				else q = p->RL;
			} // Fim de while

   		// Insere como um Novo NO e Finaliza
			if (Px->Matricula < p->Matricula) p->LL = Px;
			else p->RL = Px;
		} // Fim de if
      Px = ReservaNo();
   } // Fim de while
  	clrscr();
  	printf("\n\tStatus da recuperacao dos arquivos:\n");
	if (!Px)
   {
      printf("\n\tALERTA: O arquivo de chaves INDEX.DAT esta vazio.\n");
      getch();
		return NULL;
   } // Fim de if
   else
   {
      printf("\n\tO arquivo de chaves foi carregado de INDEX.DAT.\n");
      getch();
   } // Fim de else
   free(Px);
	fclose(Pf);
	return Raiz;
} // Fim de CarregaArvore

//----------------------------------------------------------------------------//

// Fun��o CompactaArquivo: Remove os registros do arquivo de dados que nao
// 								possuem chaves associadas no arquivo de chaves

void CompactaArquivo(ARVORE *Raiz)
{
   // Defini��o de vari�veis
   FILE *P1, *P2;
   DADOS Info;
   ARVORE *q, *p;
	PILHA PilhaA;
	int VLogico, valor = 0;

	// Inicializa��o das vari�veis
	q = Raiz;
	VLogico = 1;
	PilhaA.Topo = 0;

   P1 = fopen("AGENDA.DAT", "rb");
	if (P1 == NULL)
		return;

	P2 = fopen("NOVO.DAT", "wb+");
	if (P2 == NULL)
   {
		fclose(P1);
      return;
   } // Fim de if

   while (VLogico == 1)
   {
      // Varrendo a SubArvore a Esquerda
      while(q != NULL)
      {
         p = q;
			fseek(P1, p->EnderecoRegistro, 0);
			fread(&Info, sizeof(DADOS), 1, P1);
         fwrite(&Info, sizeof(DADOS), 1, P2);
         p->EnderecoRegistro = valor * sizeof(DADOS);
         valor++;
         Push(&PilhaA, p);
         q = p->LL;
      } // Fim de while
      q = Pop(&PilhaA);

      if ((PilhaA.Topo == 0) && (q->RL == NULL)) VLogico = 0;
      q = q->RL;
   } // Fim de while

   fclose(P1);
   fclose(P2);

   // Remove o arquivo original, com lixo
   if (remove("AGENDA.DAT") != 0)
   {
   	printf("\n\tNao foi possivel remover o arquivo AGENDA.DAT.\n");
      getch();
      return;
   } // Fim de if

   // Transforma o arquivo NOVO.DAT, no arquivo original
   if (rename("NOVO.DAT", "AGENDA.DAT") != 0)
   {
		printf("\n\tNao foi possivel renomear o arquivo NOVO.DAT.\n");
      getch();
      return;
   } // Fim de if
} // Fim de CompactaArquivo

//----------------------------------------------------------------------------//

// Fun��o CriaNovaArvore: cria uma arvore balanceada
ARVORE *CriaNovaArvore(ARVORE *Raiz1, ARVORE *Raiz2, int *V2)
{
   // Defini��o de vari�veis
   ARVORE *Px, *p, *q, *Paux;

	// Colocando o dado na arvore
   Px = ReservaNo();
   if(!Px) return NULL;
   Paux = BuscaNo(Raiz1,*V2);
   Px->EnderecoRegistro = Paux->EnderecoRegistro;
   Px->Matricula = *V2;

   // Insere o Primeiro NO
	if(!Raiz2)
   {
		Raiz2 = Px;
		return Raiz2;
	} // Fim de if

   //Insere um NO na Arvore Nao Vazia
	q = Raiz2;
	while(q != NULL)
   {
   	p = q;
		if(*V2 < q->Matricula) q = p->LL;
		else q = p->RL;
   } // Fim de while

   // Insere como um novo n� e finaliza
   if (*V2 < p->Matricula) p->LL = Px;
   else p->RL = Px;

   return Raiz2;
} // Fim de CriaNovaArvore

//----------------------------------------------------------------------------//

// Fun��o InsereNaFila: Insere um valor na fila
int InsereNaFila(FILA &Fila, ARVORE *P)
{
  // Verificando Overflow
  if (Sucessor(Fila, Fila.p) == Fila.u) return -1;

  // Inserindo um elemento
  Fila.fila[Fila.p] = P;
  Fila.p = Sucessor(Fila, Fila.p);
  return 1;

} // Fim de InsereNaFila

//----------------------------------------------------------------------------//

// Fun��o InsereNovoRegistro: Insere um novo registro
ARVORE *InsereNovoRegistro(ARVORE *Raiz)
{
   // Defini��o de vari�veis
   DADOS *Info;
   ARVORE *Px, *p, *q, *Paux;
   int nReg;

   // Reservando mem�ria dinamicamente do tipo DADOS
   Info = (DADOS *) calloc (1, sizeof(DADOS));

   // Lendo a chave primaria - Matricula
   printf("\n\tDigite a Matricula: ");
   scanf("%d", &Info->Matricula);

   // Verificando se j� existe Matricula
   Paux = BuscaNo(Raiz, Info->Matricula);
   if (Paux)
   {
		printf("\n\t\aERRO: A matricula %d ja esta armazenada.\n", Info->Matricula);
      return Raiz;
   } // Fim de if

	// Lendo os outros dados
   printf("\tDigite o Nome: ");
   scanf(" %[^\n]", Info->Nome);
   printf("\tDigite o Telefone: ");
   scanf(" %[^\n]", Info->Telefone);

   // Verificando a quantidade de registros
   nReg = LeReg();

   // Salvando no arquivo AGENDA.DAT
   SalvaReg(Info);

	// Colocando o dado na arvore
   Px = ReservaNo();
   if (!Px) return NULL;
   Px->EnderecoRegistro = nReg * sizeof(DADOS);
   Px->Matricula = Info->Matricula;

   // Insere o Primeiro NO
	if (!Raiz)
   {
		Raiz = Px;
		return Raiz;
	} // Fim de if

   // Insere um n� na �rvore n�o-vazia
	q = Raiz;
	while (q != NULL)
   {
   	p = q;
		if (Info->Matricula < q->Matricula) q = p->LL;
		else q = p->RL;
   } // Fim de while

   // Insere como um novo n� e finaliza
   if (Info->Matricula < p->Matricula) p->LL = Px;
   else p->RL = Px;

   return Raiz;
} // Fim de InsereNovoRegistro

//----------------------------------------------------------------------------//

// Fun��o LeReg: Retorna o numero de registros do arquivo de dados
int LeReg(void)
{
   // Defini��o de vari�veis
	FILE *Pf;
	int valor = 0;
	DADOS Dados;

	Pf = fopen("AGENDA.DAT", "rb+");
	if (Pf == NULL) return 0;
	while(fread(&Dados, sizeof(DADOS), 1, Pf) != 0) valor++;
	fclose(Pf);
	return valor;
} // Fim de LeReg

//----------------------------------------------------------------------------//

// Fun��o LiberaMem: Libera a mem�ria alocada pelo arquivo de chaves
void LiberaMem(ARVORE *Raiz)
{
	// Defini��o de vari�veis
   ARVORE *Px;

	// Verifica se a �rvore est� vazia
   if (!Raiz) return;

   // Caminha na sub-�rvore esquerda de R
	LiberaMem(Raiz->LL);
	Px = Raiz->RL;
	free(Raiz);

	// Caminha na subarvore direita de R
 	LiberaMem(Px);
} // Fim de LiberaMem

//----------------------------------------------------------------------------//

// Fun��o Menu: Imprime o menu
int Menu(void)
{
	int op;

	clrscr();
	printf("\n     Projeto final de curso - Estruturas de Dados / Prof. Sdnei Brito");
	printf("\n     Nome: Heron Yugo Inouye    -  Matricula: 11877  -  CCO 2003");
	printf("\n     Nome: Tiago Romero Garcia  -  Matricula: 12643  -  CCO 2004");
   printf("\n\n\n\tMenu de Opcoes:");
   printf("\n\t  1. Inserir um registro");
   printf("\n\t  2. Remover um registro");
   printf("\n\t  3. Buscar um registro");
   printf("\n\t  4. Compactar o arquivo");
   printf("\n\t  0. Sair");
   printf("\n\n\tDigite a opcao desejada: ");
   scanf("%d", &op);
   printf("\n\n");

   return op;

} // Fim de Menu

//----------------------------------------------------------------------------//

// Fun��o OrdemSimetrica: Percorre a �rvore em ordem sim�trica de forma seq�encial
void OrdemSimetrica(ARVORE *Raiz, int *V)
{
   // Defini��o de variaveis
	ARVORE *p,*q;
   PILHA PilhaA;
   int VLogico;

   // Inicializa��o das vari�veis
   q = Raiz;
   VLogico = 1;
   PilhaA.Topo = 0;

   while (VLogico == 1)
   {
   	while (q != NULL)
      {
      	p = q;
         Push(&PilhaA, p);
         q = p->LL;
      } // Fim de while
      p = Pop(&PilhaA);
      *V = p->Matricula;
      V++;
      while ((p->RL == NULL) && (PilhaA.Topo != 0))
      {
      	p = Pop(&PilhaA);
			*V = p->Matricula;
         V++;
      } // Fim de while
      q = p->RL;
      if ((PilhaA.Topo == 0) && (q == NULL)) VLogico = 0;
   } // Fim de while
} // Fim de OrdemSimetrica

//----------------------------------------------------------------------------//

// Fun��o Pop: Retira um endere�o da pilha de endere�os
ARVORE *Pop(PILHA *PilhaA)
{
	// Defini��o de vari�veis
  	ARVORE *P;

  	// Verifica se a pilha est� vazia
  	PilhaA->Topo--;
	if (PilhaA->Topo < 0)
   {
      printf("\n\t\aERRO: Tentativa de underflow!\n");
      getch();
		return NULL;
   } // Fim de if

  	// Desempilha
  	P = PilhaA->Pilha[PilhaA->Topo];
  	return P;
} // Fim de Pop

//----------------------------------------------------------------------------//

// Fun��o Push: Empilha o endere�o da raiz
void Push(PILHA *PilhaA, ARVORE *P)
{
  	// Verifica se a pilha est� cheia
  	if (PilhaA->Topo >= MAX)
   {
      printf("\n\t\aERRO: Tentativa de overflow!\n");
      getch();
   	return;
   } // Fim de if

  	// Insere na PILHA
  	PilhaA->Pilha[PilhaA->Topo] = P;
  	PilhaA->Topo++;
} // Fim de Push

//----------------------------------------------------------------------------//

// Fun��o Remove:	Verifica se o dado a ser removido est� armazenado na �rvore
ARVORE *Remove(ARVORE *Raiz, int mat)
{
	// Defini��o de vari�veis
	FILE *Pf;
   ARVORE *Paux;

   // Busca o ponteiro que aponta para n� da arvore
   Paux = BuscaNo(Raiz, mat);
   if (!Paux)
   {
      printf("\n\tDado nao encontrado.\n");
      return Raiz;
   } // Fim de if

	// Busca no arquivo
	Pf = fopen("AGENDA.DAT", "rb+");
	if (Pf == NULL)
   {
		printf("\n\t\aERRO: Arquivos de dados nao encontrado.\n");
	  	return NULL;
   } // Fim de if
	Raiz = RemoveNoArvore(Raiz, mat);
	fclose(Pf);
   return Raiz;
} // Fim de Remove

//----------------------------------------------------------------------------//

// Fun��o RemoveDaFila: Remove um valor da fila
ARVORE *RemoveDaFila(FILA &Fila)
{
	// Vari�veis locais
	ARVORE *P;

	// Verificando Underflow
	if (Fila.p == Fila.u) return NULL;

	// Retirando o elemento
	P = Fila.fila[Fila.u];
	Fila.u = Sucessor(Fila, Fila.u);
	return P;

} // Fim de RemoveDaFila

//----------------------------------------------------------------------------//

// Fun��o RemoveNoArvore: Remove um n� da Arvore
ARVORE *RemoveNoArvore(ARVORE *R, int x)
{
	// Defini��o de vari�veis
	ARVORE *P, *P2;

   // Verifica se � o n� a ser removido
   if (R == NULL)
   {
    	printf("\n\tDado nao encontrado.\n");
   	return NULL;
   } // Fim de if
   if (R->Matricula == x)
   {
		// N�o existem sub�rvores. Elimina o n�, neste caso.
   	if (R->LL == R->RL)
      {
         printf("\n\tDado Removido com sucesso.");
			printf("\n\t  Matricula: %d\n", R->Matricula);
			free(R);
         return NULL;
      } // Fim de if

      // A sub�rvore esquerda de R � vazia
      else if(R->LL == NULL)
      {
			P = R->RL;
         printf("\n\tDado Removido com sucesso.");
			printf("\n\t  Matricula: %d\n", R->Matricula);
         free(R);
         return P;
      } // Fim de else

		// A sub�rvore direita de R � vazia
      else if(R->RL == NULL)
      {
      	P = R->LL;
         printf("\n\tDado Removido com sucesso.");
			printf("\n\t  Matricula: %d\n", R->Matricula);
         free(R);
         return P;
      } // Fim de else

      // Existem ambas as sub�rvores de R
      else
      {
         P = R->RL;
         P2 = P;
         // Procura o sucessor
         while (P->LL)
         {
            P2 = P;
            P = P->LL;
         }
         printf("\n\tDado Removido com sucesso.");
			printf("\n\t  Matricula: %d\n", R->Matricula);
         R->Matricula = P->Matricula;
			R->EnderecoRegistro = P->EnderecoRegistro;
         if (P2 == P) R->RL = P->RL;
         else P2->LL = P->RL;
         free(P);
         return R;
      } // Fim de else
   } // Fim de if

   if (R->Matricula < x) R->RL = RemoveNoArvore(R->RL,x);
   else R->LL = RemoveNoArvore(R->LL,x);
   return R;
} // Fim de RemoveNoArvore

//----------------------------------------------------------------------------//

// Fun��o ReservaNO: Reserva um novo n�
ARVORE *ReservaNo(void)
{
   ARVORE *p;
   p = (ARVORE *)calloc(1, sizeof(ARVORE));
   p->RL = NULL;
   p->LL = NULL;
   return p;
} // Fim de ReservaNO

//----------------------------------------------------------------------------//

// Fun��o SalvaArvore: Salva o arquivo de chaves no arquivo binario INDEX.DAT
void SalvaArvore(ARVORE *Raiz)
{
	// Defini��o de vari�veis
   FILA Fila;
   ARVORE *R, *T;
   FILE *Pf;

	// Inicializa��o das vari�veis
	Fila.base = Fila.p = Fila.u = 0;
	Fila.limite = MAX-1;

   // Verifica se a Raiz existe
   if (!Raiz)
   {
   	remove("INDEX.DAT");
   	return;
   } // Fim de if

	// Abre o arquivo bin�rio
	Pf = fopen("INDEX.DAT", "wb+");
	if (Pf == NULL)
   {
		printf("\n\t\aERRO: O arquivo nao foi aberto: INDEX.DAT\n");
		getch();
		return;
	} // Fim de if

	// Inicia o processo de salvamento
   InsereNaFila(Fila, Raiz);
   while (Fila.p != Fila.u)
   {
   	R = RemoveDaFila(Fila);
		fwrite(R, sizeof(ARVORE), 1, Pf);
      for (int i=0; i<2; i++)
      {
      	T = BuscaSubArvore(R, i);
         if (T) InsereNaFila(Fila, T);
      } // Fim de for
   } // Fim de while
	fclose(Pf);

} // Fim de SalvaArvore

//----------------------------------------------------------------------------//

// Fun��o SalvaReg: Salva a arvore no arquivo de dados AGENDA.DAT
void SalvaReg(DADOS *Info)
{
   // Defini��o de variaveis Locais
	FILE *Pf;

	// Abre o arquivo bin�rio
	Pf = fopen("AGENDA.DAT", "ab+");
	if (Pf == NULL )
   {
		printf("\n\t\aERRO: O arquivo nao foi aberto: AGENDA.DAT\n");
		return;
	} // Fim de if

	// Inicia o processo de salvamento
	fwrite(Info, sizeof(DADOS), 1, Pf);
	fclose(Pf);
	printf("\n\tRegistro salvo com sucesso.\n");   
} // Fim de SalvaReg

//----------------------------------------------------------------------------//

// Fun��o Sucessor: Circula a fila
int Sucessor(FILA Fila, int px)
{
	if (px >= Fila.limite) return Fila.base;
	return ++px;

} // Fim de Sucessor

