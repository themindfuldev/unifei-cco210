/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 18 - Entrega: 26/10/2004                                          *
*   Objetivos: Exerc�cios 3.5.3.1 ao 3.5.3.6 da apostila                       *
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
#define MAX 10

//----------------------------------------------------------------------------//

// Prot�tipos de fun��es
int   Analise(char *, int, char);
int   MDC(int, int);
float Media(float *, int);
int   Menu(void);
float Raiz(float, float, float);
int   Soma(int *, int);

//----------------------------------------------------------------------------//

// Fun��o Main: Estrutura do programa
void main(void)
{
	// Declara��o de vari�veis
   char vetc[MAX], pesq;
	float x, r, tol, vetf[MAX];
   int i, op, m, n, pos, veti[MAX];

   do
   {
   	op = Menu();
   	switch(op)
      {
      	case 1:  // Procura de caracter em vetor ordenado crescentemente
                  for (i=0; i<MAX; i++)
                  {
   						printf("\tDigite um caracter: ");
					   	scanf("%s", &vetc[i]);
                     if ((i>0)&&(vetc[i]<=vetc[i-1])) // Verifica se o vetor � crescente para i>0
                     {
   							printf("\a\n\tDigite um caracter maior que o anterior!\n\t[Pressione qualquer tecla para continuar...]\n\n");
			               getch();
                        i--;
                     } // Fim de if
                  } // Fim de for
                  printf("\n\n\tDigite um caracter para pesquisa: ");
					   scanf("%s", &pesq);
                  pos = Analise(vetc, -1, pesq);
                  if(pos<0) printf("\a\n\n\tO caracter %c nao se encontra no vetor!\n\t[Pressione qualquer tecla para continuar...]\n", pesq);
                  else printf("\a\n\n\tO caracter %c se encontra na posicao %d!\n\t[Pressione qualquer tecla para continuar...]\n", pesq, pos);
		            getch();
                  break;

      	case 2:  // Soma dos elementos de um vetor de inteiros
                  for (i=0; i<MAX; i++)
                  {
   						printf("\tDigite um valor: ");
					   	scanf("%d", &veti[i]);
                  } // Fim de for
						printf("\a\n\tA soma dos elementos do vetor = %d\n\t[Pressione qualquer tecla para continuar...]\n", Soma(veti, -1));
		            getch();
                  break;

      	case 3:  // Media aritmetica dos elementos de um vetor de reais
                  for (i=0; i<MAX; i++)
                  {
   						printf("\tDigite um valor: ");
					   	scanf("%f", &vetf[i]);
                  } // Fim de for
						printf("\a\n\tA media aritmetica dos elementos do vetor = %2.2f\n\t[Pressione qualquer tecla para continuar...]\n", Media(vetf, -1));
		            getch();
                  break;

      	case 4:  // Calculo do MDC de dois inteiros
   					printf("\tDigite um valor: ");
					   scanf("%d", &m);
					   printf("\tDigite outro valor: ");
					   scanf("%d", &n);
					   printf("\n\tO mdc de %d e %d = %d\n", m, n, MDC(m, n));
   					printf("\n\t[Pressione qualquer tecla para continuar...]\n");
					   getch();
                  break;

      	case 5:  // Procura de caracter em vetor n�o-ordenado
                  for (i=0; i<MAX; i++)
                  {
   						printf("\tDigite um caracter: ");
					   	scanf("%s", &vetc[i]);
                  } // Fim de for
                  printf("\n\n\tDigite um caracter para pesquisa: ");
					   scanf("%s", &pesq);
                  pos = Analise(vetc, -1, pesq);
                  if(pos<0) printf("\a\n\n\tO caracter %c nao se encontra no vetor!\n\t[Pressione qualquer tecla para continuar...]\n", pesq);
                  else printf("\a\n\n\tO caracter %c se encontra na posicao %d!\n\t[Pressione qualquer tecla para continuar...]\n", pesq, pos);
		            getch();
                  break;

      	case 6:  // Calculo da raiz quadrada aproximada de um real
   					printf("\tDigite o numero para se calcular a raiz aproximada: ");
   					scanf("%f", &x);
   					printf("\tDigite uma aproximacao do resultado: ");
   					scanf("%f", &r);
   					printf("\tDigite a tolerancia: ");
   					scanf("%f", &tol);
				   	printf("\n\tA raiz aproximada de %2.2f = %2.2f", x, Raiz(x, r, tol));
   					printf("\n\t[Pressione qualquer tecla para continuar...]\n");
				   	getch();
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

// Fun��o Analise: Pesquisa um caracter no vetor recursivamente
int Analise(char vetc[MAX], int i, char pesq)
{
	// Declara��o de vari�veis
	int ret;

	// Incremento da posi��o do vetor
   i++;

	// Se n�o encontrar o caracter no vetor
	if (i>=MAX) return -1;

   // Se o caracter atual for o procurado
   if (vetc[i]==pesq) return i;

   // Procurando recursivamente
   ret = Analise(vetc, i, pesq);

   return ret;

} // Fim de Analise

//----------------------------------------------------------------------------//

// Fun��o MDC: Calcula o MDC de dois n�meros recursivamente
int MDC(int m, int n)
{
   // Calculando recursivamente
	if ((m%n)==0) return n;

   return MDC(n, m%n);
} // Fim de MDC

//----------------------------------------------------------------------------//

// Fun��o Media: Calcula a media aritim�tica recursivamente
float Media(float vetf[MAX], int i)
{
   // Declara��o de vari�veis
	float tot;

	// Incremento da posi��o do vetor
   i++;

	// Se chegar ao fim do vetor
   if (i>=MAX) return 0;

   // Calculando recursivamente
   tot = vetf[i]/MAX + Media(vetf, i);

   return tot;
} // Fim de Media

//----------------------------------------------------------------------------//

// Fun��o Menu: Imprime o menu
int Menu(void)
{
	int op;

	clrscr();
	printf("\n     18o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
	printf("\n     Nome: Heron Yugo Inouye    -  Matricula: 11877  -  CCO 2003");
	printf("\n     Nome: Tiago Romero Garcia  -  Matricula: 12643  -  CCO 2004");
   printf("\n\n\n\tMenu de Opcoes:");
   printf("\n\t  1. Procura de caracter em vetor ordenado crescentemente");
   printf("\n\t  2. Soma dos elementos de um vetor de inteiros");
   printf("\n\t  3. Media aritmetica dos elementos de um vetor de reais");
   printf("\n\t  4. Calculo do MDC de dois inteiros");
   printf("\n\t  5. Procura de caracter em vetor nao-ordenado");
   printf("\n\t  6. Calculo da raiz quadrada aproximada de um real");
   printf("\n\t  0. Sair");
   printf("\n\n\tDigite a opcao desejada: ");
   scanf("%d", &op);
   printf("\n\n");

   return op;
} // Fim de Menu

//----------------------------------------------------------------------------//

// Fun��o Raiz: Calcula a raiz quadrada de um n�mero recursivamente
float Raiz(float x, float r, float tol)
{
   // Calculando recursivamente
	if (abs(x-r*r) <= tol) return r;

   return (Raiz(x, (x/r+r)/2, tol));
} // Fim de Raiz

//----------------------------------------------------------------------------//

// Fun��o Soma: Calcula a soma recursivamente
int Soma(int veti[MAX], int i)
{
	// Declara��o de vari�veis
	int tot;

	// Incremento da posi��o do vetor
   i++;

	// Se chegar ao fim do vetor
   if (i>=MAX) return 0;

   // Calculando recursivamente
   tot = veti[i] + Soma(veti, i);

   return tot;
} // Fim de Soma

