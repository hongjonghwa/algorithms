#include<stdio.h>

unsigned long long solv(int n){
  unsigned long long ret = (unsigned long long)(n*n)* (n*n-1)/2;
  if (n > 2) ret -= (n-1) * (n-2) * 4;
  return ret;
}

int main(){
  int n;
  if (scanf("%d", &n) != 1) return -1;
  for (int i = 1 ; i <= n ; ++i){
    printf("%llu\n", solv(i));
  }

}