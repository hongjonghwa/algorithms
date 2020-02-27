#include<stdio.h>

int MOD = 1e9 + 7;

int main(){
  int n;
  if (scanf("%d", &n) != 1) return -1;
  
  long long x = 2;
  long long ans = 1;
  while (n){
    if (n & 1)
      ans = ans * x % MOD;
    n /= 2;
    x = x * x % MOD;
  }
  printf("%lld", ans);
}