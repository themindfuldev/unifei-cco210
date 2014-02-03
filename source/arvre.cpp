#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>
#define max 20

//----------------------------------------------------------------------------//
// declaração de estruturas
typedef struct NO{
	NO *LL;
   char Nome[20];
   long Endereco;
   NO *RL;
}NO;

typedef struct PILHA{
	int topo,base;
   NO *pilha[max];
}PILHA;

struct FILA
{
   NO *fila[max];
   int topo,base,p,u;

};

//----------------------------------------------------------------------------//
int Menu(void);
NO *sInsereNO(NO *&raiz, char nome[20]);
NO *ReservaNO(void);
int BuscaNO(NO *r, char pesq[20]);
void sPercursoPreOrdem(NO *r);
int Push(PILHA &Pilha, NO *p);
NO *Pop(PILHA &Pilha);
int PercursoOrdemSimetrica(NO *r);

//----------------------------------------------------------------------------//

void main (void)
{
  int op, qtde,i,pesq;
  char nome[20];
  NO *raiz;

  raiz=NULL;
  do
   {
     op = Menu();
     switch(op)
     {
        case 1 : // Cria árvore por sInsereNO()
                 printf("\nDigite o numero de elementos a serem inseridos:");
                 scanf("%d",&qtde);
                 for(i=0;i<qtde;i++)
                 {
                    printf("\nDigite o nome do %d elemento:",i+1);
                    scanf(" %[^\n]",&nome);
                    raiz = sInsereNO(raiz,nome);
                 }
                 break;

        case 3 : //Busca um no com a funcao BuscaNO()
                 printf("\nDigite um nome para pesquisa:");
                 scanf(" %[^\n]",&nome);
                 pesq = BuscaNO(raiz,nome);
                 if(!pesq)
                 {
                    printf("\nO nome %s NAO consta na arvore!!!",nome);
                    getch();
                 }
                 else
                 {
                    printf("\nO nome %s consta na arvore!!!",nome);
                    getch();
                 }

                 break;

        case 5 : //Lista os nos com a funcao sPercursoPreOrdem
                 sPercursoPreOrdem(raiz);
                 getch();
                 break;

		  case 7 : //Lista os nos com a funcao sPercursoPreOrdem
                 PercursoOrdemSimetrica(raiz);
                 getch();

                 break;

		  case 9 : //Lista os nos com a funcao sPercursoPreOrdem
                 //PercursoEmLargura(raiz);
                 getch();

                 break;

        case 0 ://
        				printf("\nFinalizando o programa...");
        				getch();
                  break;

		  default : printf("\nOpcao Invalida");
        				getch();
         			break;
     }//fim do switch
   }while(op);//fim do do
}//fim da funcao main


//----------------------------------------------------------------------------//

int Push(PILHA &Pilha, NO *p){
	//Verificando overflow
   if(Pilha.topo>=max) return -1;
   Pilha.topo++;
   Pilha.pilha[Pilha.topo]= p;
   return 1;
}//Fim Push()

//----------------------------------------------------------------------------//

NO *Pop(PILHA &Pilha){

   NO *p;
	//Verificando underflow
   if(Pilha.topo<=Pilha.base) return 0;
   p=Pilha.pilha[Pilha.topo];
   Pilha.topo--;
   return p;
}//Fim Pop
//----------------------------------------------------------------------------//

