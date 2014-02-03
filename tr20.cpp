/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 20 - Entrega: 08/11/2004                                          *
*   Objetivos: Algoritmo recursivo do problema das torres de Hanoi             *
*                                                                              *
*   Nome: Heron Yugo Inouye                     Matrícula: 11877               *
*   Nome: Tiago Romero Garcia                   Matrícula: 12643               *
*   Ciência da Computação - Universidade Federal de Itajubá                    *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <conio.h>

//----------------------------------------------------------------------------//
// Protótipos de funções

void Torres(int n, char origem, char destino, char auxiliar);

//----------------------------------------------------------------------------//

// Função main: corpo do programa
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

// Função Torres
void Torres(int n, char origem, char destino, char auxiliar)
{
	// Se existir somente um disco, faça o movimento e retorne
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
