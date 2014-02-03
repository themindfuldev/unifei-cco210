/*******************************************************************************
*                                                                              *
*   CCO210 - Estruturas de Dados / Prof. Sdnei Brito                           *
*   Trabalho 13 - Entrega: 27/8/2004                                           *
*   Calcula expressões matemáticas usando pilha seqüencial                     *
*                                                                              *
*   Nome: Cláudio Paulo Faustino                Matrícula: 12620               *
*   Nome: Tiago Romero Garcia                   Matrícula: 12643               *
*   Ciências da Computação / 1° ano, 2° semestre                               *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define Max 100

//definindo estruturas
typedef struct PILHAC{

	char Carac[Max];
   int Base,Limite,Topo;

}PILHAC;

typedef struct PILHAN{

	float Carac[Max];
   int Base,Limite,Topo;

}PILHAN;

//prototipos das funcoes
float sPopN(PILHAN &);
char sPopC(PILHAC &);
int sPushN(PILHAN &, float);
int sPushC(PILHAC &, char);
int CriaPilhas(char *, PILHAN &, PILHAC &);

//inicio da funcao principal
void main(){

	//declaracao das variveis e tipos
   char Exp[Max]="";
   int ret;
   PILHAN Numeros;
   PILHAC Operadores;


   //inicializando pilhas
   Numeros.Base=0;
   Numeros.Limite=100;
   Numeros.Topo=-1;

   Operadores.Base=0;
   Operadores.Limite=100;
   Operadores.Topo=-1;

   // Leitura da expressão
  clrscr();
  printf("\n     13o. trabalho de CCO210 - Estruturas de Dados / Prof. Sdnei Brito");
  printf("\n     Nome: Claudio Paulo Faustino - Matricula: 12620 - CCO 2004");
  printf("\n     Nome: Tiago Romero Garcia    - Matricula: 12643 - CCO 2004\n");
  printf("\n\n     O programa funciona com:\n\t\t(, ), [, ], {, }, +, -, *, / e inteiros entre 0 e 9");
  printf("\n\n\tDigite a expressao: ");
  gets(Exp);

  // Verificando a pilha
  ret = CriaPilhas(Exp, Numeros, Operadores);
  if (ret == -1) printf("\n\tERRO: Expressao incorreta!\n\t      Lembre-se de usar apenas numeros positivos entre 0 e 9.");
  else if (ret == -2) printf("\n\tERRO: Divisao por zero!");
  else printf("\n\tResultado: %d", ret);

  printf("\n\t[Pressione qualquer tecla para terminar...]\n");
  getch();

}//fim da main
//----------------------------------------------------------------------------//

//inicio da funcao criapilha
int CriaPilhas(char *Exp, PILHAN &Numeros, PILHAC &Operadores){

  // Definição de variáveis locais
  int ret = 1, tam = strlen(Exp);
  float numA, numB;
  char op, *cnum="";

  // Varre a expressão
  for (int i=0; (i<tam)&&(ret!=-2); i++) {
    switch(Exp[i]) {
      case '(':
      case '[':
      case '{':
      case '+':
      case '-':
      case '*':
      case '/':
        sPushC(Operadores, Exp[i]);
        break;

      case ')':
        numA = sPopN(Numeros);
        if (numA == -1) ret = -1;
        numB = sPopN(Numeros);
        if (numB == -1) ret = -1;
        op = sPopC(Operadores);
        if (op == 'e') ret = -1;
        switch (op) {
          case '+':
            numA = numB+numA;
            break;

          case '-':
            numA = numB-numA;
            break;

          case '*':
            numA = numB*numA;
            break;

          case '/':
            if (numA == 0) {
              ret = -2;
              break;
            }
            numA = numB/numA;
            break;

          default:
            ret = -1;
        }
        sPushN(Numeros, numA);
        op = sPopC(Operadores);
        if (op != '(') ret = -1;
        break;

      case ']':
        numA = sPopN(Numeros);
        if (numA == -1) ret = -1;
        numB = sPopN(Numeros);
        if (numB == -1) ret = -1;
        op = sPopC(Operadores);
        if (op == 'e') ret = -1;
        switch (op) {
          case '+':
            numA = numB+numA;
            break;

          case '-':
            numA = numB-numA;
            break;

          case '*':
            numA = numB*numA;
            break;

          case '/':
            if (numA == 0) {
              ret = -2;
              break;
            }
            numA = numB/numA;
            break;

          default:
            ret = -1;
        }
        sPushN(Numeros, numA);
        op = sPopC(Operadores);
        if (op != '[') ret = -1;
        break;

      case '}':
        numA = sPopN(Numeros);
        if (numA == -1) ret = -1;
        numB = sPopN(Numeros);
        if (numB == -1) ret = -1;
        op = sPopC(Operadores);
        if (op == 'e') ret = -1;
        switch (op) {
          case '+':
            numA = numB+numA;
            break;

          case '-':
            numA = numB-numA;
            break;

          case '*':
            numA = numB*numA;
            break;

          case '/':
            if (numA == 0) {
              ret = -2;
              break;
            }
            numA = numB/numA;
            break;

          default:
            ret = -1;
        }
        sPushN(Numeros, numA);
        op = sPopC(Operadores);
        if (op != '{') ret = -1;
        break;

      default:
        if (i == 0) ret = -1;
        cnum[0] = Exp[i];
        sPushN(Numeros, atof(cnum));
    }
  }

  if ((Numeros.Topo!=0)||(Operadores.Topo >= 0)) ret = -1;
  else if ((ret != -2)&&(ret != -1)) {
    ret = Numeros.Carac[Numeros.Topo];
  }

  return ret;

} // Fim de CriaPilha
//----------------------------------------------------------------------------//

//Inicio da funcao sPushC
int sPushC(PILHAC &Pilha, char Exp){

	if(Pilha.Topo>=Pilha.Limite) return -1; //verificando overflow

   Pilha.Topo++;
   Pilha.Carac[Pilha.Topo]=Exp;

   return 1;

}//fim da sPuchC
//----------------------------------------------------------------------------//

//inicio da sPushN
int sPushN(PILHAN &Pilha, float Exp){

	if(Pilha.Topo>=Pilha.Limite) return -1; //verificando overflow

   Pilha.Topo++;
   Pilha.Carac[Pilha.Topo]=Exp;

   return 1;

}//fim da sPushN
//----------------------------------------------------------------------------//

//inicio da sPopC
char sPopC(PILHAC &Pilha){

   //definindo variaveis locais
   char Valor;

	//nao tem valores a serem desempilhados
   if(Pilha.Topo<Pilha.Base) return 'e';

   //desempilhando
   Valor=Pilha.Carac[Pilha.Topo];
   Pilha.Topo--;

   return Valor;

}//fim da sPopC
//----------------------------------------------------------------------------//

//inicio da sPopN
float sPopN(PILHAN &Pilha){

   //definindo variaveis locais
   int Valor;

	//nao tem valores a serem desempilhados
   if(Pilha.Topo<Pilha.Base) return -1;

   //desempilhando
   Valor=Pilha.Carac[Pilha.Topo];
   Pilha.Topo--;

   return Valor;

}//fim sPopN
//----------------------------------------------------------------------------//
