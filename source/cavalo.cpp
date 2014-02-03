#include <conio.h>
#include <iostream>
#include <iomanip>
//using namespace std;

const int Size = 8;
int dx[Size+1] = {0,2,1,-1,-2,-2,-1,1,2},
    dy[Size+1] = {0,1,2,2,1,-1,-2,-2,-1},
    h[Size+1][Size+1],
    n;
//------------------------------------------------------------------
void Print()
{ int i,j;

  for(i=1; i<=n; i++)
  { for(j=1; j<=n; j++)
      cout << setw(5) << h[i][j];
    cout << endl;
  }
  cout << endl;
}
//------------------------------------------------------------------
void TryNextMove(int i, int x, int y, bool &s)
{ int u,v,k;
  bool sucesso;

  k = 0;
  sucesso = false;
  do
  { k++;
    u = x + dx[k];
    v = y + dy[k];
    if (1<=u && u<=n && 1<=v && v<=n && h[u][v]==0)
    { h[u][v] = i;
      if (i < n*n)
      { TryNextMove(i+1,u,v,sucesso);
        if (!sucesso)
          h[u][v] = 0;
      }
      else
        sucesso = true;
    }
  } while (!sucesso && k < Size);
  s = sucesso;
}
//------------------------------------------------------------------
int main()
{ int i,j;
  bool q;

  cout << "Tamanho do tabuleiro (1-8): ";
  cin >> n;
  for(i=1; i<=n; i++)
    for(j=1; j<=n; j++)
      h[i][j] = 0;
  cout << "Posicao inicial do cavalo (x,y): ";
  cin >> i >> j;
  h[i][j] = 1;
  TryNextMove(2,i,j,q);
  if (q)
    Print();
  else
    cout << "Caminho nao encontrado" << endl;

	getch();
  return 0;
}

