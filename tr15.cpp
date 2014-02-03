/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 15 - Entrega: 22/10/2004                                          *
*   Objetivos: Operar com transforma��o de express�es infixas para prefixa e   *
*              posfixa, avalia��o de express�es escritas nessas formas e       *
*              gera��o de instru��es em assembler para uma express�o posfixa.  *
*                                                                              *
*   Nome: Heron Yugo Inouye                     Matr�cula: 11877               *
*   Nome: Tiago Romero Garcia                   Matr�cula: 12643               *
*   Ci�ncia da Computa��o - Universidade Federal de Itajub�                    *
*                                                                              *
*******************************************************************************/

#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//----------------------------------------------------------------------------//

// Declara��o de constantes
#define MAX 50

//----------------------------------------------------------------------------//

// Declara��o de estruturas
typedef struct PILHAc
{
	char valor[MAX];
   int base, limite, topo;
} PILHAc;

typedef struct PILHAf
{
	float valor[MAX];
   int base, limite, topo;
} PILHAf;

//----------------------------------------------------------------------------//

// Declara��o de prot�tipos das fun��es
int   Assembler(char *);
int   AvaliaExpressaoPosfixa(char *);
int   AvaliaExpressaoPrefixa(char *);
char  cPop(PILHAc &);
int   cPush(PILHAc &, char);
float fPop(PILHAf &);
int   fPush(PILHAf &, float);
int   InfixaPosfixa(char *);
int   InfixaPrefixa(char *);
int   Menu(void);

//----------------------------------------------------------------------------//

// Fun��o main
void main(void)
{
	// Declara��o de Vari�veis
   int op, ret;
   char *exp;

	// Corpo do programa
	do
   {
		op = Menu();
      switch(op)
      {
      	case 49: // Transformar expressao de infixa para posfixa
         			exp[0] = '\0';
						printf("\n\n\n\tDigite a expressao: ");
                  gets(exp);
                  ret = InfixaPosfixa(exp);
                  if (ret == -1) printf("\n\n\tERRO: Expressao invalida!");
                  else if (ret == -2) printf("\n\n\tERRO: Expressao muito longa!");
                  printf("\n\t[Pressione qualquer tecla para continuar...]\n");
                  getch();
         			break;

         case 50: // Transformar expressao de infixa para prefixa
         			exp[0] = '\0';
						printf("\n\n\n\tDigite a expressao: ");
                  gets(exp);
                  ret = InfixaPrefixa(exp);
                  if (ret == -1) printf("\n\n\tERRO: Expressao invalida!");
                  else if (ret == -2) printf("\n\n\tERRO: Expressao muito longa!");
                  printf("\n\t[Pressione qualquer tecla para continuar...]\n");
                  getch();
         			break;

         case 51: // Avaliar expressao posfixa
                  exp[0] = '\0';
						printf("\n\n\n\tDigite a expressao: ");
                  gets(exp);
                  ret = AvaliaExpressaoPosfixa(exp);
                  if (ret == -1) printf("\n\n\tERRO: Expressao invalida!");
                  else if (ret == -2) printf("\n\n\tERRO: Expressao muito longa!");
                  else if (ret == -3) printf("\n\n\tERRO: Divisao por zero!");
                  printf("\n\t[Pressione qualquer tecla para continuar...]\n");
                  getch();
         			break;

         case 52: // Avaliar expressao prefixa
         			exp[0] = '\0';
						printf("\n\n\n\tDigite a expressao: ");
                  gets(exp);
                  ret = AvaliaExpressaoPrefixa(exp);
                  if (ret == -1) printf("\n\n\tERRO: Expressao invalida!");
                  else if (ret == -2) printf("\n\n\tERRO: Expressao muito longa!");
                  else if (ret == -3) printf("\n\n\tERRO: Divisao por zero!");
                  printf("\n\t[Pressione qualquer tecla para continuar...]\n");
                  getch();
         			break;

         case 53: // Gerar instru��es em Assembler para uma express�o posfixa
                  exp[0] = '\0';
						printf("\n\n\n\tDigite a expressao: ");
                  gets(exp);
                  ret = Assembler(exp);
                  if (ret == -1) printf("\n\n\tERRO: Expressao invalida!");
                  else if (ret == -2) printf("\n\n\tERRO: Expressao muito longa!");
                  else if (ret == -3) printf("\n\n\tERRO: Divisao por zero!");
                  printf("\n\t[Pressione qualquer tecla para continuar...]\n");
                  getch();
         	   	break;

         case 48: // Sair
         			printf("\n\n\n\t\aFinalizando...\n\t[Pressione qualquer tecla para continuar...]\n");
                  getch();
         			break;

         default: // Op��o inv�lida
         			printf("\n\n\n\t\aERRO: Opcao invalida!\n\t[Pressione qualquer tecla para continuar...]\n");
                  getch();
                  break;

      } // Fim de switch
   } while (op!=48);

} // Fim de main

