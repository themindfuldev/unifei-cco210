/*******************************************************************************

								PROGRAMA DE ARVORE INDEXADA

--------------------------------------------------------------------------------

DISCIPLINA: CCO-210 - Estrutura de Dados
PROFESSOR: Sdnei de Brito Alves, Dr.                 MONITOR: Daltro

--------------------------------------------------------------------------------

Nomes:												Matriculas:
Breno Lisi Romano								   	11316
Thiago Nascimento Comicio							11889

/*----------------------------------------------------------------------------*/

//Declaracao das Bibliotecas
#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*----------------------------------------------------------------------------*/

//Constantes
#define F1 59
#define F2 60
#define F3 61
#define F4 62
#define F5 63
#define End 79
#define HOME 71
#define Max 30

/*----------------------------------------------------------------------------*/

//Definicao das Estruturas
typedef struct TREE{
	TREE *LL;
	int Mat;
	long int Endereco;
	TREE *RL;
}TREE;

typedef struct DADOS{
	int Matricula;
	char Nome[21];
}DADOS;

typedef struct PILHA {
	TREE *Pilha[Max];
   int Topo;
}PILHA;

/*----------------------------------------------------------------------------*/

//Prototipos das Funcoes
TREE *ReservaNO(void);
int Menu(void);
void SalvaReg(DADOS *Info);
TREE *InsereNovoRegistro(TREE *Raiz);
int LeReg(void);
void PrintArvore(TREE *R, int L);
void SalvaTREE(TREE *Raiz);
void Push(PILHA *PilhaA, TREE *p);
TREE *Pop(PILHA *PilhaA);
TREE *CarregTREE(TREE *Raiz);
TREE *BuscaNO(TREE *Raiz, int Mat);
void BuscaInfo(TREE *Raiz, int Mat);
TREE *RemoveNoTREE(TREE *R, int x);
TREE *Remove(TREE *Raiz, int Mat);
void CompactaArquivo(TREE *Raiz);
void OrdemSimetrica(TREE *Raiz, int *V);
TREE *BalanArvore(TREE *Raiz);
void ArbVal(int Ls, int Li, int *V,int *V2, int *vetNovo, int *vet, int NReg);
TREE *CriaNovaArvore(TREE *Raiz1, TREE *Raiz2, int *V2);
void liberaMem(TREE *Raiz);

/*----------------------------------------------------------------------------*/

/*void main
	Programa Principal*/
void main(void){
	//Variaveis Locais
	TREE *Raiz = NULL;
   int Opcao = 0;
   int Mat;

	//Carregando arquivo da arvore
	Raiz = CarregTREE(Raiz);
	if (Raiz == NULL){
   	clrscr();
   	printf("\n------------------------------------------------------------------------");
		printf("\n\t\t   Programa de Arvores Indexadas");
		printf("\n------------------------------------------------------------------------\n");
      printf("\n  [ATENCAO] Falha no carregamento do arquivo de arvores");
      getch();
   }

	//Programa
	while(Opcao != End) {
		Opcao = Menu();
   	switch(Opcao) {
         case F1:
            clrscr();
            printf("\n------------------------------------------------------------------------");
            printf("\n\t\t\t Inserindo Novo registro");
            printf("\n------------------------------------------------------------------------\n");
            Raiz = InsereNovoRegistro(Raiz);
            getch();
            break;

         case F2:
            clrscr();
            printf("\n------------------------------------------------------------------------");
            printf("\n\t\t Removendo um dos registros");
            printf("\n------------------------------------------------------------------------\n");
            if(!Raiz){
               printf("Crie primeiro a arvore");
               getch();
            	break;
            }
				printf("\nDigite a MATRICULA [6]: ");
				scanf("%d",&Mat);
            Raiz = Remove(Raiz,Mat);
            getch();
            break;

         case F3:
            clrscr();
            printf("\n------------------------------------------------------------------------");
            printf("\n\t\t Buscando Registro");
            printf("\n------------------------------------------------------------------------\n");
            if(!Raiz){
               printf("Crie primeiro a arvore");
               getch();
               break;
            }
				printf("\nDigite a MATRICULA [6]: ");
				scanf("%d",&Mat);
				BuscaInfo(Raiz,Mat);
				getch();
            break;

         case F4:
            clrscr();
            printf("\n------------------------------------------------------------------------");
            printf("\n\t\t Compactacao do arquivo");
            printf("\n------------------------------------------------------------------------\n");
            CompactaArquivo(Raiz);
  	         Raiz = BalanArvore(Raiz);
            printf("\n [COMPACTACAO]  Arvore balanceada e compactada com sucesso");
            getch();
            break;

         case End:
            liberaMem(Raiz);
            printf("\n\n Memoria Liberada com sucesso");
            printf("\n\n Finalizando o Programa...");
            getch();
            break;

			case HOME:
				clrscr();
				printf("\n------------------------------------------------------------------------");
				printf("\n\t\t Imprime a Arvore Em Forma Horizontal");
				printf("\n------------------------------------------------------------------------\n\n");
				if(!Raiz)
	            printf("\n Crie Primeiro a Arvore");
				else
   	         PrintArvore(Raiz, 0);
				getch();
            break;

         default:
            printf("\n\n Opcao Invalida...");
            getch();
            break;
   	}//switch
	}//while
}//fim de main

