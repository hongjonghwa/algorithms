#include<stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))

int n;
int p[20];
long long sum;
bool pick[20];

long long bt(int idx, long long s){
  if (s > sum/2) return 0;
  if (idx == n) return s;
  long long pick_yes = bt(idx+1, s + p[idx]);
  long long pick_no = bt(idx+1, s);
  return max(pick_yes, pick_no);
}

int main(){
  if (scanf("%d", &n) != 1) return -1;

  for (int i = 0 ; i < n ; ++i)
    if (scanf("%d", &p[i]) != 1) return -1;
  for (int i = 0 ; i < n ; ++i)
    sum += p[i];

  long long half = bt(0, 0L);
  printf("%lld", sum - 2*half);
  
}
