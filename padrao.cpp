/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 21 - Entrega: 18/11/2004                                          *
*   Objetivos: Lista de exerc�cio sobre �rvores bin�rias                       *
*                                                                              *
*   Nome: Heron Yugo Inouye                     Matr�cula: 11877               *
*   Nome: Tiago Romero Garcia                   Matr�cula: 12643               *
*   Ci�ncia da Computa��o - Universidade Federal de Itajub�                    *
*                                                                              *
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

//----------------------------------------------------------------------------//

// Defini��o de constantes
//#define MAX 10

//----------------------------------------------------------------------------//

// Prot�tipos de fun��es
int Menu(void);

//----------------------------------------------------------------------------//

// Fun��o Main: Estrutura do programa
void main(void)
{
	// Declara��o de vari�veis
   int op;

   do
   {
   	op = Menu();
   	switch(op)
      {
      	case 1:  //
                  break;

      	case 2:  //
                  break;

      	case 3:  //
                  break;

      	case 4:  //
                  break;

      	case 5:  //
                  break;

      	case 6:  //
                  break;

      	case 7:  //
                  break;

      	case 8:  //
                  break;

      	case 9:  //
                  break;

         case 0:  // Sair
   					printf("\tFinalizando...\n\t[Pressione qualquer tecla para continuar...]\n");
                  getch();
         			break;

         default: // Op��o inv�lida
   					printf("\a\tOpcao invalida!\n\t[Pressione qualquer tecla para continuar...]\n");
                  getch();
         			break;
      } // Fim de switch
   } while(op);
} // Fim de main

//----------------------------------------------------------------------------//

// Fun��o Menu: Imprime o menu
int Menu(void)
{
	int op;

	clrscr();
	printf("\n     21o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
	printf("\n     Nome: Heron Yugo Inouye    -  Matricula: 11877  -  CCO 2003");
	printf("\n     Nome: Tiago Romero Garcia  -  Matricula: 12643  -  CCO 2004");
   printf("\n\n\n\tMenu de Opcoes:");
   printf("\n\t  1. ");
   printf("\n\t  2. ");
   printf("\n\t  3. ");
   printf("\n\t  4. ");
   printf("\n\t  5. ");
   printf("\n\t  6. ");
   printf("\n\t  7. ");
   printf("\n\t  8. ");
   printf("\n\t  9. ");
   printf("\n\t  0. Sair");
   printf("\n\n\tDigite a opcao desejada: ");
   scanf("%d", &op);
   printf("\n\n");

   return op;
} // Fim de Menu

