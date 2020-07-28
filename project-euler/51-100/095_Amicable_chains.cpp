#include<stdio.h>


int FACT[1000001];
void e(){
  for (int i = 1 ; i <= 1000000 ; ++i)
    FACT[i] = i;
  for (int i = 2 ; i <= 1000; ++i)
    if (FACT[i] == i)
      for (int j = i*i ; j <= 1000000 ; j += i)
        if (FACT[j] == j)
          FACT[j] = i;
}

int bt(int n){
  if (n == 1) return 1;
  if (n == FACT[n]) return 1 + n;
  int f = FACT[n];
  int x = 1;
  while (n % f == 0){
    n /= f;
    x = x*f + 1;
  }
  int ret = bt(n) * x;
  // printf("    %d  => %d\n", n, ret);
  return ret;
}

int sum_of_divisors(int n){
  return bt(n)-n;
}

int D[1000001];
int discovered[1000001];
int main(){
  e();
  /*
  int test[] = {1,2,220,284, 9464};
  for (int i = 0 ; i < 5; ++i)
    printf("...  %d => %d \n", test[i], sum_of_divisors(test[i]));
  */
  for (int i = 1 ; i <= 1000000 ; ++i){
    int ret = sum_of_divisors(i);
    if (ret <= 1000000)
      D[i] = ret;
  }
  
  int max_cycle = 0;
  int answer = 0;
  for (int i = 1 ; i <= 1000000 ; ++i){
    int x = i;
    int len = 0;
    while (discovered[x]!=i){
      discovered[x] = i;
      x = D[x];
      len++;
    }
    if (len > max_cycle && x == i){
      int k = i;
      for (int j = 0 ; j < len ; ++j){
        printf("%d -> ", k);
        k = D[k];
      }
      printf("(%d)", k);
      printf(": cycle len %d\n", len);

      max_cycle = len;
      answer = i;
    }    
  }
  printf("\nAnswer is %d\n", answer);

}