// Função Menu: Imprime o menu
int Menu(void)
{
	int op;

	clrscr();
	printf("\n     Trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
	printf("\n     Nome: Heron Yugo Inouye    -  Matricula: 11877  -  CCO 2003");
	printf("\n     Nome: Tiago Romero Garcia  -  Matricula: 12643  -  CCO 2004");
   printf("\n\n\n\tMenu de Opcoes:");
   printf("\n\t  1. Cria árvore por sInsereNO()");
   printf("\n\t  3. Busca informacao X com a funcao BuscaNO()");
   printf("\n\t  5. Lista as informacoes com a funcao sPercursoPreOrdem");
   printf("\n\t  7. Listar as informacoes com a funcao PercursoOrdemSimetrica");
   printf("\n\t  9. Listar as informacoes com a funcao PercursoEmLargura");
   printf("\n\t  0. Sair");
   printf("\n\n\tDigite a opcao desejada: ");
   scanf("%d", &op);
   printf("\n\n");

   return op;
} // Fim de Menu

//----------------------------------------------------------------------------//
NO *ReservaNO(void)
{
	NO *p;

   p=(NO *)calloc(1,sizeof(NO));
   return p;
}


//----------------------------------------------------------------------------//

NO *sInsereNO(NO *&raiz, char nome[20])
{

	NO *Px,*p,*q;

   //reservando memoria para um novo no
   Px=ReservaNO();
   if(!Px) return 0;

   strcpy(Px->Nome,nome);

   //inserindo no se a arvore for vazia
   if(!raiz)
   {
   	raiz=Px;
      return raiz;
   }

   //inserindo em arvore nao vazia
   q=raiz;
   while(q)
   {
   	p=q;
      if(strcmp(nome,p->Nome)<0)
      	q=p->LL;
      else
      	q=p->RL;
   }

   //insere como novo nó folha e finaliza
   if(strcmp(nome,p->Nome)<0)
   	p->LL=Px;
   else
   	p->RL=Px;

   return raiz;
}
//----------------------------------------------------------------------------//

int BuscaNO(NO *r, char nome[20])
{
   int pesq;
	//verificando se arvore está vazia
   if(!r)
   	return 0;

   //verificando se encontrou a informacao
   if(strcmp(r->Nome,nome)==0)
   	return 1;

   //fazendo as pesquisae pelas subarvores da esquerda e direita
   if(strcmp(nome,r->Nome)<0)
   	pesq=BuscaNO(r->LL,nome);
   if(strcmp(nome,r->Nome)>0)
   	pesq=BuscaNO(r->RL,nome);

   return pesq;


}

//----------------------------------------------------------------------------//

void sPercursoPreOrdem(NO *r)
{
	NO *p, *q;
   int v,ok;
   PILHA Pilha;

   Pilha.base=0;
   Pilha.topo=0;
   v=1;
   q=r;
   while(v)
   {
   	while(q!=0)
      {
      	p=q;
         printf("\nVisitando o no: %s", p->Nome);
         ok=Push(Pilha,p);
         if(ok<0)
         {
         	printf("\nOverflow!!!");
            getch();
         	return;
         }
         q=p->LL;
      }//fim while
      q=Pop(Pilha);
      while((q->RL!=0)&&(Pilha.topo))
      	q=Pop(Pilha);
      if(!Pilha.topo)
      	v=0;
      q=q->RL;
   }//fim while
}

//----------------------------------------------------------------------------//

int PercursoOrdemSimetrica(NO *r)
{
	//verificando se a arvore esta vazia
   if(!r)
   	return 0;

   //caminhando na sub arvore esquerda de R
   PercursoOrdemSimetrica(r->LL);
   printf("\nVisitando o no : %s", r->Nome);

   //caminhando na sub arvore direita de R
   PercursoOrdemSimetrica(r->RL);

}

//----------------------------------------------------------------------------//

void PercursoEmLargura(NO *r)
{
   int i;
	FILA Fila;
   NO *t;

   Fila.p =  0;
   Fila.u = -1;

   if(r)
   {
   	Fila.fila[Fila.u]=r;
      while(Fila.p!=Fila.u)
      {
			t=Fila.fila[Fila.p];
         printf("\n Visitando o no : %s", t->Nome);
         for(i=0;i<h;i++)
         {
         	r=BuscaSubArvore(r,i);
            if(!r)
            	Fila.fila[Fila.u]=r
         }

      }
   }
}

