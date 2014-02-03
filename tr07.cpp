#include <stdio.h>
#include <conio.h>
#include <malloc.h>

// Estrutura de dados da LISTA
typedef struct LISTA {
        int Valor;
        LISTA *LL;
        LISTA *RL;
}LISTA;
// Protótipos
int Menu(void);
int 	InserePrimeiro(LISTA *&Pi, LISTA *&Pf, int Valor);
int 	InsereFinal(LISTA *&Pf, int Valor);
int 	InsereNaLista(LISTA *&Pi, LISTA *&Pf, int Valor);
LISTA *AlocaNO(void);
int 	Relatorio(LISTA *Pi);
int 	RemovePrimeiro(LISTA *&Pi, LISTA *&Pf, int Valor);
int 	RemoveFinal(LISTA *&Pi, LISTA *&Pf, int Valor);
int 	RemoveDaLista(LISTA *&Pi, LISTA *&Pf, int Valor);
int 	BuscaNO(LISTA *&Pi, LISTA *&P, int Valor);

// Inicio do programa que insere um valor, na ordem, em uma lista
void main (void) {
	//Definindo as variáveis necessárias
   LISTA *Pi=NULL, *Pf=NULL, *P;
   int Valor, opcao=0;
   // Menu de opções
   while (opcao != 9) {
   	opcao = Menu();
      switch(opcao) {
      	case 1 : 	// Insere na lista
         				printf("\n Digite um valor para insercao:");
                     scanf("%d", &Valor);
         				if(!InsereNaLista(Pi, Pf, Valor))
                     	printf("\n Problema na insercao - veja memoria !\n");
         				break;
         case 2 :	// Remove da lista
							printf("\n Digite o valor a ser removido:");
                     scanf("%d", &Valor);
         				if(!RemoveDaLista(Pi, Pf, Valor)) {
                       	printf("\n Lista vazia !.\n");
                        getch();
                     }
                     else
         				if(RemoveDaLista(Pi, Pf, Valor) == 2) {
                       	printf("\n Dado inexistente !.\n");
                        getch();
                     }
                     break;
         case 3 : 	// Listar os dados da Lista
         				if(!Relatorio(Pi)) {
                     	printf("\n\a Lista vazia!\n");
                        getch();
                     }
                     break;
         case 5 :	// Busca dos dados de um Nó
         				printf("\n Digite o valor a ser pesquisado:");
                     scanf("%d", &Valor);
         				if(!BuscaNO(Pi, P, Valor))
                     	printf("\n Dado inexistente!\n");
                     else
                        if(P->LL!=NULL)
                       	  printf("\n NO Anterior : %d, NO atual %d", P->LL->Valor, P->Valor);
                        else
                       	  printf("\n NO Anterior : NULL, NO atual %d", P->Valor);
                     getch();
                     break;
         case 9 :	// Fim das operações
         				printf("\n\a Finalizando as operacoes...!");
                     getch();
                     break;
      	default :	// Condição de erro
         				printf("\n\a Opcao incorreta. Escolha nova opcao!");
                     getch();
      }// Fim do switch()
   }// Fim do while()
}// Fim do main()

//************* Função MENU
int Menu(void) {
	int opcao;
   clrscr();
   printf("\n Escolha uma das operacoes :");
   printf("\n		1. Insercao de um no na Lista.");
   printf("\n		2. Remocao de um no da Lista.");
   printf("\n		3. Listagem dos dados da Lista.");
   printf("\n		5. Busca de dados na Lista.");
   printf("\n		9. Fim das operacoes......");
   printf("\n\n Escolha uma das operacoes sobre a Lista : ");
   scanf("%d", &opcao);
   return opcao;
}// Fim de Menu()

// ************* Função InserePrimeiro()
int InserePrimeiro(LISTA *&Pi, LISTA *&Pf, int Valor) {
	// Variaveis locais
   LISTA *Pnew;
   // Reserva um novo NO e prepara
   Pnew = AlocaNO();
   if(!Pnew) return 0;
   Pnew->Valor = Valor;
   Pnew->LL = NULL;

   // Insere o primeiro Nó, se lista vazia
   if(Pi==NULL){
   	Pi=Pf=Pnew;
      Pi->RL = NULL;
      return 1;
   }
   // Insere antes do Primeiro, se for o caso
   if(Valor <= Pi->Valor) {
      Pnew->RL = Pi;
      Pi->LL = Pnew;
      Pi = Pnew;
   }
   return 1;
}// Fim de InserePrimeiro()

//************** Função InsereFinal()
int InsereFinal(LISTA *&Pf, int Valor){
	// Variaveis locais
   LISTA *Pnew;
   Pnew = AlocaNO();
   if(!Pnew) return 0;
   Pnew->Valor = Valor;
   Pnew->RL = NULL;
   // Insere depois do fim
   Pnew->LL = Pf;
   Pf->RL = Pnew;
   Pf = Pnew;
   return 1;
}// Fim de InsereFinal()

