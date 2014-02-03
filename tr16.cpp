#include <stdio.h>
#include <conio.h>

int mdc(int, int);

void main(void)
{
	int m, n;

   printf("\n\tDigite m: ");
   scanf("%d", &m);
   printf("\tDigite n: ");
   scanf("%d", &n);

   printf("\n\tO mdc de %d e %d = %d\n", m, n, mdc(m,n));
   getch();
}

int mdc(int m, int n)
{
	if ((m%n)==0) return n;
   return mdc(n, m%n);
}