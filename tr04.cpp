/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 5 - Entrega: 17/08/2004                                           *
*   Proposto: Operar com uma lista linear encadeada                            *
*                                                                              *
*   Nome: Cláudio Paulo Faustino  12620            Matrícula: 12620            *
*   Nome: Tiago Romero Garcia                      Matrícula: 12643            *
*   Ciência da Computação / 1° ano, 2° semestre                                *
*                                                                              *
*******************************************************************************/

#include <bios.h>
#include <conio.h>
#include <malloc.h>
#include <stdio.h>

// Definição da estrutura
typedef struct LISTA {
  int Valor;
  LISTA *Prox;
} LISTA;

// Definição de constantes
#define F1 59
#define F2 60
#define F3 61
#define F4 62
#define F5 63
#define F6 64
#define End 79

// Definição de protótipos
LISTA *AlocaNo(void);
int BuscaNo(LISTA *Pi, int Valor, LISTA *&Pant, LISTA *&Pdep);
int InsereNo(LISTA *&, LISTA *&, int);
int Menu(void);
int Relatorio(LISTA *Pi);
int RemoveNo(LISTA *&Pi, LISTA *&Pf, int);

//----------------------------------------------------------------------------//

// Início do programa main
void main(void)
{

  // Definindo as variáveis necessárias
  LISTA *Pi=NULL, *Pf=NULL, *Pant=NULL, *Pdep=NULL;
  int Opcao=0, Valor;

  // Estrutura do programa
  while (Opcao!=End) {
    Opcao = Menu();
    switch (Opcao) {
      case F1: // Insere um nó na lista
               printf("\n\n\tDigite um valor: ");
               scanf("%d", &Valor);
               InsereNo(Pi, Pf, Valor);
               break;

      case F2: // Remove um nó da lista
               printf("\n\n\tDigite um valor: ");
               scanf("%d", &Valor);
               RemoveNo(Pi, Pf, Valor);
               break;

      case F3: // Listar dados da lista
               Relatorio(Pi);
               break;

      case F4: // Busca por um nó com Info(P)
               printf("\n\n\tDigite um valor: ");
               scanf("%d", &Valor);
               BuscaNo(Pi, Valor, Pant, Pdep);
               printf("\n\n\tPant: %d, Pdep: %d\n", Pant->Valor, Pdep->Valor);
               getch();
               break;

      case F5: // Altera Nó(P)
               printf("\n\n\tDigite um valor: ");
               scanf("%d", &Valor);
               //Altera(Pi, Valor);
               break;

      case End: // Fim do programa
                printf("\n\n\t\aFinalizando...\n");
                getch();
                break;

      default: // Opção inválida
                printf("\n\n\t\aDigite uma opcao valida!\n");
                getch();
                break;
    } // Fim switch()
  } // Fim while()
} // Fim do main()

//----------------------------------------------------------------------------//

// Inicio função AlocaNo
LISTA *AlocaNo(void) {
  LISTA *Px;
  Px = (LISTA *) calloc (1, sizeof(LISTA));
  return Px;
} // Fim de AlocaNo

//----------------------------------------------------------------------------//

// Início função BuscaNo
int BuscaNo(LISTA *Pi, int Valor, LISTA *&Pant, LISTA *&Pdep) {

  // Declaração das variáveis locais
  Pant = Pdep = Pi;

  // Verificando se a lista é vazia
  if (!Pi) {
    printf("\n\n\t\aA lista esta vazia!\n");
    getch();
    return 0;
  }

  // Verifica se é o primeiro nó da lista
  if (Valor == Pi->Valor) {
    Pant = Pdep = Pi;
    return 1;
  }

  // Varre a lista e registra se achar o valor
  while ((Pdep)&&(Pdep->Valor!=Valor)) {
    Pant = Pdep;
    Pdep = Pdep->Prox;
  }

  // Fim das operações
  if (Pdep) return 1;

  return 0;

} // Fim de BuscaNo

//----------------------------------------------------------------------------//