//----------------------------------------------------------------------------//

// Fun��o Assembler: Gera instru��es em Assembler para uma express�o posfixa
int Assembler(char *exp)
{
	// Declara��o de vari�veis
   PILHAf Pilha, PilhaT;
   char *temp = "\0";
   int i, tam, sub=0;
   float op1, op2, op1t, op2t, res=0;

	// Inicializa��o da estrutura
   Pilha.base = Pilha.topo = PilhaT.base = PilhaT.topo = -1;
   Pilha.limite = PilhaT.limite = MAX-1;

   // Express�o vazia
   if (exp[0]=='\0') return -1;

   tam = strlen(exp);

   // Express�o muito longa
   if (tam >= MAX-1) return -2;

   // Execu��o do processo
   for (i=0; i<tam; i++)
   {
   	if ((exp[i] == '+')||(exp[i] == '-')||(exp[i] == '*')||(exp[i] == '/')||(exp[i] == '$'))
      {
  			op2 = fPop(Pilha);
  			op1 = fPop(Pilha);
  			if (Pilha.topo == -2) return -1;
  			op2t = fPop(PilhaT);
  			op1t = fPop(PilhaT);
  			if (PilhaT.topo == -2) return -1;

        	if (op1t != 0) printf("\n\tLD     T%1.0f\t// valor %2.2f no AC", op1t, op1);
        	else printf("\n\tLD     %2.2f\t// valor %2.2f no AC", op1, op1);

			switch (exp[i])
      	{
				case '+': // Opera��o +
	                   res = op1+op2;
							 if (op2t != 0) printf("\n\tAD     T%1.0f\t// %2.2f + %2.2f = %2.2f", op2t, op1, op2, res);
   	                else printf("\n\tAD     %2.2f\t// %2.2f + %2.2f = %2.2f", op2, op1, op2, res);
         				 sub++;
							 if (fPush(Pilha, res) == -1) return -1;
							 if (fPush(PilhaT, sub) == -1) return -1;
         	          break;

				case '-': // Opera��o -
	                   res = op1-op2;
							 if (op2t != 0) printf("\n\tSB     T%1.0f\t// %2.2f - %2.2f = %2.2f", op2t, op1, op2, res);
   	                else printf("\n\tSB     %2.2f\t// %2.2f - %2.2f = %2.2f", op2, op1, op2, res);
         				 sub++;
							 if (fPush(Pilha, res) == -1) return -1;
							 if (fPush(PilhaT, sub) == -1) return -1;
         	          break;

				case '*': // Opera��o *
	                   res = op1*op2;
							 if (op2t != 0) printf("\n\tML     T%1.0f\t// %2.2f * %2.2f = %2.2f", op2t, op1, op2, res);
   	                else printf("\n\tML     %2.2f\t// %2.2f * %2.2f = %2.2f", op2, op1, op2, res);
         				 sub++;
							 if (fPush(Pilha, res) == -1) return -1;
							 if (fPush(PilhaT, sub) == -1) return -1;
         	          break;

				case '/': // Opera��o /
	                   res = op1/op2;
							 if (op2t != 0) printf("\n\tDV     T%1.0f\t// %2.2f / %2.2f = %2.2f", op2t, op1, op2, res);
   	                else printf("\n\tDV     %2.2f\t// %2.2f / %2.2f = %2.2f", op2, op1, op2, res);
         				 sub++;
							 if (fPush(Pilha, res) == -1) return -1;
							 if (fPush(PilhaT, sub) == -1) return -1;
         	          break;

				case '$': // Opera��o $
	                   res = pow(op1, op2);
							 if (op2t != 0) printf("\n\tEX     T%1.0f\t// %2.2f $ %2.2f = %2.2f", op2t, op1, op2, res);
   	                else printf("\n\tEX     %2.2f\t// %2.2f $ %2.2f = %2.2f", op2, op1, op2, res);
         				 sub++;
							 if (fPush(Pilha, res) == -1) return -1;
							 if (fPush(PilhaT, sub) == -1) return -1;

         } // Fim de switch

			if (i != tam-1) printf("\n\tST     T%d\t// T%d recebe o conteudo de AC, isto e, recebe %2.2f", sub, sub, res);
      }
      else // Empilha o operando
      {
			temp[0] = exp[i];
			if (fPush(Pilha, atof(temp)) == -1) return -1;
			if (fPush(PilhaT, 0) == -1) return -1;
      }
   } // Fim de for

   res = fPop(Pilha);
	if (Pilha.topo == -2) return -1;
   printf("\n\tST     R\t// R recebe o conteudo de AC, isto e, recebe %2.2f\n", res);

	// Express�o incorreta
   if (Pilha.topo != -1) return -1;

   return 1;

} // Fim de Assembler