/*----------------------------------------------------------------------------*/

/*int Menu
	Imprime as opcoes*/
int Menu(void) {
	//Delcaracao das Variaveis Locais
	int Opcao;

	do {
   	clrscr();
   	printf("\n------------------------------------------------------------------------");
		printf("\n\t\t   Programa de Arvores Indexadas");
		printf("\n------------------------------------------------------------------------\n");
      printf("\n  [F1]  Insere Novo registro");
		printf("\n  [F2]  Remove um dos registros");
      printf("\n  [F3]  Busca Registro");
      printf("\n  [F4]  Compactacao do arquivo");
		printf("\n  [Home] Imprime a Arvore Em Forma Horizontal");
      printf("\n  [End] Finaliza o programa");
   	printf("\n\n------------------------------------------------------------------------");
   	printf("\n Escolha uma opcao: ");
   }while( (Opcao=getch()) != 0);
   Opcao = getch();
   return Opcao;
}//fim de Menu

/*----------------------------------------------------------------------------*/

/*ReservaNO
	Reserva um novo Nó*/
TREE *ReservaNO(void)
{
   TREE *p;
   p = (TREE *)calloc(1, sizeof(TREE));
   p->RL = NULL;
   p->LL = NULL;
   return p;
}//fim de ReservaNO

/*----------------------------------------------------------------------------*/

TREE *InsereNovoRegistro(TREE *Raiz){
   //Variáveis Locais
   DADOS *Info;
   TREE *Px, *p, *q,*Paux;
   int nReg;

   //Reservando Memoria Dinamicamente do tipo DADOS
   Info = (DADOS *)calloc(1, sizeof(DADOS));

   //Lendo a chave primaria - Matricula
   printf("\nDigite a MATRICULA [6]: ");
   scanf("%d", &Info->Matricula);

   //Verificando se ja existe Matricula
   Paux = BuscaNO(Raiz, Info->Matricula);
   if(Paux) {
		printf("\nMatricula %d ja esta armazenada", Info->Matricula);
      getch();
      return Raiz;
   }

	//Lendo os outros dados
   printf("\nDigite o NOME [20]: ");
   scanf(" %[^\n]", Info->Nome);

   //Verificando a quantidade de registros
   nReg = LeReg();

   //Salvando no arquivo Dados.dat
   SalvaReg(Info);
	printf("\n [DADOS] Registro salvo com sucesso");

	//Colocando o dado na arvore
   Px = ReservaNO();
   if(!Px) return NULL;
   Px->Endereco = nReg * sizeof(DADOS);
   Px->Mat = Info->Matricula;

   //Insere o Primeiro NO
	if(!Raiz) {
		Raiz = Px;
		SalvaTREE(Raiz);
		return Raiz;
	}

   //Insere um NO na Arvore Nao Vazia
	q = Raiz;
	while(q != NULL) {
   	p = q;
		if(Info->Matricula < q->Mat) q = p->LL;
		else q = p->RL;
   }

   //Insere como um Novo NO e Finaliza
   if(Info->Matricula < p->Mat) p->LL = Px;
   else p->RL = Px;

   //salva arvore
   SalvaTREE(Raiz);

   return Raiz;
}//fim de InsereNovoRegistro

