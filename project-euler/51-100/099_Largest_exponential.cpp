#include <stdio.h>
#include <assert.h>
#include <math.h>

int X[1000][2];
int main(){  
  freopen("p099_base_exp.txt", "r", stdin);

  for (int i = 0 ; i < 1000 ; ++i){
    if (scanf("%d,%d", &X[i][0], &X[i][1]) != 2) break;
  } 
  double max_value = -1;
  int best = -1;
  for (int i = 0 ; i < 1000 ; ++i){
    double val = log10(X[i][0]) * X[i][1];
    if (val > max_value){
      max_value = val;
      best = i;
    }
    printf("\n");
  } 
  printf("Answer is %d\n", best+1);
}