//----------------------------------------------------------------------------//

// Fun��o AvaliaExpressaoPosfixa: Avalia uma expressao posfixa
int AvaliaExpressaoPosfixa(char *exp)
{
	// Declara��o de vari�veis
   PILHAf Pilha;
   char *temp = "\0";
   int tam;
   float op1, op2, res;

	// Inicializa��o da estrutura
   Pilha.base = Pilha.topo = -1;
   Pilha.limite = MAX-1;

   // Express�o vazia
   if (exp[0]=='\0') return -1;

	tam = strlen(exp);

   // Express�o muito longa
   if (tam >= MAX-1) return -2;

   for (int i=0; i<tam; i++)
   {
		switch (exp[i])
      {
			case '+': // Opera��o +
         			 op2 = fPop(Pilha);
         			 op1 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   op1 = op1+op2;
						 if (fPush(Pilha, op1) == -1) return -1;
                   break;

         case '-': // Opera��o -
         			 op2 = fPop(Pilha);
         			 op1 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   op1 = op1-op2;
						 if (fPush(Pilha, op1) ==- 1) return -1;
                   break;

         case '*': // Opera��o *
         			 op2 = fPop(Pilha);
         			 op1 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   op1 = op1*op2;
						 if (fPush(Pilha, op1) == -1) return -1;
                   break;

         case '/': // Opera��o /
         			 op2 = fPop(Pilha);
         			 op1 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   if (op2 == 0) return -3;
                   op1 = op1/op2;
						 if (fPush(Pilha, op1) == -1) return -1;
                   break;

         case '$': // Opera��o $
         			 op2 = fPop(Pilha);
         			 op1 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   op1 = pow(op1, op2);
						 if (fPush(Pilha, op1) == -1) return -1;
                   break;

         default:  // Empilha o operando
         			 temp[0] = exp[i];
         			 if (fPush(Pilha, atof(temp)) == -1) return -1;

      } // Fim de switch
   } // Fim de for

   res = fPop(Pilha);

	// Express�o incorreta
   if (Pilha.topo != -1) return -1;

 	printf("\n\n\tResultado: %2.2f", res);

	return 1;

} // Fim de AvaliaExpressaoPosfixa

//----------------------------------------------------------------------------//