/*----------------------------------------------------------------------------*/

/*void Push
	Empilha o endereço da raiz*/
void Push(PILHA *PilhaA, TREE *p){
  	// Verifica se pilha cheia
  	if(PilhaA->Topo >= Max) {
      printf("\n Overflow!!!");
      getch();
   	return;
   }

  	// Insere na PILHA
  	PilhaA->Pilha[PilhaA->Topo] = p;
  	PilhaA->Topo++;
}//fim de Push

/*----------------------------------------------------------------------------*/

/*TREE *Pop
	Função que retira um endereço da pilha de endereços*/
TREE *Pop(PILHA *PilhaA){
	//Variaveis Locais
  	TREE *p;

  	// Verifica se Pilha vazia
  	PilhaA->Topo--;
	if (PilhaA->Topo < 0) return NULL;

  	// Desempilha
  	p = PilhaA->Pilha[PilhaA->Topo];
  	return p;
}//fim de TREE *Pop

/*----------------------------------------------------------------------------*/

/*void SalvaTREE
	Salva a arvore no arquivo binario Tree.dat*/
void SalvaTREE(TREE *Raiz){
	//Variaveis Locais
	FILE *Pf;
	TREE *p,*q;
	PILHA PilhaA;
	int VLogico;

	//Inicializacao das Variaveis
	q = Raiz;
	VLogico = 1;
	PilhaA.Topo = 0;

   //Verifica se a Raiz existe
   if(!Raiz) {
   	remove("Tree.dat");
   	return;
   }

	// Abre o arquivo binário
	Pf = fopen("Tree.dat", "wb+");
	if (Pf == NULL ) {
		printf("\n Arquivo Nao foi aberto : Tree.dat");
		getch();
		return;
	}//fim if

	// Inicia o processo de salvamento
	while(VLogico == 1) {
      //Varrendo a SubArvore a Esquerda
      while(q != NULL) {
         p = q;
			fwrite(p, sizeof(TREE), 1, Pf);
         Push(&PilhaA, p);
         q = p->LL;
      }
      q = Pop(&PilhaA);

      if((PilhaA.Topo == 0) && (q->RL == NULL)) VLogico = 0;
      q = q->RL;
   }
	fclose(Pf);
}//fim de SalvaTREE

/*----------------------------------------------------------------------------*/
/*void SalvaReg
	Salva a arvore no arquivo de dados Dados.dat*/
void SalvaReg(DADOS *Info) {
   //Variaveis Locais
	FILE *Pf;

	// Abre o arquivo binário
	Pf = fopen("Dados.dat", "ab+");
	if (Pf == NULL ) {
		printf("\n Arquivo Nao foi aberto : Dados.dat");
		getch();
		return;
	}//fim if

	// Inicia o processo de salvamento
	fwrite(Info, sizeof(DADOS), 1, Pf);
	fclose(Pf);
}// Fim de SalvaReg

/*----------------------------------------------------------------------------*/

/*int LeReg
	Retorna o numero de registros do arquivo Dados*/
int LeReg(void) {
   //Variaveis Locais
	FILE *Pf;
	int valor = 0;
	DADOS Dados;

	Pf = fopen("Dados.dat", "rb+");
	if(Pf == NULL)
	  	return 0;
	while(fread(&Dados, sizeof(DADOS), 1, Pf) != 0) valor++;
	fclose(Pf);
	return valor;
}//fim de int LeReg

/*----------------------------------------------------------------------------*/

/*void PrintArvore
	Imprime a arvore de forma horizontal*/
void PrintArvore(TREE *R, int L){
   //Variaveis Locais
   int i;

	if (R == NULL) return;
	PrintArvore(R->LL,L+1);
	for(i=0;i<L;i++)
	printf("   ");
	printf(" %d %ld\n",R->Mat,R->Endereco);
	PrintArvore(R->RL,L+1);
}//fim de void PrintArvore

/*----------------------------------------------------------------------------*/

