#include<stdio.h>

int solv(int n){
  int num5 =0;
  long long i = 5;
  while (i <= n){
    num5 += n / i;
    i *= 5;      
  }
  return num5;
}

int main(){
  int n;
  if (scanf("%d", &n) != 1) return -1;
  printf("%d", solv(n));
}