// Fun��o AvaliaExpressaoPrefixa: Avalia uma expressao prefixa
int AvaliaExpressaoPrefixa(char *exp)
{
	// Declara��o de vari�veis
   PILHAf Pilha;
   char *temp = "\0";
   int tam;
   float op1, op2, res;

	// Inicializa��o da estrutura
   Pilha.base = Pilha.topo = -1;
   Pilha.limite = MAX-1;

   // Express�o vazia
   if (exp[0]=='\0') return -1;

	tam = strlen(exp);

   // Express�o muito longa
   if (tam >= MAX-1) return -2;

   for (int i=tam-1; i>=0; i--)
   {
		switch (exp[i])
      {
			case '+': // Opera��o +
         			 op1 = fPop(Pilha);
         			 op2 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   op1 = op1+op2;
						 if (fPush(Pilha, op1) == -1) return -1;
                   break;

         case '-': // Opera��o -
         			 op1 = fPop(Pilha);
         			 op2 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   op1 = op1-op2;
						 if (fPush(Pilha, op1) == -1) return -1;
                   break;

         case '*': // Opera��o *
         			 op1 = fPop(Pilha);
         			 op2 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   op1 = op1*op2;
						 if (fPush(Pilha, op1) == -1) return -1;
                   break;

         case '/': // Opera��o /
         			 op1 = fPop(Pilha);
         			 op2 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   if (op2 == 0) return -3;
                   op1 = op1/op2;
						 if (fPush(Pilha, op1) == -1) return -1;
                   break;

         case '$': // Opera��o $
         			 op1 = fPop(Pilha);
         			 op2 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   op1 = pow(op1, op2);
						 if (fPush(Pilha, op1) == -1) return -1;
                   break;

         default:  // Empilha o operando
         			 temp[0] = exp[i];
         			 if (fPush(Pilha, atof(temp)) == -1) return -1;

      } // Fim de switch
   } // Fim de for

   res = fPop(Pilha);

	// Express�o incorreta
   if (Pilha.topo != -1) return -1;

 	printf("\n\n\tResultado: %2.2f", res);

	return 1;

} // Fim de AvaliaExpressaoPrefixa

//----------------------------------------------------------------------------//

// Fun��o cPush: Empilha um valor numa pilha char
int cPush(PILHAc &Pilha, char valor)
{
  // Verificando Overflow
  if (Pilha.topo >= Pilha.limite) return -1;

  Pilha.topo++;
  Pilha.valor[Pilha.topo] = valor;

  return 1;

} // Fim de cPush

//----------------------------------------------------------------------------//

// Fun��o cPop: Desempilha um valor de uma pilha char
char cPop(PILHAc &Pilha)
{
  // Defini��o de vari�veis locais
  char valor;

  // Verificando Underflow
  if (Pilha.topo < Pilha.base) Pilha.topo = -2;

  valor = Pilha.valor[Pilha.topo];
  Pilha.topo--;

  return valor;

} // Fim de cPop

//----------------------------------------------------------------------------//

// Fun��o fPush: Empilha um valor numa pilha float
int fPush(PILHAf &Pilha, float valor)
{
  // Verificando Overflow
  if (Pilha.topo >= Pilha.limite) return -1;

  Pilha.topo++;
  Pilha.valor[Pilha.topo] = valor;

  return 1;

} // Fim de fPush

//----------------------------------------------------------------------------//

// Fun��o fPop: Desempilha um valor de uma pilha float
float fPop(PILHAf &Pilha)
{
  // Defini��o de vari�veis locais
  float valor;

  // Verificando Underflow
  if (Pilha.topo < Pilha.base) Pilha.topo = -2;

  valor = Pilha.valor[Pilha.topo];
  Pilha.topo--;

  return valor;

} // Fim de fPop

//----------------------------------------------------------------------------//