/*TREE *CarregTREE
	Carrega arvore do arquivo Tree.dat*/
TREE *CarregTREE(TREE *Raiz) {
	//variáveis
	FILE *Pf;
   TREE *Px, *p, *q;

   Px = ReservaNO();
	Pf = fopen("Tree.dat", "rb");
	if(Pf == NULL)
		return NULL;

   //leitura do arquivo
   while(fread(Px, sizeof(TREE), 1, Pf) != 0){
		Px->RL = Px->LL = NULL;
      //monta a árvore
      if (Raiz == NULL){
		   Raiz = Px;
      }else{
			q = Raiz;
			while(q != NULL) {
				p = q;
				if(Px->Mat < q->Mat) q = p->LL;
				else q = p->RL;
			}//fim while

   		//Insere como um Novo NO e Finaliza
			if(Px->Mat < p->Mat) p->LL = Px;
			else p->RL = Px;
		}//fim if
      Px = ReservaNO();
   }//fim while
   free(Px);
	fclose(Pf);
	return Raiz;
}//fim de *CarregTREE

/*----------------------------------------------------------------------------*/

/*TREE *BuscaNO
	Busca um determinado nó na árvore*/
TREE *BuscaNO(TREE *Raiz, int Mat) {
	//Variaveis Locais
   TREE *paux;

	//Verifica se a Arvore esta Vazia
   if(!Raiz) return NULL;

   //Verifica se Encontrou o NO com a Informacao Dado
   if(Mat == Raiz->Mat) return Raiz;

  	//Pesquisar Na Sub-Arvore Esquerda e Direita
	if(Mat <= Raiz->Mat) paux = BuscaNO(Raiz->LL, Mat);
  	if(Mat > Raiz->Mat) paux = BuscaNO(Raiz->RL, Mat);
	return paux;
}//fim de TREE *BuscaNO

/*----------------------------------------------------------------------------*/

/*void BuscaInfo
	Verifica se um dado esta no arquivo de dados*/
void BuscaInfo(TREE *Raiz,int Mat){
	//Variaveis Locais
	FILE *Pf;
	DADOS Dados;
   TREE *Paux;

   //busca o ponteiro que aponta para no da arvore
   Paux = BuscaNO(Raiz,Mat);
   if (!Paux){
      printf("\n  [ERRO]  Dado nao encontrado");
      return;
   }

	//busca no arquivo
	Pf = fopen("Dados.dat", "rb+");
	if(Pf == NULL){
		printf("\n  [ERRO]  Arquivos de dados nao encontrado");
	  	return;
   }
   fseek(Pf, Paux->Endereco, 0);
	fread(&Dados, sizeof(DADOS), 1, Pf);
	fclose(Pf);
   printf("\n  [Registro Encontrado]");
   printf("\n    [Matricula]:\t%d",Dados.Matricula);
   printf("\n    [Nome]:\t\t%s",Dados.Nome);
}//fim de void BuscaInfo

/*----------------------------------------------------------------------------*/

/*TREE *RemoveNoTREE
	Remove um NO da Arvore*/
TREE *RemoveNoTREE(TREE *R, int x){
	//Variaveis Locais
	TREE *P, *P2;

   //Verifica se é o nó a ser removido
   if (R == NULL)
   {
    	printf("\n  [ERRO]  Dado nao encontrado");
   	return NULL;
   }
   if (R->Mat == x){
		//Não existem subárvores. Elimina o nó , neste caso.
   	if (R->LL == R->RL)
      {
         printf("\n  [REMOCAO DE DADO] : Dado Removido com sucesso");
			printf("\n    [Matricula]:\t%d",R->Mat);
			free(R);
         return NULL;
      }
      //A subárvore esquerda de R é vazia
      else if(R->LL == NULL)
      {
			P=R->RL;
         printf("\n  [REMOCAO DE DADO] : Dado Removido com sucesso");
			printf("\n    [Matricula]:\t%d",R->Mat);
         free(R);
         return P;
      }
		//A subárvore direita de R é vazia
      else if(R->RL == NULL)
      {
      	P = R->LL;
         printf("\n  [REMOCAO DE DADO] : Dado Removido com sucesso");
			printf("\n    [Matricula]:\t%d",R->Mat);
         free(R);
         return P;
      }
      //Existem ambas as subárvores de R
      else
      {
         P = R->RL;
         P2 = P;
         //Procura o Sucessor(x)
         while (P->LL)
         {
            P2 = P;
            P = P->LL;
         }
			printf("\n  [REMOCAO DE DADO] : Dado Removido com sucesso");
			printf("\n    [Matricula]:\t%d",R->Mat);
         R->Mat = P->Mat;
			R->Endereco = P->Endereco;
         if(P2 == P)
         	R->RL = P->RL;
         else
	         P2->LL = P->RL;
         free(P);
         return R;
      }
   }

   if (R->Mat < x) R->RL = RemoveNoTREE(R->RL,x);
   else R->LL = RemoveNoTREE(R->LL,x);
   return R;
}//fim de TREE *RemoveNo

