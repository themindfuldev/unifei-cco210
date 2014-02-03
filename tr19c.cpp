/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 19 - Entrega: 08/11/2004                                          *
*   Objetivos: Algoritmo exaustivo do percurso do cavalo de xadrez             *
*                                                                              *
*   Nome: Heron Yugo Inouye                     Matr�cula: 11877               *
*   Nome: Tiago Romero Garcia                   Matr�cula: 12643               *
*   Ci�ncia da Computa��o - Universidade Federal de Itajub�                    *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <conio.h>

//----------------------------------------------------------------------------//
// Declara��es de constantes

const int Size = 8;
int dx[Size+1] = {0,2,1,-1,-2,-2,-1,1,2},
    dy[Size+1] = {0,1,2,2,1,-1,-2,-2,-1},
    h[Size+1][Size+1],
    n;

//----------------------------------------------------------------------------//
// Prot�tipos de fun��es

void Print();
void TryNextMove(int i, int x, int y, bool &s);

//----------------------------------------------------------------------------//

// Fun��o main: corpo do programa
void main()
{
	// Decara��o de vari�veis
	int i, j;
	bool q;

	printf("\n     19o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
	printf("\n     Nome: Heron Yugo Inouye    -  Matricula: 11877  -  CCO 2003");
	printf("\n     Nome: Tiago Romero Garcia  -  Matricula: 12643  -  CCO 2004");
   printf("\n\n\n\tTamanho do tabuleiro (3-8): ");
   scanf("%d", &n);

	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++)
			h[i][j] = 0;

	printf("\n\tPosicao inicial do cavalo: p0 = (x0, y0)\n\n\tCoordenada x0: ");
   scanf("%d", &i);
   printf("\tCoordenava y0: ");
   scanf("%d", &j);
	h[i][j] = 1;
   TryNextMove(2, i, j, q);

   if (q) Print();
   else printf("\n\n\tCaminho nao encontrado!\n");
   printf("\t[Pressione qualquer tecla para terminar...]\n");
   getch();

} // Fim de main

//----------------------------------------------------------------------------//

// Fun��o Print: imprime as jogadas
void Print()
{
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
			printf("\t%d", h[i][j]);
		printf("\n");
	} // Fim de if
	printf("\n\n");

} // Fim de Print

//----------------------------------------------------------------------------//

// Fun��o TryNextMove: determina recursivamente a posi��o do cavalo
void TryNextMove(int i, int x, int y, bool &s)
{
   // Declara��o de vari�veis
	int u, v, k;
	bool sucesso;

	k = 0;
	sucesso = false;
	do
	{
		k++;
		u = x + dx[k];
		v = y + dy[k];
		if (1<=u && u<=n && 1<=v && v<=n && h[u][v]==0)
		{
			h[u][v] = i;
			if (i < n*n)
			{
				TryNextMove(i+1, u, v, sucesso);
				if (!sucesso)
					h[u][v] = 0;
			} // Fim de if
			else
				sucesso = true;
		} // fim de if
	} while (!sucesso && k < Size);
	s = sucesso;
   
} // Fim de TryNextMove

