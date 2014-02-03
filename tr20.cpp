/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 20 - Entrega: 08/11/2004                                          *
*   Objetivos: Algoritmo recursivo do problema das torres de Hanoi             *
*                                                                              *
*   Nome: Heron Yugo Inouye                     Matr�cula: 11877               *
*   Nome: Tiago Romero Garcia                   Matr�cula: 12643               *
*   Ci�ncia da Computa��o - Universidade Federal de Itajub�                    *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <conio.h>

//----------------------------------------------------------------------------//
// Prot�tipos de fun��es

void Torres(int n, char origem, char destino, char auxiliar);

//----------------------------------------------------------------------------//

// Fun��o main: corpo do programa
void main()
{
	int n;

	printf("\n     20o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
	printf("\n     Nome: Heron Yugo Inouye    -  Matricula: 11877  -  CCO 2003");
	printf("\n     Nome: Tiago Romero Garcia  -  Matricula: 12643  -  CCO 2004");
   printf("\n\n\n\tDigite o numero de pinos: ");
   scanf("%d", &n);
   printf("\n");
   Torres(n, 'A', 'C', 'B');
   printf("\n");
   getch();

} // Fim de main

//----------------------------------------------------------------------------//

// Fun��o Torres
void Torres(int n, char origem, char destino, char auxiliar)
{
	// Se existir somente um disco, fa�a o movimento e retorne
   if (n == 1)
   {
   	printf("\n\tMover disco %d da estaca %c para a estaca %c", n, origem, destino);
      return;
	} // Fim de if

   // Move os n-1 discos de A p/ B usando C como auxiliar
   Torres(n-1, origem, auxiliar, destino);

   // Move o ultimo disco de A p/ C
  	printf("\n\tMover disco %d da estaca %c para a estaca %c", n, origem, destino);

   // Move n-1 discos de B p/ C usando a como auxiliar
   Torres(n-1, auxiliar, destino, origem);

} // Fim de Torres