// Fun��o InfixaPosfixa: Transforma uma expressao de infixa para posfixa
int InfixaPosfixa(char *exp)
{
	// Declara��o de vari�veis
   PILHAc PilhaA;
   char ListaB[MAX], aux, aux2;
	int pos=0, tam;

	// Inicializa��o da estrutura
   PilhaA.base = PilhaA.topo = -1;
   PilhaA.limite = MAX-1;

   // Express�o vazia
   if (exp[0]=='\0') return -1;

	tam = strlen(exp);

   // Express�o muito longa
   if (tam >= MAX-1) return -2;

   for (int i=0; i<tam; i++)
   {
		switch (exp[i])
      {
      	case '(':
         case '[':
         case '{': // Empilha abre par�ntese na PilhaA
         			 if (cPush(PilhaA, exp[i])==-1) return -1;
                   break;

         case ')': // Transforma o que est� dentro do par�ntese inteiro
                   aux = cPop(PilhaA);
			  			 if (PilhaA.topo == -2) return -1;
                   while (aux != '(')
                   {
                   	ListaB[pos] = aux;
                     pos++;
                     aux = cPop(PilhaA);
			  			 	if (PilhaA.topo == -2) return -1;
                   } // Fim de while
                   break;

         case ']': // Transforma o que est� dentro do colchete inteiro
                   aux = cPop(PilhaA);
			  			 if (PilhaA.topo == -2) return -1;
                   while (aux != '[')
                   {
                   	ListaB[pos] = aux;
                     pos++;
                     aux = cPop(PilhaA);
			  			 	if (PilhaA.topo == -2) return -1;
                   } // Fim de while
                   break;

         case '}': // Transforma o que est� dentro da chave inteira
                   aux = cPop(PilhaA);
			  			 if (PilhaA.topo == -2) return -1;
                   while (aux != '{')
                   {
                   	ListaB[pos] = aux;
                     pos++;
                     aux = cPop(PilhaA);
			  			 	if (PilhaA.topo == -2) return -1;
                   } // Fim de while
                   break;

			case '$': // Insere operador $
         			 aux = cPop(PilhaA);
			  			 if (PilhaA.topo == -2) return -1;
                   switch (aux)
                   {
                     case '$': // exp[i] tem preced�ncia igual
         			 				 if (cPush(PilhaA, aux) == -1) return -1;
         			 				 if (cPush(PilhaA, exp[i]) == -1) return -1;
                               break;

                     case '(':
                     case '[':
                     case '{':
                   	case '/':
							case '*':
                     case '-':
                     case '+': // exp[i] tem preced�ncia maior
                     			 aux2 = aux;
                     			 while (aux2 == '$')
                     			 {
                                 ListaB[pos] = aux2;
                                 pos++;
                                 aux2 = cPop(PilhaA);
			  			 					if (PilhaA.topo == -2) return -1;
                     			 } // Fim de while
         			 				 if (cPush(PilhaA, aux2) == -1) return -1;
         			 				 if (cPush(PilhaA, exp[i]) == -1) return -1;
                     			 break;

                     default : if (cPush(PilhaA, aux) == -1) return -1;
                     			 break;

                   } // Fim de switch
                   break;

			case '/': // Insere operador /
			case '*': // Insere operador *
         			 aux = cPop(PilhaA);
			  			 if (PilhaA.topo == -2) return -1;
                   switch (aux)
                   {
                     case '(':
                     case '[':
                     case '{':
                     case '-':
                     case '+': // exp[i] tem preced�ncia maior
         			 				 if (cPush(PilhaA, aux) == -1) return -1;
         			 				 if (cPush(PilhaA, exp[i]) == -1) return -1;
                               break;

                   	case '/':
							case '*':
                     case '$': // exp[i] tem preced�ncia menor ou igual
                     			 aux2 = aux;
                     			 while ((aux2 == '$')||(aux2 == '*')||(aux2 == '/'))
                     			 {
                                 ListaB[pos] = aux2;
                                 pos++;
                                 aux2 = cPop(PilhaA);
			  			 					if (PilhaA.topo == -2) return -1;
                     			 } // Fim de while
         			 				 if (cPush(PilhaA, aux2) == -1) return -1;
         			 				 if (cPush(PilhaA, exp[i]) == -1) return -1;
                     			 break;

                     default : if (cPush(PilhaA, aux) ==- 1) return -1;
                     			 break;

                   } // Fim de switch
                   break;

			case '+': // Insere operador +
			case '-': // Insere operador -
         			 aux = cPop(PilhaA);
			  			 if (PilhaA.topo == -2) return -1;
                   switch (aux)
                   {
                     case '(':
                     case '[':
                     case '{': // exp[i] tem preced�ncia maior
                     			 if (cPush(PilhaA, aux) == -1) return -1;
                     			 if (cPush(PilhaA, exp[i]) == -1) return -1;
                               break;

                     case '-':
                     case '+':
                   	case '/':
							case '*':
                     case '$': // exp[i] tem preced�ncia menor ou igual
                     			 aux2 = aux;
                     			 while ((aux2 == '$')||(aux2 == '*')||(aux2 == '/')||(aux2 == '+')||(aux2 == '-'))
                     			 {
                                 ListaB[pos] = aux2;
                                 pos++;
                                 aux2 = cPop(PilhaA);
			  			 					if (PilhaA.topo == -2) return -1;
                     			 } // Fim de while
                               if (cPush(PilhaA, aux2) == -1) return -1;
                               if (cPush(PilhaA, exp[i]) == -1) return -1;
                     			 break;

                     default : if (cPush(PilhaA, aux) == -1) return -1;
                     			 break;

                   } // Fim de switch
                   break;

         default:  // Insere operando na ListaB
                   ListaB[pos] = exp[i];
                   pos++;
                   break;

      } // Fim de switch
   } // Fim de for

   while (PilhaA.topo != -1)
   {
		ListaB[pos] = cPop(PilhaA);
      pos++;
   } // Fim de while
   ListaB[pos] = '\0';

	printf("\n\n\tForma Posfixa: %s", ListaB);

	return 1;

} // Fim de InfixaPosfixa

