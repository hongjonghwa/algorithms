#include<stdio.h>
#include<assert.h>

int main(){
  int n;
  if (scanf("%d", &n) != 1) return -1;

  long long sum = (long long) n * (n+1) / 2;
  if (sum % 2 == 1) {
    printf("NO");
    return 0;
  }

  printf("YES\n");
  if (n % 2 == 0) { //even
    int half = n/2;
    printf("%d\n", half);
    for (int i = 1 ; i < half ; i += 2)
      printf("%d ", i);
    for (int i = half+2 ; i <= n ; i += 2)
      printf("%d ", i);
    printf("\n");
    printf("%d\n", half);
    for (int i = 2 ; i <= half ; i += 2)
      printf("%d ", i);
    for (int i = half+1 ; i <= n ; i += 2)
      printf("%d ", i);
    return 0;
  }

  // odd
  int median = (n+1) /2;
  assert (median % 2 == 0);
  int diff = median / 2;
  printf("%d\n", median);
  for (int i = 1 ; i <= n ; i += 2)
    printf("%d ",  i > 1 && i < (diff+1)*2 ? i-1 : i);
  printf("\n");
  printf("%d\n", n-median);
  for (int i = 2 ; i < n ; i += 2)
    printf("%d ",  i <= diff*2 ? i+1 : i);

}