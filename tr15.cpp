/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 15 - Entrega: 22/10/2004                                          *
*   Objetivos: Operar com transformação de expressões infixas para prefixa e   *
*              posfixa, avaliação de expressões escritas nessas formas e       *
*              geração de instruções em assembler para uma expressão posfixa.  *
*                                                                              *
*   Nome: Heron Yugo Inouye                     Matrícula: 11877               *
*   Nome: Tiago Romero Garcia                   Matrícula: 12643               *
*   Ciência da Computação - Universidade Federal de Itajubá                    *
*                                                                              *
*******************************************************************************/

#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//----------------------------------------------------------------------------//

// Declaração de constantes
#define MAX 50

//----------------------------------------------------------------------------//

// Declaração de estruturas
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

// Declaração de protótipos das funções
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

// Função main
void main(void)
{
	// Declaração de Variáveis
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

         case 53: // Gerar instruções em Assembler para uma expressão posfixa
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

         default: // Opção inválida
         			printf("\n\n\n\t\aERRO: Opcao invalida!\n\t[Pressione qualquer tecla para continuar...]\n");
                  getch();
                  break;

      } // Fim de switch
   } while (op!=48);

} // Fim de main

//----------------------------------------------------------------------------//

// Função Assembler: Gera instruções em Assembler para uma expressão posfixa
int Assembler(char *exp)
{
	// Declaração de variáveis
   PILHAf Pilha, PilhaT;
   char *temp = "\0";
   int i, tam, sub=0;
   float op1, op2, op1t, op2t, res=0;

	// Inicialização da estrutura
   Pilha.base = Pilha.topo = PilhaT.base = PilhaT.topo = -1;
   Pilha.limite = PilhaT.limite = MAX-1;

   // Expressão vazia
   if (exp[0]=='\0') return -1;

   tam = strlen(exp);

   // Expressão muito longa
   if (tam >= MAX-1) return -2;

   // Execução do processo
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
				case '+': // Operação +
	                   res = op1+op2;
							 if (op2t != 0) printf("\n\tAD     T%1.0f\t// %2.2f + %2.2f = %2.2f", op2t, op1, op2, res);
   	                else printf("\n\tAD     %2.2f\t// %2.2f + %2.2f = %2.2f", op2, op1, op2, res);
         				 sub++;
							 if (fPush(Pilha, res) == -1) return -1;
							 if (fPush(PilhaT, sub) == -1) return -1;
         	          break;

				case '-': // Operação -
	                   res = op1-op2;
							 if (op2t != 0) printf("\n\tSB     T%1.0f\t// %2.2f - %2.2f = %2.2f", op2t, op1, op2, res);
   	                else printf("\n\tSB     %2.2f\t// %2.2f - %2.2f = %2.2f", op2, op1, op2, res);
         				 sub++;
							 if (fPush(Pilha, res) == -1) return -1;
							 if (fPush(PilhaT, sub) == -1) return -1;
         	          break;

				case '*': // Operação *
	                   res = op1*op2;
							 if (op2t != 0) printf("\n\tML     T%1.0f\t// %2.2f * %2.2f = %2.2f", op2t, op1, op2, res);
   	                else printf("\n\tML     %2.2f\t// %2.2f * %2.2f = %2.2f", op2, op1, op2, res);
         				 sub++;
							 if (fPush(Pilha, res) == -1) return -1;
							 if (fPush(PilhaT, sub) == -1) return -1;
         	          break;

				case '/': // Operação /
	                   res = op1/op2;
							 if (op2t != 0) printf("\n\tDV     T%1.0f\t// %2.2f / %2.2f = %2.2f", op2t, op1, op2, res);
   	                else printf("\n\tDV     %2.2f\t// %2.2f / %2.2f = %2.2f", op2, op1, op2, res);
         				 sub++;
							 if (fPush(Pilha, res) == -1) return -1;
							 if (fPush(PilhaT, sub) == -1) return -1;
         	          break;

				case '$': // Operação $
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

	// Expressão incorreta
   if (Pilha.topo != -1) return -1;

   return 1;

} // Fim de Assembler

//----------------------------------------------------------------------------//

