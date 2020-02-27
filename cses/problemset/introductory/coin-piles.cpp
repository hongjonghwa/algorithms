#include<stdio.h>

int main(){
  int n, a, b;
  if (scanf("%d", &n) != 1) return -1;
  for (int i = 0 ; i < n ; ++i){
    if (scanf("%d%d", &a, &b) != 2) return -1;
    if ( (a+b) % 3== 0 && a*2 >= b && a <= b*2) printf("YES\n");
    else  printf("NO\n");
  }
}