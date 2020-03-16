#include<stdio.h>
#define INF 987654321
#define N 80

int X[N+1][N+1];
int D[N+2][N+2];

void report(){
  for (int y = 0 ; y < N+2 ; ++y){
    for (int x = 0 ; x < N+2 ; ++x)
      printf("%10d", D[y][x]);
    printf("\n");
  } 
  printf("\n");
}

inline int min(int a, int b, int c){
  int ret = a;
  if (b < ret) ret = b;
  if (c < ret) ret = c;
  return ret;
}

void solv(){
  for (int y = 0 ; y < N+2 ; ++y)
    for (int x = 0 ; x < N+2 ; ++x)
      D[y][x] = INF;
  for (int i = 1 ; i <= N ; ++i) D[i][0] = 0;
  //report();
  for (int x = 1 ; x <= N ; ++x){
    for (int y = 1 ; y <= N ; ++y)
      D[y][x] = min (D[y][x-1], D[y-1][x], D[y+1][x]) + X[y][x];
    for (int y = N - 1 ; y > 0 ; --y)
      D[y][x] = min (D[y][x-1], D[y-1][x], D[y+1][x]) + X[y][x];
    //report();
  }

  int answer = INF;
  for (int i = 1 ; i <= N ; ++i)
    if (D[i][N] < answer) answer = D[i][N];
  //report();
  printf("Answer is %d\n", answer);
}

int main(){
  if (N==5) freopen("p081-083_matrix_sample.txt", "rt", stdin);
  else if (N==80) freopen("p081-083_matrix.txt", "rt", stdin);
  else printf("Wrong!");

  char t;
  for (int y = 1 ; y <= N ; ++y){
    for (int x = 1 ; x <= N ; ++x){
      scanf("%d", &X[y][x]);
      scanf("%c", &t);
    }
  }
  solv();
}
