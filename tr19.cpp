/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 19 - Entrega: 08/11/2004                                          *
*   Objetivos: Algoritmo exaustivo do percurso do cavalo de xadrez             *
*                                                                              *
*   Nome: Heron Yugo Inouye                     Matrícula: 11877               *
*   Nome: Tiago Romero Garcia                   Matrícula: 12643               *
*   Ciência da Computação - Universidade Federal de Itajubá                    *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <conio.h>

//----------------------------------------------------------------------------//
// Declarações de constantes

const int Size = 8;

//----------------------------------------------------------------------------//
// Protótipos de funções

void Print(int n, int h[Size+1][Size+1]);
void TryNextMove(int i, int x, int y, bool &s, int n, int dx[Size+1], int dy[Size+1], int h[Size+1][Size+1]);

//----------------------------------------------------------------------------//

// Função main: corpo do programa
void main()
{
	// Decaração de variáveis
	bool q;
	int dx[Size+1] = {0,2,1,-1,-2,-2,-1,1,2},
   	 dy[Size+1] = {0,1,2,2,1,-1,-2,-2,-1},
   	 h[Size+1][Size+1],
   	 n, i, j;

	printf("\n     19o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
	printf("\n     Nome: Heron Yugo Inouye    -  Matricula: 11877  -  CCO 2003");
	printf("\n     Nome: Tiago Romero Garcia  -  Matricula: 12643  -  CCO 2004\n\n");
   do
   {
   	printf("\n\tTamanho do tabuleiro (3-%d): ", Size);
   	scanf("%d", &n);
      if ((n<3)||(n>8))
      {
      	printf("\n\tTamanho invalido!\n\t[Pressione qualquer tecla para continuar...]\n");
         getch();
      }
   } while ((n<3)||(n>8));

	for (i=1; i<=n; i++)
		for (j=1; j<=n; j++)
			h[i][j] = 0;

   printf("\n\n\tPosicao inicial do cavalo: p0 = (x0, y0)\n");
   do
   {
		printf("\n\t  Coordenada x0: ");
	   scanf("%d", &i);
      if ((i>=n)||(i<0))
      {
      	printf("\n\tCoordenada invalida!\n\t[Pressione qualquer tecla para continuar...]\n");
         getch();
      }
   } while ((i>=n)||(i<0));
   do
   {
   	printf("\n\t  Coordenada y0: ");
   	scanf("%d", &j);
      if ((j>=n)||(j<0))
      {
      	printf("\n\tCoordenada invalida!\n\t[Pressione qualquer tecla para continuar...]\n");
         getch();
      }
   } while ((j>=n)||(j<0));
   i++; j++;
	h[i][j] = 1;
   TryNextMove(2, i, j, q, n, dx, dy, h);

   if (q) Print(n, h);
   else printf("\n\n\tCaminho nao encontrado!\n");
   printf("\t[Pressione qualquer tecla para terminar...]\n");
   getch();

} // Fim de main

//----------------------------------------------------------------------------//

// Função Print: imprime as jogadas
void Print(int n, int h[Size+1][Size+1])
{

   printf("\n\n\tPassos do cavalo:\n\n");
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
			printf("\t  %d", h[i][j]);
		printf("\n");
	} // Fim de if
	printf("\n");

} // Fim de Print

//----------------------------------------------------------------------------//

// Função TryNextMove: determina recursivamente a próxima posição do cavalo
void TryNextMove(int i, int x, int y, bool &s, int n, int dx[Size+1], int dy[Size+1], int h[Size+1][Size+1])
{
   // Declaração de variáveis
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
			if (i < n*n-1)
			{
				TryNextMove(i+1, u, v, sucesso, n, dx, dy, h);
				if (!sucesso)
					h[u][v] = 0;
			} // Fim de if
			else
				sucesso = true;
		} // Fim de if
	} while (!sucesso && k < Size);
	s = sucesso;

} // Fim de TryNextMove