// Função AvaliaExpressaoPosfixa: Avalia uma expressao posfixa
int AvaliaExpressaoPosfixa(char *exp)
{
	// Declaração de variáveis
   PILHAf Pilha;
   char *temp = "\0";
   int tam;
   float op1, op2, res;

	// Inicialização da estrutura
   Pilha.base = Pilha.topo = -1;
   Pilha.limite = MAX-1;

   // Expressão vazia
   if (exp[0]=='\0') return -1;

	tam = strlen(exp);

   // Expressão muito longa
   if (tam >= MAX-1) return -2;

   for (int i=0; i<tam; i++)
   {
		switch (exp[i])
      {
			case '+': // Operação +
         			 op2 = fPop(Pilha);
         			 op1 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   op1 = op1+op2;
						 if (fPush(Pilha, op1) == -1) return -1;
                   break;

         case '-': // Operação -
         			 op2 = fPop(Pilha);
         			 op1 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   op1 = op1-op2;
						 if (fPush(Pilha, op1) ==- 1) return -1;
                   break;

         case '*': // Operação *
         			 op2 = fPop(Pilha);
         			 op1 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   op1 = op1*op2;
						 if (fPush(Pilha, op1) == -1) return -1;
                   break;

         case '/': // Operação /
         			 op2 = fPop(Pilha);
         			 op1 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   if (op2 == 0) return -3;
                   op1 = op1/op2;
						 if (fPush(Pilha, op1) == -1) return -1;
                   break;

         case '$': // Operação $
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

	// Expressão incorreta
   if (Pilha.topo != -1) return -1;

 	printf("\n\n\tResultado: %2.2f", res);

	return 1;

} // Fim de AvaliaExpressaoPosfixa

//----------------------------------------------------------------------------//

// Função AvaliaExpressaoPrefixa: Avalia uma expressao prefixa
int AvaliaExpressaoPrefixa(char *exp)
{
	// Declaração de variáveis
   PILHAf Pilha;
   char *temp = "\0";
   int tam;
   float op1, op2, res;

	// Inicialização da estrutura
   Pilha.base = Pilha.topo = -1;
   Pilha.limite = MAX-1;

   // Expressão vazia
   if (exp[0]=='\0') return -1;

	tam = strlen(exp);

   // Expressão muito longa
   if (tam >= MAX-1) return -2;

   for (int i=tam-1; i>=0; i--)
   {
		switch (exp[i])
      {
			case '+': // Operação +
         			 op1 = fPop(Pilha);
         			 op2 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   op1 = op1+op2;
						 if (fPush(Pilha, op1) == -1) return -1;
                   break;

         case '-': // Operação -
         			 op1 = fPop(Pilha);
         			 op2 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   op1 = op1-op2;
						 if (fPush(Pilha, op1) == -1) return -1;
                   break;

         case '*': // Operação *
         			 op1 = fPop(Pilha);
         			 op2 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   op1 = op1*op2;
						 if (fPush(Pilha, op1) == -1) return -1;
                   break;

         case '/': // Operação /
         			 op1 = fPop(Pilha);
         			 op2 = fPop(Pilha);
         			 if (Pilha.topo == -2) return -1;
                   if (op2 == 0) return -3;
                   op1 = op1/op2;
						 if (fPush(Pilha, op1) == -1) return -1;
                   break;

         case '$': // Operação $
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

	// Expressão incorreta
   if (Pilha.topo != -1) return -1;

 	printf("\n\n\tResultado: %2.2f", res);

	return 1;

} // Fim de AvaliaExpressaoPrefixa

//----------------------------------------------------------------------------//

// Função cPush: Empilha um valor numa pilha char
int cPush(PILHAc &Pilha, char valor)
{
  // Verificando Overflow
  if (Pilha.topo >= Pilha.limite) return -1;

  Pilha.topo++;
  Pilha.valor[Pilha.topo] = valor;

  return 1;

} // Fim de cPush

//----------------------------------------------------------------------------//

// Função cPop: Desempilha um valor de uma pilha char
char cPop(PILHAc &Pilha)
{
  // Definição de variáveis locais
  char valor;

  // Verificando Underflow
  if (Pilha.topo < Pilha.base) Pilha.topo = -2;

  valor = Pilha.valor[Pilha.topo];
  Pilha.topo--;

  return valor;

} // Fim de cPop

//----------------------------------------------------------------------------//

// Função fPush: Empilha um valor numa pilha float
int fPush(PILHAf &Pilha, float valor)
{
  // Verificando Overflow
  if (Pilha.topo >= Pilha.limite) return -1;

  Pilha.topo++;
  Pilha.valor[Pilha.topo] = valor;

  return 1;

} // Fim de fPush

//----------------------------------------------------------------------------//

// Função fPop: Desempilha um valor de uma pilha float
float fPop(PILHAf &Pilha)
{
  // Definição de variáveis locais
  float valor;

  // Verificando Underflow
  if (Pilha.topo < Pilha.base) Pilha.topo = -2;

  valor = Pilha.valor[Pilha.topo];
  Pilha.topo--;

  return valor;

} // Fim de fPop

//----------------------------------------------------------------------------//

// Função InfixaPosfixa: Transforma uma expressao de infixa para posfixa
int InfixaPosfixa(char *exp)
{
	// Declaração de variáveis
   PILHAc PilhaA;
   char ListaB[MAX], aux, aux2;
	int pos=0, tam;

	// Inicialização da estrutura
   PilhaA.base = PilhaA.topo = -1;
   PilhaA.limite = MAX-1;

   // Expressão vazia
   if (exp[0]=='\0') return -1;

	tam = strlen(exp);

   // Expressão muito longa
   if (tam >= MAX-1) return -2;

   for (int i=0; i<tam; i++)
   {
		switch (exp[i])
      {
      	case '(':
         case '[':
         case '{': // Empilha abre parêntese na PilhaA
         			 if (cPush(PilhaA, exp[i])==-1) return -1;
                   break;

         case ')': // Transforma o que está dentro do parêntese inteiro
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

         case ']': // Transforma o que está dentro do colchete inteiro
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

         case '}': // Transforma o que está dentro da chave inteira
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
                     case '$': // exp[i] tem precedência igual
         			 				 if (cPush(PilhaA, aux) == -1) return -1;
         			 				 if (cPush(PilhaA, exp[i]) == -1) return -1;
                               break;

                     case '(':
                     case '[':
                     case '{':
                   	case '/':
							case '*':
                     case '-':
                     case '+': // exp[i] tem precedência maior
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
                     case '+': // exp[i] tem precedência maior
         			 				 if (cPush(PilhaA, aux) == -1) return -1;
         			 				 if (cPush(PilhaA, exp[i]) == -1) return -1;
                               break;

                   	case '/':
							case '*':
                     case '$': // exp[i] tem precedência menor ou igual
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
                     case '{': // exp[i] tem precedência maior
                     			 if (cPush(PilhaA, aux) == -1) return -1;
                     			 if (cPush(PilhaA, exp[i]) == -1) return -1;
                               break;

                     case '-':
                     case '+':
                   	case '/':
							case '*':
                     case '$': // exp[i] tem precedência menor ou igual
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

// Função InfixaPrefixa: Transforma uma expressao de infixa para prefixa
int InfixaPrefixa(char *exp)
{
	// Declaração de variáveis
   PILHAc PilhaA;
   char ListaB[MAX], aux, aux2;
	int pos, posn, tam;

	// Inicialização da estrutura
   PilhaA.base = PilhaA.topo = -1;
   PilhaA.limite = MAX-1;

   // Expressão vazia
   if (exp[0]=='\0') return -1;

	tam = strlen(exp);
   pos = tam;

   // Expressão muito longa
   if (tam >= MAX-1) return -2;

   for (int i=tam-1; i>=0; i--)
   {
		switch (exp[i])
      {
      	case ')':
         case ']':
         case '}': // Empilha abre parêntese na PilhaA
         			 if (cPush(PilhaA, exp[i]) == -1) return -1;
                   break;

         case '(': // Transforma o que está dentro do parêntese inteiro
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

         case '[': // Transforma o que está dentro do colchete inteiro
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

         case '{': // Transforma o que está dentro da chave inteira
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
                     case '$': // exp[i] tem precedência igual ou maior que o operador do topo da pilha
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
							case '*': // exp[i] tem precedência maior ou igual que o operador do topo da pilha
                     			 if (cPush(PilhaA, aux) == -1) return -1;
         			 				 if (cPush(PilhaA, exp[i]) == -1) return -1;
                               break;

                     case '$': // exp[i] tem precedência menor que operador do topo da pilha
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
                     case '+': // exp[i] tem precedência igual ou maior que operador do topo da pilha
                     			 if (cPush(PilhaA, aux) == -1) return -1;
                     			 if (cPush(PilhaA, exp[i]) == -1) return -1;
                               break;

                     case '/':
							case '*':
                     case '$': // exp[i] tem precedência menor que operador do topo da pilha
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

// Função Menu: Imprime o menu
int Menu(void)
{
	// Declaração de variáveis
   int op;

   // Impressão do menu
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

	// Retorno da opção escolhida
   return op;

} // Fim de Menu

