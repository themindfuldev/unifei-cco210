#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

float raiz(float, float, float);

void main(void)
{
	float x, r, tol;

   printf("\n\tDigite x: ");
   scanf("%f", &x);
   printf("\tDigite r: ");
   scanf("%f", &r);
   printf("\tDigite tol: ");
   scanf("%f", &tol);

   printf("\n\tA raiz aproximada de %2.2f = %2.2f\n", x, raiz(x, r, tol));
   getch();
}

float raiz(float x, float r, float tol)
{
	if (abs(x-r*r) <= tol) return r;
   return (raiz(x, (x/r+r)/2, tol));
}
