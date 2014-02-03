/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Projeto final de curso - Entrega: 10/12/2004                               *
*   Objetivos: Criar um sistema de arquivo seqüencial indexado com chave       *
*					primária única armazenada em um arquivo de chaves, organizado   *
*              na forma de uma árvore de grau 2 (binária), utilizando o        *
*              método Ordem Simétrica                                          *
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
#define MAX 50

//----------------------------------------------------------------------------//

// Declaração de estruturas
typedef struct ARVORE
{
	ARVORE *LL, *RL;
   int  Matricula;
   long EnderecoRegistro;
} ARVORE;

typedef struct ARVREG
{
   int  Matricula;
   long EnderecoRegistro;
} ARVREG;

typedef struct FILA
{
   ARVORE *fila[MAX];
   int base, limite, p, u;
} FILA;

typedef struct REGISTRO
{
	int Matricula;
   char Nome[20], Telefone[10];
} REGISTRO;

//----------------------------------------------------------------------------//

// Protótipos das funções
int       Arbval(int ls, int li, ARVREG Avr[MAX], ARVREG Cha[MAX], int &k);
ARVORE   *BuscaNO(ARVORE *Raiz, int mat);
ARVORE   *BuscaSubArvore(ARVORE *R, int i);
int       CompactaArquivos(ARVORE *&R, REGISTRO Reg[MAX], int &end);
int       GravaEmLargura(ARVORE *R, FILE *Ac);
ARVORE   *InsereNO(ARVORE *Raiz, ARVORE *R, int mat, long end);
int	    InsereNaFila(FILA &Fila, ARVORE *P);
int       Menu(void);
ARVORE   *RemoveDaFila(FILA &Fila);
ARVORE   *ReservaNO(void);
REGISTRO *ReservaREG(void);
int       Sucessor(FILA Fila, int px);

//temp
int sPercursoEmLargura(ARVORE *R);

//----------------------------------------------------------------------------//

