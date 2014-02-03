/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 5 - Entrega: 17/08/2004                                           *
*   Proposto: Operar com uma lista linear encadeada                            *
*                                                                              *
*   Nome: Cl�udio Paulo Faustino  12620            Matr�cula: 12620            *
*   Nome: Tiago Romero Garcia                      Matr�cula: 12643            *
*   Ci�ncia da Computa��o / 1� ano, 2� semestre                                *
*                                                                              *
*******************************************************************************/

#include <bios.h>
#include <conio.h>
#include <malloc.h>
#include <stdio.h>

// Defini��o da estrutura
typedef struct LISTA {
  int Valor;
  LISTA *Prox;
} LISTA;

// Defini��o de constantes
#define F1 59
#define F2 60
#define F3 61
#define F4 62
#define F5 63
#define F6 64
#define End 79

// Defini��o de prot�tipos
LISTA *AlocaNo(void);
int BuscaNo(LISTA *Pi, int Valor, LISTA *&Pant, LISTA *&Pdep);
int InsereNo(LISTA *&, LISTA *&, int);
int Menu(void);
int Relatorio(LISTA *Pi);
int RemoveNo(LISTA *&Pi, LISTA *&Pf, int);

//----------------------------------------------------------------------------//

// In�cio do programa main
void main(void)
{

  // Definindo as vari�veis necess�rias
  LISTA *Pi=NULL, *Pf=NULL, *Pant=NULL, *Pdep=NULL;
  int Opcao=0, Valor;

  // Estrutura do programa
  while (Opcao!=End) {
    Opcao = Menu();
    switch (Opcao) {
      case F1: // Insere um n� na lista
               printf("\n\n\tDigite um valor: ");
               scanf("%d", &Valor);
               InsereNo(Pi, Pf, Valor);
               break;

      case F2: // Remove um n� da lista
               printf("\n\n\tDigite um valor: ");
               scanf("%d", &Valor);
               RemoveNo(Pi, Pf, Valor);
               break;

      case F3: // Listar dados da lista
               Relatorio(Pi);
               break;

      case F4: // Busca por um n� com Info(P)
               printf("\n\n\tDigite um valor: ");
               scanf("%d", &Valor);
               BuscaNo(Pi, Valor, Pant, Pdep);
               printf("\n\n\tPant: %d, Pdep: %d\n", Pant->Valor, Pdep->Valor);
               getch();
               break;

      case F5: // Altera N�(P)
               printf("\n\n\tDigite um valor: ");
               scanf("%d", &Valor);
               //Altera(Pi, Valor);
               break;

      case End: // Fim do programa
                printf("\n\n\t\aFinalizando...\n");
                getch();
                break;

      default: // Op��o inv�lida
                printf("\n\n\t\aDigite uma opcao valida!\n");
                getch();
                break;
    } // Fim switch()
  } // Fim while()
} // Fim do main()

//----------------------------------------------------------------------------//

// Inicio fun��o AlocaNo
LISTA *AlocaNo(void) {
  LISTA *Px;
  Px = (LISTA *) calloc (1, sizeof(LISTA));
  return Px;
} // Fim de AlocaNo

//----------------------------------------------------------------------------//

// In�cio fun��o BuscaNo
int BuscaNo(LISTA *Pi, int Valor, LISTA *&Pant, LISTA *&Pdep) {

  // Declara��o das vari�veis locais
  Pant = Pdep = Pi;

  // Verificando se a lista � vazia
  if (!Pi) {
    printf("\n\n\t\aA lista esta vazia!\n");
    getch();
    return 0;
  }

  // Verifica se � o primeiro n� da lista
  if (Valor == Pi->Valor) {
    Pant = Pdep = Pi;
    return 1;
  }

  // Varre a lista e registra se achar o valor
  while ((Pdep)&&(Pdep->Valor!=Valor)) {
    Pant = Pdep;
    Pdep = Pdep->Prox;
  }

  // Fim das opera��es
  if (Pdep) return 1;

  return 0;

} // Fim de BuscaNo

//----------------------------------------------------------------------------//

// In�cio fun��o InsereNo
int InsereNo(LISTA *&Pi, LISTA *&Pf, int Valor) {

  // Defini��o das vari�veis locais
  LISTA *Pnew, *Pante, *Pdep;

  // Reserva de um novo n�
  Pnew = AlocaNo();

  // Inserindo como primeiro n� se for o caso
  if (Pi==NULL) {
    Pi = Pf = Pnew;
    Pi->Valor = Valor;
    Pi->Prox = NULL;
    return 1;
  }

  // Inserindo antes do primeiro n�
  if (Valor < Pi->Valor) {
    Pnew->Valor = Valor;
    Pnew->Prox = Pi;
    Pi = Pnew;
    return 1;
  }

  // Inserindo ap�s o �ltimo n�
  if (Valor > Pf->Valor) {
    Pnew->Valor = Valor;
    Pf->Prox = Pnew;
    Pf = Pf->Prox;
    Pf->Prox = NULL;
    return 1;
  }

  // Inserindo entre dois n�s
  Pdep = Pi;
  while (Pdep->Valor < Valor) {
    Pante = Pdep;
    Pdep = Pdep->Prox;
  }

  // Insere ap�s N�(Pante)
  Pnew->Valor = Valor;
  Pnew->Prox = Pdep;
  Pante->Prox = Pnew;
  return 1;

} // Fim de InsereNo

//----------------------------------------------------------------------------//

// In�cio fun��o Relatorio
int Relatorio(LISTA *Pi) {

  // Defini��o das vari�veis locais
  LISTA *Px;
  int No=1;

  // Verificando se a lista � vazia
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

  // Fim das opera��es
  return 1;

} // Fim de Relatorio

//----------------------------------------------------------------------------//

// Inicio fun��o Menu
int Menu(void) {

  // Defini��o das vari�veis locais
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

  // Retorna a op��o teclada 
  return Opcao;

} // Fim de Menu

//----------------------------------------------------------------------------//

// Inicio fun��o RemoveNo
int RemoveNo(LISTA *&Pi, LISTA *&Pf, int Valor) {

  // Definindo vari�veis locais
  LISTA *Pant, *Pdep, *Px;

  // Verificando se a lista � vazia
  if (!Pi) {
    printf("\n\t\aA lista esta vazia!\n");
    getch();
    return 0;
  }

  // Removendo o primero n� da lista
  if (Pi->Valor == Valor) {
    Px = Pi;
    Pi = Pi->Prox;
    Px->Prox = NULL;
    free(Px);
    return 1;
  }

  // Removendo o �ltimo n� da lista
  if (Pf->Valor==Valor){
    Pant = Pi;
    while (Pant->Prox != Pf) Pant = Pant->Prox;
    Px = Pf;
    Pf = Pant;
    Pf->Prox = NULL;
    free(Px);
    return 1;
  }

  // Removendo um n� entre dois n�s
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

  // Fim das opera��es
  return 1;

} // Fim de RemoveNo