/*----------------------------------------------------------------------------*/

/*TREE *Remove
	Verifica se o dado a ser removido esta armazenado na arvore*/
TREE *Remove(TREE *Raiz, int Mat){
	//Variaveis Locais
	FILE *Pf;
   TREE *Paux;

   //busca o ponteiro que aponta para no da arvore
   Paux = BuscaNO(Raiz,Mat);
   if (!Paux){
      printf("  [ERRO]  Dado nao encontrado");
      return Raiz;
   }

	//busca no arquivo
	Pf = fopen("Dados.dat", "rb+");
	if(Pf == NULL){
		printf("  [ERRO]  Arquivos de dados nao encontrado");
	  	return NULL;
   }
	Raiz = RemoveNoTREE(Raiz,Mat);
   SalvaTREE(Raiz);
	fclose(Pf);
   return Raiz;
}//fim de TREE *Remove

/*----------------------------------------------------------------------------*/

/*void CompactaArquivo
	Remove os registros do arquivo Dados.dat que nao possuem chaves associadas
   no arquivo de chaves*/

void CompactaArquivo(TREE *Raiz) {
   //Variaveis Locais
   FILE *P1, *P2;
   DADOS Info;
   TREE *q, *p;
	PILHA PilhaA;
	int VLogico, valor = 0;

	//Inicializacao das Variaveis
	q = Raiz;
	VLogico = 1;
	PilhaA.Topo = 0;

   P1 = fopen("Dados.dat", "rb");
	if(P1 == NULL)
		return;

	P2 = fopen("Novo.Dat", "wb+");
	if(P2 == NULL) {
		fclose(P1);
      return;
   }

   while(VLogico == 1) {
      //Varrendo a SubArvore a Esquerda
      while(q != NULL) {
         p = q;
			fseek(P1, p->Endereco, 0);
			fread(&Info, sizeof(DADOS), 1, P1);
         fwrite(&Info, sizeof(DADOS), 1, P2);
         p->Endereco = valor * sizeof(DADOS);
         valor++;
         Push(&PilhaA, p);
         q = p->LL;
      }
      q = Pop(&PilhaA);

      if((PilhaA.Topo == 0) && (q->RL == NULL)) VLogico = 0;
      q = q->RL;
   }

   SalvaTREE(Raiz);
   fclose(P1);
   fclose(P2);

   //Remove o arquivo original, com lixo
   if(remove("Dados.dat") != 0) {
   	printf("\nNao foi possivel remover o arquivo Dados.dat");
      getch();
      return;
   }

   //Transforma o arquivo Novo.dat, no arquivo original
   if(rename("Novo.dat", "Dados.dat") != 0) {
		printf("\nNao foi possivel renomear o arquivo Novo.dat");
      getch();
      return;
   }
}//fim de CompactaArquivo

/*----------------------------------------------------------------------------*/

/*void BalanArvore
	Funcao que balanceia a árvore*/