// Programa main
void main(void)
{
   // Definição de variáveis
   ARVORE *Raiz=NULL, *Res;
   FILE *Ac;
	REGISTRO Reg[MAX], *P;
   int endReg=0, end=0, mat, op;
   long aend;
   char nome[20], fone[10], *msg = "\n\tStatus da recuperacao dos arquivos:\n";

   // Inicialização de variáveis
   Reg[0].Matricula = 0;

   // Recuperação do arquivo de chaves
   Ac = fopen("INDEX.DAT", "r");
   if (!Ac) strcat(msg, "\n\tALERTA: Nao foi possivel abrir o arquivo de chaves INDEX.DAT.\n\t      Criando um novo...");
   else
   {
		fscanf(Ac, "%d", &end);
		if (end==0)	strcat(msg, "\n\tALERTA: O arquivo de chaves INDEX.DAT esta vazio.");
		else
		{
			fscanf(Ac, "%d", &mat);
      	fscanf(Ac, "%ld", &aend);
         Res = InsereNO(Raiz, Raiz, mat, aend);
			if (!Res) strcat(msg, "\n\tERRO: Um no nao foi alocado com sucesso!");
			Raiz = Res;
         while(!feof(Ac))
         {
				fscanf(Ac, "%d", &mat);
      		fscanf(Ac, "%ld", &aend);
	         Res = InsereNO(Raiz, Raiz, mat, aend);
				if (!Res) strcat(msg, "\n\tERRO: Um no nao foi alocado com sucesso!");
         } // Fim de while
	      strcat(msg, "\n\tArquivo de chaves carregado com sucesso de INDEX.DAT.");
			fclose(Ac);
		}
	} // Fim de else

	// Recuperação do arquivo de dados
   Ac = fopen("AGENDA.DAT", "rb");
   if (!Ac)	strcat(msg, "\n\tALERTA: Nao foi possivel abrir o arquivo de dados AGENDA.DAT.\n\t      Criando um novo...");
   else
   {
      P = ReservaREG();
      if (!P) strcat(msg, "\n\tERRO: Um no nao foi alocado com sucesso!");
      if (!endReg) endReg = &P;
      fread(P, sizeof(REGISTRO), 1, Ac);
      if (P->Matricula != 0)
      {
      	strcat(msg, "\n\tArquivo de dados carregado com sucesso de AGENDA.DAT.");
	      while (P->Matricula != 0)
      	{
		      P = ReservaREG();
	   	   if (!P) strcat(msg, "\n\tERRO: Um no nao foi alocado com sucesso!");
		      fread(P, sizeof(REGISTRO), 1, Ac);
	         end++;
	      } // Fim de while
      } // Fim de if
      else strcat(msg, "\n\tALERTA: O arquivo de dados AGENDA.DAT esta vazio.");
   	fclose(Ac);
   } // Fim de else

  	printf("%s\n\t[Pressione qualquer tecla para continuar...]\n\a", msg);
	getch();

   do
   {
   	op = Menu();
   	switch(op)
      {
      	case 1:  // Insere um registro

				      P = ReservaREG();
				      if (!P) return NULL; // Nó não alocado com sucesso
                  if (!endReg) endReg = &P;

         			// Busca da chave primária no arquivo de chaves
                  do
                  {
                  	printf("\t  Digite a matricula: ");
							scanf(" %d", &mat);
                     if (mat<=0)
                     {
                    		printf("\n\t\aERRO: Digite um valor positivo!\n\t[Pressione qualquer tecla para continuar...]\n");
                       	getch();
                     }
                     Res = NULL;
         				if (Raiz)
                  	{
								Res = BuscaNO(Raiz, mat);
								if (Res)
                    		{
                     		printf("\n\t\aERRO: Matricula existente!\n\t[Pressione qualquer tecla para continuar...]\n");
                        	getch();
                        	// return -1;
                        	break;
                     	}
                  	} // Fim de if
                  } while ((Res)||(mat<=0));
                 	P->Matricula = mat;

       				do
                  {
							printf("\t  Digite o nome: ");
							scanf(" %[^\n]", &nome);
                    	if (strlen(nome)>20)
                    	{
                    		printf("\n\t\aERRO: Digite um nome com menos que 20 caracteres!\n\t[Pressione qualquer tecla para continuar...]\n\n");
                       	getch();
                   	} // Fim de if
                  } while (strlen(nome)>20);
                  strcpy(P->Nome, nome);
                  do
                  {
							printf("\t  Digite o telefone: ");
							scanf(" %[^\n]", &fone);
                    	if (strlen(fone)>20)
                   	{
                    		printf("\n\t\aERRO: Digite um nome com menos que 20 caracteres!\n\t[Pressione qualquer tecla para continuar...]\n\n");
                      	getch();
                   	} // Fim de if
                  } while (strlen(fone)>20);
                  strcpy(P->Telefone, fone);
                  end++;

                  // Inserção no arquivo de chaves
                  Res = InsereNO(Raiz, Raiz, mat, endReg+end*sizeof(REGISTRO));
						if (!Res)
                  {
	   					printf("\n\t\aERRO: O no nao foi alocado com sucesso!\n\t[Pressione qualquer tecla para continuar...]\n");
     		            getch();
                  } // Fim de if
						if (!Raiz) Raiz = Res;
                  break;

      	case 2:  // Remove um registro
                  break;

      	case 3:  // Busca de um registro
         			if (Raiz) sPercursoEmLargura(Raiz);
                  else printf("\t\aERRO: Arvore vazia!");
                  printf("\n\t[Pressione qualquer tecla para continuar...]\n");
						getch();
                  break;

      	case 4:  // Compactação do arquivo
         			if (Raiz)
                  {
                     if (!CompactaArquivos(Raiz, Reg, end)) printf("\t\aERRO: Ocorreram problemas na recriacao do arquivo de chaves.");
                     else printf("\t\Compactacao dos arquivos efetuada com sucesso.");
                  }
                  else printf("\t\aERRO: Arquivos vazios!");
                  printf("\n\t[Pressione qualquer tecla para continuar...]\n");
                  getch();
                  break;

         case 0:  // Sair
   					printf("\tFinalizando...\n");

                  // Gravação do arquivo de chaves
					   Ac = fopen("INDEX.DAT", "w");
					   fprintf(Ac, "%d", end);
                  if (Raiz) GravaEmLargura(Raiz, Ac);
					   fclose(Ac);
                  printf("\n\tArquivo de chaves gravado com sucesso em INDEX.DAT.");

                  // Gravação do arquivo de dados
					   Ac = fopen("AGENDA.DAT", "wb+");
                  &P = endReg;
                  if (P->Matricula != 0) fwrite(P, sizeof(REGISTRO), end, Ac);
					   fclose(Ac);

                  printf("\n\tArquivo de chaves dados com sucesso em AGENDA.DAT\n\t[Pressione qualquer tecla para continuar...]\n");
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

// Função Arbval: Cria um vetor balanceado a partir de um vetor ordenado
int Arbval(int ls, int li, ARVREG Avr[MAX], ARVREG Cha[MAX], int &k)
{
	// Declaração de variáveis
   int meio;

   meio = (ls+li)/2;
   if (li>ls) return 1;

   Cha[k].Matricula = Avr[meio-1].Matricula;
   Cha[k].EnderecoRegistro = Avr[meio-1].EnderecoRegistro;
   k++;
   Arbval(meio-1, li, Avr, Cha, k);
   Arbval(ls, meio+1, Avr, Cha, k);

} // Fim de Arbval

//----------------------------------------------------------------------------//

// Função BuscaNO: Busca um nó na árvore usando método recursivo
ARVORE *BuscaNO(ARVORE *R, int mat)
{
	// Declaração de variáveis
   ARVORE *Pesq;

	// Verifica se arvore está vazia
   if (!R) return 0;

   // Verificando se encontrou a informação
   if (R->Matricula == mat)
		return R;

   // Pesquisa pelas sub-árvores da esquerda e direita
   if (mat < R->Matricula)
   	Pesq = BuscaNO(R->LL, mat);
   else
   	Pesq = BuscaNO(R->RL, mat);

   return Pesq;

} // Fim de BuscaNO

//----------------------------------------------------------------------------//

// Função BuscaSubArvore: Busca a i-ésima sub-árvore de uma árvore
ARVORE *BuscaSubArvore(ARVORE *R, int i)
{
	// Declaração de variáveis
   ARVORE *P=NULL;

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

// Função CompactaArquivos: Otimiza os arquivos de dados e chaves
int CompactaArquivos(ARVORE *&Raiz, REGISTRO Reg[MAX], int &end)
{
	// Declaração de variáveis
   FILA Fila;
   ARVORE *T, *R=Raiz;
	ARVREG Avr[MAX], Cha[MAX];
   REGISTRO Comp[MAX];
   int i, j=0, k=0, endComp=0;

   // Inicialização de variáveis
	Fila.base = Fila.p = Fila.u = 0;
	Fila.limite = MAX-1;

   // Balanceamento do arquivo de chaves
   InsereNaFila(Fila, Raiz);
   while (Fila.p != Fila.u)
   {
   	R = RemoveDaFila(Fila);
      Avr[j].Matricula = R->Matricula;
      Avr[j].EnderecoRegistro = R->EnderecoRegistro;
      j++;
      for (i=0; i<2; i++)
      {
      	T = BuscaSubArvore(R, i);
         if (T) InsereNaFila(Fila, T);
      } // Fim de for
   } // Fim de while

	Arbval(j, 1, Avr, Cha, k);

	Raiz = NULL;
   R = InsereNO(Raiz, Raiz, Cha[0].Matricula, Cha[0].EnderecoRegistro);
	if (!R)	return 0;
	Raiz = R;
   for (i=1; i<j; i++)
   {
	   R = InsereNO(Raiz, Raiz, Cha[i].Matricula, Cha[i].EnderecoRegistro);
		if (!R) 	return 0;
   } // Fim de for

   // Compactação do arquivo de dados
   for (i=0; i<end; i++)
   {
		R = BuscaNO(Raiz, Reg[i].Matricula);
		if (R)
		{
			Comp[endComp].Matricula = Reg[i].Matricula;
			strcpy(Comp[endComp].Nome, Reg[i].Nome);
			strcpy(Comp[endComp].Telefone, Reg[i].Telefone);
         R->EnderecoRegistro = endComp;
         endComp++;
	   } // Fim de if
   } // Fim de for

   for (i=0; i<endComp; i++)
   {
		Reg[i].Matricula = Comp[i].Matricula;
		strcpy(Reg[i].Nome, Comp[i].Nome);
		strcpy(Reg[i].Telefone, Comp[i].Telefone);
   } // Fim de for

	// Atribuição do total de endereços do arquivo de dados
   end = i;

	return 1;

} // Fim de CompactaArquivos

//----------------------------------------------------------------------------//

// Função sGravaEmLargura: Grava os nós por percurso em largura usando método seqüencial no arquivo de chaves
int GravaEmLargura(ARVORE *R, FILE *Ac)
{
	// Declaração de variáveis
   FILA Fila;
   ARVORE *T;

   // Inicialização de variáveis
	Fila.base = Fila.p = Fila.u = 0;
	Fila.limite = MAX-1;

   InsereNaFila(Fila, R);
   while (Fila.p != Fila.u)
   {
   	R = RemoveDaFila(Fila);
	   fprintf(Ac, " %d", R->Matricula);
   	fprintf(Ac, " %ld", R->EnderecoRegistro);
      for (int i=0; i<2; i++)
      {
      	T = BuscaSubArvore(R, i);
         if (T) InsereNaFila(Fila, T);
      } // Fim de for

   } // Fim de while

	return 1;

} // Fim de sPercursoEmLargura

//----------------------------------------------------------------------------//

// Função InsereNaFila: Insere um valor na fila
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

// Função rInsereNO: Insere um nó numa árvore binária usando método recursivo
ARVORE *InsereNO(ARVORE *Raiz, ARVORE *R, int mat, long end)
{
	// Se o ponto de inserção for localizado, insere um novo nó
	if (!R)
   {
   	// Reservando memória para um novo nó
   	R = ReservaNO();
      if (!R) return NULL; // Registro não alocado com sucesso

		// Inserindo informação no nó
		R->Matricula = mat;
      R->EnderecoRegistro = end;
      R->LL = R->RL = NULL;

      if (Raiz)
      {
      	if (mat < Raiz->Matricula)
         	Raiz->LL = R;
      	else
         	Raiz->RL = R;
      } // Fim de if
      return R;

   } // Fim de if

	// Continua a busca pelo ponto de inserção (nó folha)
   if (mat < R->Matricula)
   	InsereNO(R, R->LL, mat, end);
   else
   	InsereNO(R, R->RL, mat, end);

   return R;

} // Fim de rInsereNO

//----------------------------------------------------------------------------//

// Função Menu: Imprime o menu
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

// Função RemoveDaFila: Remove um valor da fila
ARVORE *RemoveDaFila(FILA &Fila)
{
	// Variáveis locais
	ARVORE *P;

	// Verificando Underflow
	if (Fila.p == Fila.u) return NULL;

	// Retirando o elemento
	P = Fila.fila[Fila.u];
	Fila.u = Sucessor(Fila, Fila.u);
	return P;

} // Fim de RemoveDaFila

//----------------------------------------------------------------------------//

// Função ReservaNO: Reserva um nó na memória
ARVORE *ReservaNO(void)
{
	ARVORE *P;
   P = (ARVORE *) calloc (1, sizeof(ARVORE));
   return P;

} // Fim de ReservaNO

//----------------------------------------------------------------------------//

// Função ReservaREG: Reserva um registro na memória
REGISTRO *ReservaREG(void)
{
	REGISTRO *P;
   P = (REGISTRO *) calloc (1, sizeof(REGISTRO));
   return P;

} // Fim de ReservaNO

//----------------------------------------------------------------------------//

// Função Sucessor: Circula a fila
int Sucessor(FILA Fila, int px)
{
	if (px >= Fila.limite) return Fila.base;
	return ++px;

} // Fim de Sucessor


//temp

// Função sPercursoEmLargura: Lista os nós por percurso em largura usando método seqüencial
int sPercursoEmLargura(ARVORE *R)
{
	// Declaração de variáveis
   FILA Fila;
   ARVORE *T;

   // Inicialização de variáveis
	Fila.base = Fila.p = Fila.u = 0;
	Fila.limite = MAX-1;

   InsereNaFila(Fila, R);
   while (Fila.p != Fila.u)
   {
   	R = RemoveDaFila(Fila);
	   printf("\tMatricula: %d\n", R->Matricula);
  		printf("\tEndereco: %ld\n\n", R->EnderecoRegistro);
      for (int i=0; i<2; i++)
      {
      	T = BuscaSubArvore(R, i);
         if (T) InsereNaFila(Fila, T);
      } // Fim de for

   } // Fim de while

	return 1;

} // Fim de sPercursoEmLargura