// Início função InsereNo
int InsereNo(LISTA *&Pi, LISTA *&Pf, int Valor) {

  // Definição das variáveis locais
  LISTA *Pnew, *Pante, *Pdep;

  // Reserva de um novo nó
  Pnew = AlocaNo();

  // Inserindo como primeiro nó se for o caso
  if (Pi==NULL) {
    Pi = Pf = Pnew;
    Pi->Valor = Valor;
    Pi->Prox = NULL;
    return 1;
  }

  // Inserindo antes do primeiro nó
  if (Valor < Pi->Valor) {
    Pnew->Valor = Valor;
    Pnew->Prox = Pi;
    Pi = Pnew;
    return 1;
  }

  // Inserindo após o último nó
  if (Valor > Pf->Valor) {
    Pnew->Valor = Valor;
    Pf->Prox = Pnew;
    Pf = Pf->Prox;
    Pf->Prox = NULL;
    return 1;
  }

  // Inserindo entre dois nós
  Pdep = Pi;
  while (Pdep->Valor < Valor) {
    Pante = Pdep;
    Pdep = Pdep->Prox;
  }

  // Insere após Nó(Pante)
  Pnew->Valor = Valor;
  Pnew->Prox = Pdep;
  Pante->Prox = Pnew;
  return 1;

} // Fim de InsereNo

//----------------------------------------------------------------------------//

// Início função Relatorio
int Relatorio(LISTA *Pi) {

  // Definição das variáveis locais
  LISTA *Px;
  int No=1;

  // Verificando se a lista é vazia
  if (!Pi) {
    printf("\n\t\aA lista esta vazia!\n");
    getch();
    return 0;
  }

  // Listando dados
  Px = Pi;
  printf("\n\n");
  while (Px) {
    printf("\tDado do no(%d) = %d\n", No, Px->Valor);
    No++;
    Px = Px->Prox;
  }
  getch();

  // Fim das operações
  return 1;

} // Fim de Relatorio

//----------------------------------------------------------------------------//

// Inicio função Menu
int Menu(void) {

  // Definição das variáveis locais
  int Opcao;

  // Impressao do menu
  clrscr();
  printf("\n     3o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
  printf("\n     Nome: Claudio Paulo Faustino - Matricula: 12620 - CCO 2004");
  printf("\n     Nome: Tiago Romero Garcia    - Matricula: 12643 - CCO 2004\n\n");
  printf("\n\t**Escolha uma das operacoes:\n");
  printf("\n\t  F1: Insercao de um novo no.");
  printf("\n\t  F2: Remocao de um no.");
  printf("\n\t  F3: Listagem dos dados da lista.");
  printf("\n\t  F4: Localizar um no.");
  printf("\n\t  F5: Alterar os dados de um no.");
  printf("\n\t  End: Finalizar.\n");
  printf("\n\t\aEscolha uma operacao: ");
  Opcao = bioskey(0) >> 8;

  // Retorna a opção teclada 
  return Opcao;

} // Fim de Menu

//----------------------------------------------------------------------------//

// Inicio função RemoveNo
int RemoveNo(LISTA *&Pi, LISTA *&Pf, int Valor) {

  // Definindo variáveis locais
  LISTA *Pant, *Pdep, *Px;

  // Verificando se a lista é vazia
  if (!Pi) {
    printf("\n\t\aA lista esta vazia!\n");
    getch();
    return 0;
  }

  // Removendo o primero nó da lista
  if (Pi->Valor == Valor) {
    Px = Pi;
    Pi = Pi->Prox;
    Px->Prox = NULL;
    free(Px);
    return 1;
  }

  // Removendo o último nó da lista
  if (Pf->Valor==Valor){
    Pant = Pi;
    while (Pant->Prox != Pf) Pant = Pant->Prox;
    Px = Pf;
    Pf = Pant;
    Pf->Prox = NULL;
    free(Px);
    return 1;
  }

  // Removendo um nó entre dois nós
  Pdep = Pi;
  while((Pdep->Valor != Valor)&&(Pdep)) {
    Pant = Pdep;
    Pdep = Pdep->Prox;
  } // Fim da busca

  // Verificando se o valor esta na lista
  if (Pdep == NULL) {
    printf("\n\t\aO valor nao esta na lista!\n");
    getch();
    return 0;
  }

  // Agora remove o No(Pdep)
  Pant->Prox = Pdep->Prox;
  Pdep->Prox = NULL;
  free(Pdep);

  // Fim das operações
  return 1;

} // Fim de RemoveNo