//************** Função InsereNaLista()
int InsereNaLista(LISTA *&Pi, LISTA *&Pf, int Valor){
	// Define as variaveis locais
   LISTA *Pnew, *P, *Paux;
   // Insere o primeiro Nó, se lista vazia
   if(Pi==NULL || Valor <= Pi->Valor) {
      InserePrimeiro(Pi, Pf, Valor);
      return 1;
   }
   // Insere depois do fim
   if(Valor >= Pf->Valor) {
   	InsereFinal(Pf, Valor);
      return 1;
   }
   // Reserva um novo nó para insercao
   Pnew = AlocaNO();
   if(!Pnew) return 0;
   // Insere entre o primeiro e o ultimo - pesquisa
   P = Pi;
   while (Valor > P->Valor) {
     P = P->RL;
   }
   // Insere
   Pnew->Valor = Valor;
   Paux = P->LL;
   P->LL = Pnew;
   Paux->RL = Pnew;
   Pnew->LL = Paux;
   Pnew->RL = P;
   return 1;
   // Fim das operações
}// Fim de InsereNaLista()

//************* Função AlocaNO()
LISTA *AlocaNO(void){
	//define as variaveis locais
   LISTA *Px;
   Px = (LISTA *)calloc(1, sizeof(LISTA));
   return Px;
}// Fim de AlocaNO()

//************* Funcao Relatorio
int Relatorio (LISTA *Pi) {
	// Define as variaveis locais
   LISTA *Px;
   int NO=1;
   Px = Pi;
   if(!Pi)return 0;
   printf("\n Relatorio de dados da Lista : ");
   while (Px) {
   	printf("\n Valor do NO (%d) : %d", NO, Px->Valor);
      Px = Px->RL;
      NO++;
   }
   getch();
   return 1;
   // Fim da Listagem
}//Fim da função

//*********** Função RemovePrimeiro()
int RemovePrimeiro(LISTA *&Pi, LISTA *&Pf, int Valor) {
	// Define as variaveis locais
   LISTA *P;
   // Verifica lista
   if(!Pi) return 0;
   // Verifica se existe só um NO e remove
   if(Pi==Pf){
   	P = Pi;
      Pi=Pf=NULL;
      delete P;
   	return 1;
   }
   // Remove o primeiro Nó, de Lista com mais de um
   if(Pi->Valor == Valor) {
	  	P = Pi;
   	Pi = Pi->RL;
      Pi->LL = NULL;
	   P->RL = NULL;
   	delete P;
	   return 1;
   }
   return 0;
}// Fim de RemovePrimeiro()

// ********** Função RemoveFinal()
int RemoveFinal(LISTA *&Pi, LISTA *&Pf, int Valor){
	// Define as variaveis locais
   LISTA *P, *Paux;
   // Remove o último NO da Lista
   P = Pi;
	while(P != Pf) {
  	   P = P->RL;
   }
   if(P->Valor == Valor) {
      Paux = P->LL;
	   Paux->RL = NULL;
   	Pf = Paux;
   	delete P;
      return 1;
   }
   return 0;
}// Fim de RemoveFinal()

//*********** Função RemoveDaLista()
int RemoveDaLista(LISTA *&Pi, LISTA *&Pf, int Valor){
	// Define as variaveis locais
   LISTA *P, *Paux;
   // Verifica se lista vazia
   if(!Pi) return 0;
   // Remove o primeiro Nó, se Lista não vazia
   if(Pi->Valor == Valor) {
   	RemovePrimeiro(Pi, Pf, Valor);
      return 1;
   }
   // o último da Lista
	if(Valor == Pf->Valor) {
   	RemoveFinal(Pi, Pf, Valor);
      return 1;
   }
   // Remove um nó do meio da lista - entre dois nós
   P = Pi;
   while ((Valor != P->Valor) && (P->RL != NULL)) {
      P = P->RL;
   }

   // Verifica se o nó existe na lista
   if (P->RL == NULL) return 2;

   // Remove
   Paux = P->LL;
   Paux->RL = P->RL;
   P->RL->LL = Paux;

   P->RL = NULL;
   P->LL = NULL;
   free(P);
   return 1;
   // Fim das operações
}// Fim de RemoveDaLista()

//********* Função BuscaDados()
int 	BuscaNO(LISTA *&Pi, LISTA *&P, int Valor){
   // Verificando se lista existe
   if(!Pi)return 0;
	// Caso o NO buscado seja o primeiro Pdep=Pant
   P = Pi;
   while (P && P->Valor != Valor){
   	P = P->RL;
   }
   if (P)return 1;
   return 0;
}// Fim de BuscaNO()