//----------------------------------------------------------------------------//

// Fun��o InfixaPrefixa: Transforma uma expressao de infixa para prefixa
int InfixaPrefixa(char *exp)
{
	// Declara��o de vari�veis
   PILHAc PilhaA;
   char ListaB[MAX], aux, aux2;
	int pos, posn, tam;

	// Inicializa��o da estrutura
   PilhaA.base = PilhaA.topo = -1;
   PilhaA.limite = MAX-1;

   // Express�o vazia
   if (exp[0]=='\0') return -1;

	tam = strlen(exp);
   pos = tam;

   // Express�o muito longa
   if (tam >= MAX-1) return -2;

   for (int i=tam-1; i>=0; i--)
   {
		switch (exp[i])
      {
      	case ')':
         case ']':
         case '}': // Empilha abre par�ntese na PilhaA
         			 if (cPush(PilhaA, exp[i]) == -1) return -1;
                   break;

         case '(': // Transforma o que est� dentro do par�ntese inteiro
                   aux = cPop(PilhaA);
			  			 if (PilhaA.topo == -2) return -1;
                   while (aux != ')')
                   {
                   	ListaB[pos] = aux;
                     pos--;
                     aux = cPop(PilhaA);
			  			 	if (PilhaA.topo == -2) return -1;
                   } // Fim de while
                   break;

         case '[': // Transforma o que est� dentro do colchete inteiro
                   aux = cPop(PilhaA);
			  			 if (PilhaA.topo == -2) return -1;
                   while (aux != ']')
                   {
                   	ListaB[pos] = aux;
                     pos--;
                     aux = cPop(PilhaA);
			  			 	if (PilhaA.topo == -2) return -1;
                   } // Fim de while
                   break;

         case '{': // Transforma o que est� dentro da chave inteira
                   aux = cPop(PilhaA);
			  			 if (PilhaA.topo == -2) return -1;
                   while (aux != '}')
                   {
                   	ListaB[pos] = aux;
                     pos--;
                     aux = cPop(PilhaA);
			  			 	if (PilhaA.topo == -2) return -1;
                   } // Fim de while
                   break;

			case '$': // Insere operador $
         			 aux = cPop(PilhaA);
			  			 if (PilhaA.topo == -2) return -1;
                   switch (aux)
                   {
                     case ')':
                     case ']':
                     case '}':
                   	case '/':
							case '*':
                     case '-':
                     case '+':
                     case '$': // exp[i] tem preced�ncia igual ou maior que o operador do topo da pilha
                               if (cPush(PilhaA, aux) == -1) return -1;
         			 				 if (cPush(PilhaA, exp[i]) == -1) return -1;
                               break;

                     default : if (cPush(PilhaA, aux) == -1) return -1;
                     			 break;

                   } // Fim de switch
                   break;

			case '/': // Insere operador /
			case '*': // Insere operador *
         			 aux = cPop(PilhaA);
			  			 if (PilhaA.topo == -2) return -1;
                   switch (aux)
                   {
                     case ')':
                     case ']':
                     case '}':
                     case '-':
                     case '+':
                   	case '/':
							case '*': // exp[i] tem preced�ncia maior ou igual que o operador do topo da pilha
                     			 if (cPush(PilhaA, aux) == -1) return -1;
         			 				 if (cPush(PilhaA, exp[i]) == -1) return -1;
                               break;

                     case '$': // exp[i] tem preced�ncia menor que operador do topo da pilha
                               aux2 = aux;
                     			 while (aux2 == '$')
                     			 {
                                 ListaB[pos] = aux2;
                                 pos--;
                                 aux2 = cPop(PilhaA);
			  			 					if (PilhaA.topo == -2) return -1;
                     			 } // Fim de while
         			 				 if (cPush(PilhaA, aux2) == -1) return -1;
         			 				 if (cPush(PilhaA, exp[i]) == -1) return -1;
                     			 break;

                     default : if (cPush(PilhaA, aux) == -1) return -1;
                     			 break;

                   } // Fim de switch
                   break;

			case '+': // Insere operador +
			case '-': // Insere operador -
         			 aux = cPop(PilhaA);
			  			 if (PilhaA.topo == -2) return -1;
                   switch (aux)
                   {
                     case ')':
                     case ']':
                     case '}':
                     case '-':
                     case '+': // exp[i] tem preced�ncia igual ou maior que operador do topo da pilha
                     			 if (cPush(PilhaA, aux) == -1) return -1;
                     			 if (cPush(PilhaA, exp[i]) == -1) return -1;
                               break;

                     case '/':
							case '*':
                     case '$': // exp[i] tem preced�ncia menor que operador do topo da pilha
                               aux2 = aux;
                     			 while ((aux2 == '$')||(aux2 == '/')||(aux2 == '*'))
                     			 {
                                 ListaB[pos] = aux2;
                                 pos--;
                                 aux2 = cPop(PilhaA);
			  			 					if (PilhaA.topo == -2) return -1;
                     			 } // Fim de while
         			 				 if (cPush(PilhaA, aux2) == -1) return -1;
         			 				 if (cPush(PilhaA, exp[i]) == -1) return -1;
                     			 break;

                     default : if (cPush(PilhaA, aux) == -1) return -1;
                     			 break;

                   } // Fim de switch
                   break;

         default:  // Insere operando na ListaB
                   ListaB[pos] = exp[i];
                   pos--;
                   break;

      } // Fim de switch
   } // Fim de for

   while (PilhaA.topo != -1)
   {
		ListaB[pos] = cPop(PilhaA);
      pos++;
   } // Fim de while

	for (posn=-1; pos<=tam; pos++, posn++)
   	ListaB[posn] = ListaB[pos];
   ListaB[posn] = '\0';

	printf("\n\n\tForma Prefixa: %s", ListaB);

	return 1;

} // Fim de InfixaPrefixa

//----------------------------------------------------------------------------//

// Fun��o Menu: Imprime o menu
int Menu(void)
{
	// Declara��o de vari�veis
   int op;

   // Impress�o do menu
   clrscr();
	printf("\n     15o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
	printf("\n     Nome: Heron Yugo Inouye    -  Matricula: 11877  -  CCO 2003");
	printf("\n     Nome: Tiago Romero Garcia  -  Matricula: 12643  -  CCO 2004\n\n");
	printf("\n\tMenu de opcoes:\n");
	printf("\n\t  1: Transformar expressao de infixa para posfixa.");
	printf("\n\t  2: Transformar expressao de infixa para prefixa.");
	printf("\n\t  3: Avaliar expressao posfixa.");
	printf("\n\t  4: Avaliar expressao prefixa.");
	printf("\n\t  5: Gerar instrucoes em Assembler para uma expressao posfixa.");
	printf("\n\t  0: Sair.\n");
	printf("\n\tEscolha uma opcao: ");
	op = getch();

	// Retorno da op��o escolhida
   return op;

} // Fim de Menu

