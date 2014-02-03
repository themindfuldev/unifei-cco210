#include <stdio.h>
#include <conio.h>

#define MAX 3

int  Cavalo(int tabuleiro[MAX][MAX], int modos[MAX*MAX], int x, int y, int passos);
bool Mover(int &x, int &y);

void main()
{
	int tabuleiro[MAX][MAX];
   int modos[MAX*MAX];

	for (int i=0; i<MAX; i++)
   	for (int j=0; j<MAX; j++)
      	tabuleiro[i][j] = 0;

   for (int i=0; i<MAX*MAX-1; i++)
   	modos[i] = 1;

   Cavalo(tabuleiro, 0, 0, 1);

} // Fim de main

int Cavalo(int tabuleiro[MAX][MAX], int modos[MAX*MAX], int x, int y, int passos)
{
	if (tabuleiro[x][y] == 0)
   	tabuleiro[x][y] = passos;
   else



   if (passos >= MAX*MAX-1) return 1;

   while (!Mover(x, y, modos[passos]))
   	modos[passos]++;

	passos++;
   Cavalo(tabuleiro, modos, x, y, passos);

} // Fim de Cavalo

bool Mover(int &x, int &y, int modo)
{
	int ret;

	switch(modo)
   {
   	case '1':
      			if (x+2<MAX && y-1>=0)
               {
                 x += 2;
                 y -= 1;
                 ret = 1;
               }
               else ret = 0;
               break;

   	case '2':
      			if (x+1<MAX && y-2>=0)
               {
                 x += 1;
                 y -= 2;
                 ret = 1;
               }
               else ret = 0;
               break;

   	case '3':
      			if (x-2<MAX && y-1>=0)
               {
                 x -= 2;
                 y += 1;
                 ret = 1;
               }
               else ret = 0;
               break;

   	case '4':
      			if (x-1<MAX && y-2>=0)
               {
                 x -= 1;
                 y += 2;
                 ret = 1;
               }
               else ret = 0;
               break;

   	case '5':
      			if (x+2<MAX && y-1>=0)
               {
                 x += 2;
                 y -= 1;
                 ret = 1;
               }
               else ret = 0;
               break;

   	case '2':
      			if (x+1<MAX && y-2>=0)
               {
                 x += 1;
                 y -= 2;
                 ret = 1;
               }
               else ret = 0;
               break;

   	case '3':
      			if (x-2<MAX && y-1>=0)
               {
                 x -= 2;
                 y += 1;
                 ret = 1;
               }
               else ret = 0;
               break;

   	case '4':
      			if (x-1<MAX && y-2>=0)
               {
                 x -= 1;
                 y += 2;
                 ret = 1;
               }
               else ret = 0;
               break;
   }

   return ret;

} // Fim de Mover