#include<stdio.h>
#define MIN(a,b) ((a)<(b)?(a):(b))
#define INF 987654321
int X[81][81];
int D[81][81];

void solv(){
  for (int i = 1 ; i <=80 ; ++i) D[0][i] = D[i][0] = INF;
  D[0][1] = 0;
  for (int y = 1 ; y <= 80 ; ++y){
    for (int x = 1 ; x <= 80 ; ++x){
      D[y][x] = MIN(D[y-1][x], D[y][x-1]) + X[y][x];
    }
  }
  printf("Answer is %d\n", D[80][80]);
}

int main(){
  //freopen("p081-083_matrix_sample.txt", "rt", stdin);
  freopen("p081-083_matrix.txt", "rt", stdin);
  char t;
  for (int y = 1 ; y <= 80 ; ++y){
    for (int x = 1 ; x <= 80 ; ++x){
      scanf("%d", &X[y][x]);
      scanf("%c", &t);
    }
  }
  solv();
}