TREE *BalanArvore(TREE *Raiz) {
   int *vet, *V, *V2, *vetNovo;
   int NReg, i;
   TREE *Raiz2 = NULL;

   NReg = LeReg();

   vet = (int *)calloc(NReg, sizeof(int));
   vetNovo = (int *)calloc(NReg, sizeof(int));
   if ((!vet)||(!vetNovo)){
   	printf("  [ERRO]  Nao foi possivel alocar o vetor dos registros");
      return NULL;
   }
   V = vet;
	OrdemSimetrica(Raiz,V);
	V = vet;
   V2 = vetNovo;
   ArbVal(NReg, 1, V, V2, vetNovo, vet, NReg);
	V2 = vetNovo;
   for(i=1;i<=NReg;i++){
	   Raiz2 = CriaNovaArvore(Raiz,Raiz2,V2);
      V2++;
   }

   //salva arvore
   SalvaTREE(Raiz2);

	//Liberando a memoria da arvore antiga e dos vetores alocados dinamicamente
  	liberaMem(Raiz);
   free(vetNovo);
	free(vet);
   return Raiz2;
}//fim de *BalanArvore

/*----------------------------------------------------------------------------*/

/*void ArbVal
	Funcao que balanceia a árvore, otimizando a procura*/
void ArbVal(int Ls, int Li, int *V,int *V2, int *vetNovo, int *vet, int NReg) {
   //Variaveis Locais
	int Meio;
   static j = 0;

   if (NReg == Ls)
   	j = 0;
   Meio = (Ls+Li)/2;
   if(Li > Ls) return;
   V2 = vetNovo;
   V = vet;
   V2+=j;
   V+=(Meio-1);
   *V2 = *V;
   j++;
   ArbVal(Meio-1, Li, V, V2, vetNovo, vet, -1);
   ArbVal(Ls, Meio+1, V, V2, vetNovo, vet, -1);
}//fim de void ArbVal

/*----------------------------------------------------------------------------*/

/*void OrdemSimetrica
	Percorre a árvore em ordem simétrica de forma sequencial*/
void OrdemSimetrica(TREE *Raiz, int *V) {
   //Variaveis Locias
	TREE *p,*q;
   PILHA PilhaA;
   int VLogico;

   //Inicializacao das Variaveis
   q = Raiz;
   VLogico = 1;
   PilhaA.Topo = 0;

   while(VLogico == 1) {
   	while(q != NULL) {
      	p = q;
         Push(&PilhaA, p);
         q = p->LL;
      }
      p = Pop(&PilhaA);
      *V = p->Mat;
      V++;
      while((p->RL == NULL) && (PilhaA.Topo != 0)) {
      	p = Pop(&PilhaA);
			*V = p->Mat;
         V++;
      }
      q = p->RL;
      if((PilhaA.Topo == 0) && (q == NULL)) VLogico = 0;
   }
}//fim de void OrdemSimetrica

/*----------------------------------------------------------------------------*/
/*TREE *CriaNovaArvore
	Cria uma arvore balanceada*/
TREE *CriaNovaArvore(TREE *Raiz1, TREE *Raiz2, int *V2){
   //Variaveis Locais
   TREE *Px, *p, *q, *Paux;

	//colocando o dado na arvore
   Px = ReservaNO();
   if(!Px) return NULL;
   Paux = BuscaNO(Raiz1,*V2);
   Px->Endereco = Paux->Endereco;
   Px->Mat = *V2;

   //Insere o Primeiro NO
	if(!Raiz2) {
		Raiz2 = Px;
		SalvaTREE(Raiz2);
		return Raiz2;
	}

   //Insere um NO na Arvore Nao Vazia
	q = Raiz2;
	while(q != NULL) {
   	p = q;
		if(*V2 < q->Mat) q = p->LL;
		else q = p->RL;
   }

   //Insere como um Novo NO e Finaliza
   if(*V2 < p->Mat) p->LL = Px;
   else p->RL = Px;

   return Raiz2;
}//fim de CriaNovaArvore

/*----------------------------------------------------------------------------*/

/*void liberaMem
	Antes de sair libera a memoria*/
void liberaMem(TREE *Raiz){
	//Variaveis Locais
   TREE *Px;

	//verifica se arvore esta vazia
   if (!Raiz)
		return;

   //caminha na subarvore esquerda de R
	liberaMem(Raiz->LL);
	Px = Raiz->RL;
	free(Raiz);

	//caminha na subarvore direita de R
 	liberaMem(Px);
}//fim de liberaMem

/*----------------------------------------------------------------------------*/
